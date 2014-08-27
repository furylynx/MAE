/*
 * rewriting_rules.cpp
 *
 *  Created on: 13.08.2014
 *      Author: keks
 */

#include "rewriting_forest.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			rewriting_forest::rewriting_forest(unsigned int beats_per_measure, unsigned int beat_duration,
					e_time_unit time_unit)
			{
				beats_per_measure_ = beats_per_measure;
				beat_duration_ = beat_duration;
				time_unit_ = time_unit;

				// decision maker
				decision_maker_ = std::shared_ptr<i_decision_maker<i_movement> >(new rewriting_decision_maker());
			}

			rewriting_forest::rewriting_forest(std::vector<std::shared_ptr<decision_value<i_movement, std::vector<std::vector<std::shared_ptr<i_movement> > > > > > rules, unsigned int beats_per_measure, unsigned int beat_duration, e_time_unit time_unit)
			{
				beats_per_measure_ = beats_per_measure;
				beat_duration_ = beat_duration;
				time_unit_ = time_unit;

				// decision maker
				decision_maker_ = std::shared_ptr<i_decision_maker<i_movement> >(new rewriting_decision_maker());

				for (unsigned int i = 0; i < rules.size(); i++)
				{
					add_rule(rules.at(i));
				}
			}

			rewriting_forest::~rewriting_forest()
			{
			}

			std::vector<std::vector<std::shared_ptr<i_movement> > > rewriting_forest::replacements(
					std::vector<std::shared_ptr<i_movement> > sequence)
			{
				//check the whole sequence for continous movements (no break, same length) : index pos
				//check decision forest for matches for the continous subsequence
				//replace subsequences of continous subsequence from index pos to size of the match
				//this does replace the first match; any other match must be applied on all previous possible sequences

				//TODO good value
				double deviation = 0.5;

				std::vector<int> indices;

				std::vector<std::vector<std::shared_ptr<i_movement> > > result;
				result.push_back(sequence);
				indices.push_back(0);

				for (unsigned int i = 0; i < result.size(); i++)
				{
					unsigned int end_index_cont = 0;
					for (unsigned int index = indices.at(i); index < result.at(i).size(); index++)
					{
						//check for continous sequence
						if (end_index_cont < index)
						{
							end_index_cont = index;
							for (unsigned int k = 1; index + k < result.at(i).size(); k++)
							{
								double last_beat_dur = result.at(i).at(index + k - 1)->get_measure()
										* beats_per_measure_ + result.at(i).at(index + k - 1)->get_beat()
										+ result.at(i).at(index + k - 1)->get_duration();
								double curr_beat = result.at(i).at(index + k)->get_measure() * beats_per_measure_
										+ result.at(i).at(index + k)->get_beat();

								if (std::abs(last_beat_dur - curr_beat) < deviation)
								{
									end_index_cont = index + k;
								}
								else
								{
									break;
								}
							}
						}

						if (index <= end_index_cont)
						{
							//no continous sequence, therefore increment index
							continue;
						}

						//find decision tree with same start pos
						for (unsigned int k = 0; k < trees_.size(); k++)
						{
							if (decision_maker_->decide(result.at(i).at(index), nullptr,
									trees_.at(k)->get_root()->get_decision_item(), nullptr))
							{
								//use end_index_cont for submatches
								std::vector<
										std::shared_ptr<
												decision_value<i_movement,
														std::vector<std::vector<std::shared_ptr<i_movement> > > > > > replacement_values =
										trees_.at(k)->find_submatches(sequence, index, end_index_cont);

								for (unsigned int l = 0; l < replacement_values.size(); l++)
								{
									for (unsigned int m = 0; m < replacement_values.at(l)->get_value()->size(); m++)
									{
										result.push_back(
												construct_replaced(result.at(i),
														replacement_values.at(l)->get_value()->at(m), index,
														replacement_values.at(l)->get_sequence().size()));

										indices.push_back(index + replacement_values.at(l)->get_value()->at(m).size());
									}
								}

								break;
							}
						}
					}

				}

				return result;
			}

			std::vector<std::shared_ptr<i_movement> > rewriting_forest::construct_replaced(
					std::vector<std::shared_ptr<i_movement> > sequence,
					std::vector<std::shared_ptr<i_movement> > replacement, unsigned int start_pos, unsigned int end_pos)
			{
				if (start_pos >= sequence.size() || end_pos >= sequence.size())
				{
					throw std::invalid_argument("start and end pos must be within the sequence.");
				}

				if (replacement.size() == 0)
				{
					//no changes to be applied
					return sequence;
				}

				std::vector<std::shared_ptr<i_movement> > result;

				for (unsigned int i = 0; i < start_pos; i++)
				{
					result.push_back(sequence.at(i));
				}

				//make continuous movement
				double beats_replaced = (sequence.at(end_pos)->get_measure() - sequence.at(start_pos)->get_measure())
						* beats_per_measure_
						+ (sequence.at(end_pos)->get_measure() - sequence.at(start_pos)->get_measure())
						+ sequence.at(end_pos)->get_duration();
				double start_beat = sequence.at(start_pos)->get_measure() * beats_per_measure_
						+ sequence.at(start_pos)->get_beat();

				for (unsigned int i = 0; i < replacement.size(); i++)
				{
					std::shared_ptr<i_movement> rep = replacement.at(i);

					std::shared_ptr<i_movement> i_mov;

					int column = sequence.at(start_pos)->get_column();

					//continous movement
					unsigned int measure = (int) (((beats_replaced / replacement.size()) * i + start_beat)
							/ beats_per_measure_);
					double beat = ((beats_replaced / replacement.size()) * i + start_beat) / beats_per_measure_
							- measure;
					double duration = beats_replaced / replacement.size();

					if (std::shared_ptr<movement> rep_mov = std::dynamic_pointer_cast<movement>(rep))
					{

						std::shared_ptr<mv::i_symbol> symbol = rep_mov->get_symbol();
						bool hold = rep_mov->get_hold();
						i_mov = std::shared_ptr<i_movement>(
								new movement(column, measure, beat, duration, symbol, hold));
					}
					else
					{
						//TODO handle other cases
					}

					result.push_back(i_mov);
				}

				for (unsigned int i = end_pos + 1; i < sequence.size(); i++)
				{
					result.push_back(sequence.at(i));
				}

				return result;
			}

			void rewriting_forest::add_rule(std::vector<std::shared_ptr<i_movement> > sequence,
					std::shared_ptr<std::vector<std::vector<std::shared_ptr<i_movement> > > > replacements)
			{

				add_rule(std::shared_ptr<decision_value<i_movement, std::vector<std::vector<std::shared_ptr<i_movement> > > > >(
						new decision_value<i_movement,
								std::vector<std::vector<std::shared_ptr<i_movement> > > >(sequence,
								replacements)));

			}

			void rewriting_forest::add_rule(std::shared_ptr<decision_value<i_movement, std::vector<std::vector<std::shared_ptr<i_movement> > > > > rule)
			{
				for (unsigned int k = 0; k < trees_.size(); k++)
				{
					if (decision_maker_->decide(rule->get_sequence().front(), nullptr, trees_.at(k)->get_root()->get_decision_item(), nullptr))
					{
						//add in normal order to tree
						trees_.at(k)->add_sequence(rule, false);

						return;
					}
				}

				//create a new tree
				trees_.push_back(
						std::shared_ptr<decision_tree<i_movement, std::vector<std::vector<std::shared_ptr<i_movement> > > > >(
								new decision_tree<i_movement, std::vector<std::vector<std::shared_ptr<i_movement> > > >(
										decision_maker_)));

				//add in normal order to tree
				trees_.back()->add_sequence(rule, false);

			}

		} // namespace laban
	} // namespace fl
} // namespace mae
