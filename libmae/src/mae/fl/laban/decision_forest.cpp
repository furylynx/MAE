/*
 * decision_forest.cpp
 *
 * Created on: 12.08.2014
 * Author: keks
 */
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
					std::shared_ptr<rewriting_forest> rw)
			{
				column_definitions_ = column_definitions;
				beats_per_measure_ = beats_per_measure;
				beat_duration_ = beat_duration;
				time_unit_ = time_unit;
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

			void decision_forest::add_sequence(std::shared_ptr<laban_sequence> sequence)
			{
				//TODO check column definitions

				//add to list for later removal by index
				sequences_.push_back(sequence);

				for (unsigned int i = 0; i < column_ids_.size(); i++)
				{
					int column = column_ids_.at(i);
					std::vector<std::shared_ptr<decision_tree<i_movement, laban_sequence> > > tree_list;

					//insert not only the sequence but all rewritten sequences
					std::vector<std::vector<std::shared_ptr<i_movement> > > all_subsequences =
							rewriting_forest_->replacements(sequence->get_column_movements(column));

					for (unsigned int k = 0; k < all_subsequences.size(); k++)
					{
						std::vector<std::shared_ptr< i_movement> > subsequence = all_subsequences.at(k);
						bool listed = false;
						std::shared_ptr<i_movement> decision_item = subsequence.back();

						if (trees_.find(column) != trees_.end())
						{
							//search for a matching tree (which means that the root's decision element compares equal to the last element of the subsequence
							tree_list = trees_.at(column);
							for (unsigned int j = 0; j < tree_list.size(); j++)
							{
								if (decision_maker_->decide(decision_item, nullptr,
										tree_list.at(j)->get_root()->get_decision_item(), nullptr))
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
				int index = 0;
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
				//remove sequence from all trees
				for (unsigned int i = 0; i < column_ids_.size(); i++)
				{
					int column_id = column_ids_.at(i);
					if (trees_.find(column_id) != trees_.end())
					{
						std::vector<std::shared_ptr<decision_tree<i_movement, laban_sequence> > > trees_vec = trees_.at(
								column_id);
						for (unsigned int j = 0; j < trees_vec.size(); j++)
						{
							trees_vec.at(j)->remove_where(sequence);
						}
					}
				}
				return false;
			}

			void decision_forest::clear()
			{
				trees_.clear();
				sequences_.clear();
			}

			std::list<std::shared_ptr<laban_sequence> > decision_forest::get_sequences()
			{
				return sequences_;
			}

			std::vector<std::shared_ptr<laban_sequence> > decision_forest::find_submatches(
					std::shared_ptr<laban_sequence> whole_sequence, std::vector<bone> body_parts)
			{
				std::vector<std::shared_ptr<laban_sequence> > result;
				for (unsigned int i = 0; i < body_parts.size(); i++)
				{
					int body_part = body_parts.at(i).get_id();
					std::shared_ptr<i_movement> decision_item = whole_sequence->get_column_movements(body_part).back();
					std::vector<std::shared_ptr<decision_tree<i_movement, laban_sequence> > > tree_list = trees_.at(
							body_part);
					std::vector<std::shared_ptr<decision_value<i_movement, laban_sequence> > > tmp_seqs;
					for (unsigned int j = 0; j < tree_list.size(); j++)
					{
						if (decision_maker_->decide(decision_item, nullptr, tree_list.at(j)->get_root()->get_decision_item(), nullptr))
						{
							//find submatches in reverse order
							tmp_seqs = tree_list.at(j)->find_submatches(
									whole_sequence->get_column_movements(body_part), 0, -1, true);
						}
					}
					if (i == 0)
					{
						for (unsigned int j = 0; j < tmp_seqs.size(); j++)
						{
							result.push_back(tmp_seqs.at(j)->get_value());
						}
					}
					else
					{
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
				}
				return result;
			}
		} // namespace laban
	} // namespace fl
} // namespace mae
