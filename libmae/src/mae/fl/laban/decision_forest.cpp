#include "decision_forest.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			decision_forest::decision_forest(std::vector<std::shared_ptr<column_definition> > column_definitions,
					std::vector<int> reserved_columns, unsigned int beats_per_measure, unsigned int beat_duration,
					e_time_unit time_unit, std::shared_ptr<i_decision_maker<i_movement> > dec_maker,
					std::shared_ptr<rewriting_forest> rw, bool cooldown)
			{
				column_definitions_ = column_definitions;
				beats_per_measure_ = beats_per_measure;
				beat_duration_ = beat_duration;
				time_unit_ = time_unit;

				cooldown_ = cooldown;

				for (int reserved : reserved_columns)
				{
					column_ids_.push_back(reserved);
				}

				for (unsigned int i = 0; i < column_definitions_.size(); i++)
				{
					column_ids_.push_back(column_definitions_.at(i)->get_column_index());
				}

				if (dec_maker != nullptr)
				{
					decision_maker_ = dec_maker;
				}
				else
				{
					decision_maker_ = std::shared_ptr<i_decision_maker<i_movement> >(
							new decision_maker(beats_per_measure_));
				}

				if (rw != nullptr)
				{
					rewriting_forest_ = rw;
				}
				else
				{
					rewriting_forest_ = std::shared_ptr<rewriting_forest>(new rewriting_forest());
				}
			}

			decision_forest::~decision_forest()
			{
			}

			std::vector<std::shared_ptr<column_definition> > decision_forest::get_column_definitions() const
			{
				return column_definitions_;
			}

			std::vector<int> decision_forest::get_column_ids() const
			{
				return column_ids_;
			}

			void decision_forest::set_recognition_tolerance(double tolerance)
			{
				if (decision_maker_ != nullptr)
				{
					decision_maker_->set_recognition_tolerance(tolerance);
				}
			}

			double decision_forest::get_recognition_tolerance() const
			{
				if (decision_maker_ != nullptr)
				{
					return decision_maker_->get_recognition_tolerance();
				}
				else
				{
					return 0.0;
				}
			}

			void decision_forest::set_cooldown(bool cooldown)
			{
				cooldown_ = cooldown;
				cooldown_set_.clear();
			}

			bool decision_forest::get_cooldown() const
			{
				return cooldown_;
			}

			int decision_forest::get_sequence_length(std::shared_ptr<laban_sequence> sequence) const
			{
				//return sequence length in milliseconds
				int time = 1;

				if (sequence->get_time_unit() == e_time_unit::SECOND)
				{
					time = 1000;
				}
				else if (sequence->get_time_unit() == e_time_unit::MINUTE)
				{
					time = 60000;
				}

				int length = std::ceil(
						sequence->get_measures() * sequence->get_beats() * sequence->get_beat_duration() * time);

				return length;
			}

			void decision_forest::add_sequence(std::shared_ptr<laban_sequence> sequence)
			{
				//recreate sequence to have columns correctly mapped and
				std::shared_ptr<laban_sequence> recreated_sequence = recreate_sequence(sequence);

				if (recreated_sequences_map_.find(sequence) == recreated_sequences_map_.end())
				{
					recreated_sequences_map_.insert(std::make_pair(sequence, recreated_sequence));
				}
				else
				{
					recreated_sequences_map_[sequence] = recreated_sequence;
				}

				//add to list for later removal by index
				sequences_.push_back(sequence);

				for (unsigned int i = 0; i < column_ids_.size(); i++)
				{
					int column = column_ids_.at(i);
					std::vector<std::shared_ptr<decision_tree<i_movement, laban_sequence> > > tree_list;

					//insert not only the sequence but all rewritten sequences
					std::vector<std::vector<std::shared_ptr<i_movement> > > all_subsequences =
							rewriting_forest_->replacements(recreated_sequence->get_column_movements(column));

					for (unsigned int k = 0; k < all_subsequences.size(); k++)
					{
						std::vector<std::shared_ptr<i_movement> > subsequence = all_subsequences.at(k);

						if (subsequence.size() == 0)
						{
							//subsequence is empty, therefore jump to next column (empty sequences will be handled by the find_submatch method.

						}
						else
						{

							bool listed = false;
							std::shared_ptr<i_movement> decision_item = subsequence.back();

							if (trees_.find(column) != trees_.end())
							{
								//search for a matching tree (which means that the root's decision element compares equal to the last element of the subsequence
								tree_list = trees_.at(column);
								for (unsigned int j = 0; j < tree_list.size(); j++)
								{
									if (tree_list.at(j)->is_root_insertion_matching(decision_item))
									{
										//add in reverse order to tree
										tree_list.at(j)->add_sequence(
												std::shared_ptr<decision_value<i_movement, laban_sequence> >(
														new decision_value<i_movement, laban_sequence>(subsequence,
																sequence)), true);
										listed = true;

										break;
									}
								}
							}
							if (!listed)
							{
								//create a new tree
								tree_list.push_back(
										std::shared_ptr<decision_tree<i_movement, laban_sequence> >(
												new decision_tree<i_movement, laban_sequence>(decision_maker_)));

								//add in reverse order to tree
								tree_list.back()->add_sequence(
										std::shared_ptr<decision_value<i_movement, laban_sequence> >(
												new decision_value<i_movement, laban_sequence>(subsequence, sequence)),
										true);

								//update the list of trees for the column
								if (trees_.find(column) != trees_.end())
								{
									trees_[column] = tree_list;
								}
								else
								{
									trees_.insert(std::make_pair(column, tree_list));
								}
							}
						}
					}
				}

			}

			std::shared_ptr<laban_sequence> decision_forest::recreate_sequence(std::shared_ptr<laban_sequence> sequence)
			{
				std::shared_ptr<laban_sequence> result;

				//check column definitions
				std::vector<std::shared_ptr<column_definition> > col_defs = sequence->get_column_definitions();

				//mapping for forest's definitions to the given sequence's definitions
				std::map<int, int> column_mapping;
				//column_mapping.reserve(col_defs.size());

				for (unsigned int i = 0; i < col_defs.size(); i++)
				{
					bool listed = false;

					//check whether same column definition is defined in the forest
					for (unsigned int j = 0; j < column_definitions_.size(); j++)
					{
						//check equals
						if (col_defs.at(i)->get_pre_sign()->equals(column_definitions_.at(j)->get_pre_sign()))
						{
							listed = true;
							column_mapping.insert(
									std::make_pair(col_defs.at(i)->get_column_index(),
											column_definitions_.at(j)->get_column_index()));
						}
					}

					if (!listed)
					{
						throw std::invalid_argument(
								"Column definition used by the sequence about to be registered does not match any of the given definitions.");
					}
				}

				//create new laban_sequence

				int time_factor = 1;
				if (sequence->get_time_unit() == e_time_unit::SECOND)
				{
					time_factor = 1000;
				}
				else if (sequence->get_time_unit() == e_time_unit::MINUTE)
				{
					time_factor = 60000;
				}

				int new_time_factor = 1;

				if (time_unit_ == e_time_unit::SECOND)
				{
					new_time_factor = 1000;
				}
				else if (time_unit_ == e_time_unit::MINUTE)
				{
					new_time_factor = 60000;
				}

				//total duration in ms
				double total_duration = sequence->get_measures() * sequence->get_beats() * sequence->get_beat_duration()
						* time_factor;
				double new_measures = total_duration / (beats_per_measure_ * beat_duration_ * new_time_factor);

				result = std::shared_ptr<laban_sequence>(
						new laban_sequence(sequence->get_title(), sequence->get_authors().at(0), new_measures,
								time_unit_, beat_duration_, beats_per_measure_));

				//insert updated column definitions
				for (unsigned int i = 0; i < col_defs.size(); i++)
				{
					result->add_column_definition(
							std::shared_ptr<column_definition>(
									new column_definition(column_mapping.at(col_defs.at(i)->get_column_index()),
											col_defs.at(i)->get_pre_sign())));
				}

				//recreate sequence with new values
				std::vector<std::shared_ptr<i_movement> > movements = sequence->get_movements();
				for (unsigned int i = 0; i < movements.size(); i++)
				{
					std::shared_ptr<i_movement> mov = movements.at(i);

					//adjust beat, measure etc

					//exact position in ms
					double exact_pos = (mov->get_measure() * sequence->get_beats() + mov->get_beat())
							* sequence->get_beat_duration() * time_factor;
					//duration in ms
					double duration = mov->get_duration() * sequence->get_beat_duration() * time_factor;

					double new_measure_length = beats_per_measure_ * beat_duration_ * new_time_factor;
					int new_measure = (int) (exact_pos / new_measure_length);
					double new_beat = (exact_pos / new_measure_length - new_measure) * beats_per_measure_;
					double new_duration = duration / (beat_duration_ * new_time_factor);

					//insert new movement
					result->add_movement(mov->recreate(column_mapping, new_measure, new_beat, new_duration));
				}

				return result;
			}

			bool decision_forest::remove_sequence(std::shared_ptr<laban_sequence> sequence)
			{
				for (std::list<std::shared_ptr<laban_sequence> >::iterator it = sequences_.begin();
						it != sequences_.end(); it++)
				{
					if (sequence == *it)
					{
						sequences_.erase(it);
						return remove_sequence_p(sequence);
					}
				}
				return false;
			}

			bool decision_forest::remove_sequence(unsigned int list_index)
			{
				if (list_index > sequences_.size())
				{
					return false;
				}
				unsigned int index = 0;
				for (std::list<std::shared_ptr<laban_sequence> >::iterator it = sequences_.begin();
						it != sequences_.end(); it++)
				{
					if (index == list_index)
					{
						std::shared_ptr<laban_sequence> sequence = *it;
						sequences_.erase(it);
						return remove_sequence_p(sequence);
					}
					index++;
				}
				return false;
			}

			bool decision_forest::remove_sequence_p(std::shared_ptr<laban_sequence> sequence)
			{
				//remove sequence from recreated_sequences_map
				recreated_sequences_map_.erase(sequence);

				//remove sequence from all trees
				for (unsigned int i = 0; i < column_ids_.size(); i++)
				{
					int column_id = column_ids_.at(i);
					if (trees_.find(column_id) != trees_.end())
					{
						std::vector<std::shared_ptr<decision_tree<i_movement, laban_sequence> > > trees_vec = trees_.at(
								column_id);

						for (unsigned int j = trees_vec.size() - 1; j >= 0; j++)
						{
							trees_vec.at(j)->remove_where(sequence);

							if (trees_vec.at(j)->is_empty())
							{
								trees_vec.erase(trees_vec.begin() + j);
							}
						}

						//update the hashmap
						if (trees_vec.size() == 0)
						{
							trees_.erase(column_id);
						}
						else
						{
							trees_[column_id] = trees_vec;
						}
					}
				}
				return false;
			}

			void decision_forest::clear()
			{
				trees_.clear();
				sequences_.clear();
				recreated_sequences_map_.clear();
				clear_buffer();
			}

			void decision_forest::clear_buffer()
			{
				cooldown_set_.clear();
			}

			void decision_forest::add_rewriting_rule(std::vector<std::shared_ptr<i_movement> > sequence,
					std::shared_ptr<std::vector<std::vector<std::shared_ptr<i_movement> > > > replacements)
			{
				rewriting_forest_->add_rule(sequence, replacements);
			}

			void decision_forest::add_rewriting_rule(
					std::shared_ptr<decision_value<i_movement, std::vector<std::vector<std::shared_ptr<i_movement> > > > > rule)
			{
				rewriting_forest_->add_rule(rule);
			}

			std::list<std::shared_ptr<laban_sequence> > decision_forest::get_sequences() const
			{
				return sequences_;
			}

			std::vector<std::shared_ptr<decision_value<i_movement, laban_sequence> > > decision_forest::get_sequences_with_empty_column_at(
					int body_part)
			{
				std::vector<std::shared_ptr<decision_value<i_movement, laban_sequence> > > tmp_seqs;

				//search for sequences that have this column empty (they are possible matches)
				for (std::list<std::shared_ptr<laban_sequence> >::iterator it = sequences_.begin();
						it != sequences_.end(); it++)
				{
					if (recreated_sequences_map_.find(*it) != recreated_sequences_map_.end())
					{
						std::shared_ptr<laban_sequence> recreated_sequence = recreated_sequences_map_.at(*it);
						if (recreated_sequence->get_column_movements(body_part).size() == 0)
						{
							//append sequence if cooldown is deactivated or sequence is not listed in the cooldown map
							if (!cooldown_ || cooldown_set_.find(*it) == cooldown_set_.end())
							{
								tmp_seqs.push_back(
										std::shared_ptr<decision_value<i_movement, laban_sequence> >(
												new decision_value<i_movement, laban_sequence>(
														recreated_sequence->get_column_movements(body_part), *it)));
							}
						}
					}
				}
				return tmp_seqs;
			}

			std::vector<std::shared_ptr<laban_sequence> > decision_forest::find_submatches(double framerate,
					std::shared_ptr<laban_sequence> whole_sequence, std::vector<bone> body_parts)
			{

				if (cooldown_)
				{
					update_cooldown_next_frame(whole_sequence, body_parts);
				}

				std::vector<std::shared_ptr<laban_sequence> > result;
				for (unsigned int i = 0; i < body_parts.size(); i++)
				{
					//process all body parts
					int body_part = body_parts.at(i).get_id();

					std::vector<std::shared_ptr<i_movement> > column_sequence = whole_sequence->get_column_movements(
							body_part);

					//get sequences that have the column empty. they are potential matches
					std::vector<std::shared_ptr<decision_value<i_movement, laban_sequence> > > tmp_seqs =
							get_sequences_with_empty_column_at(body_part);

					if (column_sequence.size() != 0)
					{
						//column sequence is not empty therefore search the tree which has a match with the last item of the sequence
						std::shared_ptr<i_movement> decision_item = column_sequence.back();
						std::vector<std::shared_ptr<decision_tree<i_movement, laban_sequence> > > tree_list;

						//actual distance to the last movement of the sequence (whole sequence's last movement does the trick since the recognition is live)
						double real_dist_to_last = distance_to_last(whole_sequence->get_last_movement(), decision_item);

						//process all trees
						if (trees_.find(body_part) != trees_.end())
						{
							tree_list = trees_.at(body_part);
						}

						for (unsigned int j = 0; j < tree_list.size(); j++)
						{
							//find matching tree(s)
							if (tree_list.at(j)->is_root_matching(decision_item))
							{
								//find submatches in reverse order

								std::vector<std::shared_ptr<decision_value<i_movement, laban_sequence> > > submatches =
										tree_list.at(j)->find_submatches(column_sequence, 0, -1, true);

								for (unsigned int k = 0; k < submatches.size(); k++)
								{
									//get set distance for the submatch
									std::shared_ptr<laban_sequence> submatch_val = submatches.at(k)->get_value();
									std::shared_ptr<i_movement> submatch_back = submatches.at(k)->get_sequence().back();

									//the target distance to the last movement
									double set_dist_to_last = distance_to_last(submatch_val->get_last_movement(),
											submatch_back);

									//position check is supposed to take care, that distance is not in area but only min dist is ok
									bool check_startpose = (submatch_back->get_measure() == 0);

									if (decision_maker_->position_okay(real_dist_to_last, set_dist_to_last,
											check_startpose))
									{
										//append sequence if cooldown is deactivated or sequence is not listed in the cooldown map
										if (!cooldown_ || cooldown_set_.find(submatches.at(k)->get_value()) == cooldown_set_.end())
										{
											//append to tmp_seqs
											tmp_seqs.push_back(submatches.at(k));
										}
									}
								}
							}
						}
					}

					//create cut set with previous sequences if not the first body part processed
					if (result.size() == 0)
					{
						//first time for insertion therefore insert all
						for (unsigned int j = 0; j < tmp_seqs.size(); j++)
						{
							result.push_back(tmp_seqs.at(j)->get_value());
						}
					}
					else
					{
						//build cut set
						std::vector<std::shared_ptr<laban_sequence> > tmp_result;
						tmp_result.reserve(result.size());
						for (unsigned int j = 0; j < tmp_seqs.size(); j++)
						{
							for (unsigned int k = 0; k < result.size(); k++)
							{
								if (result.at(k) == tmp_seqs.at(j)->get_value())
								{
									tmp_result.push_back(result.at(k));
									continue;
								}
							}
						}
						result = tmp_result;
					}

					if (result.size() == 0)
					{
						//no match found therefore no further processing is done
						return std::vector<std::shared_ptr<laban_sequence> >();
					}

				}

				if (cooldown_)
				{
					update_cooldown_recognized(whole_sequence, body_parts, result);
				}

				return result;
			}

			void decision_forest::update_cooldown_next_frame(std::shared_ptr<laban_sequence> whole_sequence, std::vector<bone> body_parts)
			{
				std::vector<std::shared_ptr<laban_sequence> > to_remove;

				//check all sequences in the cooldown set for new movements
				for (std::unordered_set<std::shared_ptr<laban_sequence> >::iterator it =
								cooldown_set_.begin(); it != cooldown_set_.end(); it++)
				{
					std::shared_ptr<laban_sequence> cooldown_seq = *it;

					for (std::size_t i = 0; i < body_parts.size(); i++)
					{
						int column_id = body_parts.at(i).get_id();

						std::vector<std::shared_ptr<i_movement> > cooldown_column = cooldown_seq->get_column_movements(column_id);
						std::vector<std::shared_ptr<i_movement> > whole_sequence_column = whole_sequence->get_column_movements(column_id);

						if (cooldown_column.size() != 0)
						{
							if (whole_sequence_column.size() == 0 || !(cooldown_column.back()->symbol_equals(whole_sequence_column.back())))
							{
								to_remove.push_back(cooldown_seq);
							}
						}
					}
				}

				//remove all sequences that had a movement
				for (std::size_t i = 0; i < to_remove.size(); i++)
				{
					cooldown_set_.erase(to_remove.at(i));
				}
			}


			void decision_forest::update_cooldown_recognized(std::shared_ptr<laban_sequence> whole_sequence, std::vector<bone> body_parts, std::vector<std::shared_ptr<laban_sequence> > recognition)
			{
				for(std::size_t i = 0; i < recognition.size(); i++)
				{
					cooldown_set_.insert(recognition.at(i));
				}
			}


			double decision_forest::distance_to_last(std::shared_ptr<i_movement> overall_last_movement,
					std::shared_ptr<i_movement> column_last_movement) const
			{
				double result = 0.0;

				if (overall_last_movement->get_measure() > 0.0)
				{
					if (column_last_movement->get_measure() > 0.0)
					{
						result = (overall_last_movement->get_measure() * beats_per_measure_
								+ overall_last_movement->get_beat() + overall_last_movement->get_duration())
								- (column_last_movement->get_measure() * beats_per_measure_
										+ column_last_movement->get_beat() + column_last_movement->get_duration());
					}
					else
					{
						result = (overall_last_movement->get_measure() * beats_per_measure_
								+ overall_last_movement->get_beat() + overall_last_movement->get_duration())
								- beats_per_measure_;
					}
				}

				return result;
			}

			std::string decision_forest::str() const
			{
				std::stringstream sstr;

				sstr << "--DECISION FOREST--" << std::endl;

				std::vector<int> colids = column_ids_;
				std::sort(colids.begin(), colids.end());

				for (unsigned int i = 0; i < colids.size(); i++)
				{
					int column = colids.at(i);

					sstr << "::column " << column << std::endl << std::endl;

					if (trees_.find(column) != trees_.end())
					{
						std::vector<std::shared_ptr<decision_tree<i_movement, laban_sequence> > > col_trees = trees_.at(
								column);

						for (unsigned int j = 0; j < col_trees.size(); j++)
						{
							sstr << col_trees.at(j)->str() << std::endl;
						}
					}
					else
					{
						sstr << "no trees for this column!" << std::endl << std::endl;
					}
				}

				sstr << "--/DECISION FOREST/--" << std::endl;

				return sstr.str();
			}

		} // namespace laban
	} // namespace fl
} // namespace mae
