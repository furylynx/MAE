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

				// TODO generate trees etc...
				// TODO decision maker

			}

			rewriting_forest::~rewriting_forest()
			{
			}

			std::vector<std::vector<std::shared_ptr<i_movement> > > rewriting_forest::replacements(
					std::vector<std::shared_ptr<i_movement> > sequence)
			{
				std::vector<int> indices;

				std::vector<std::vector<std::shared_ptr<i_movement> > > result;
				result.push_back(sequence);
				indices.push_back(0);

				for (unsigned int i = 0; i < result.size(); i++)
				{
					int index = indices.at(i);

					//TODO check for continous sequence

					//find decision tree with same start pos
					for (unsigned int k = 0; k < trees_.size(); k++)
					{
						if (decision_maker_->decide(result.at(index).back(),
								trees_.at(k)->get_root()->get_decision_item()))
						{
							std::vector<
									std::shared_ptr<
											decision_value<i_movement,
													std::vector<std::vector<std::shared_ptr<i_movement> > > > > > replacement_values =
									trees_.at(k)->find_submatches(sequence, index);

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
						}
					}

				}

				//TODO handle replacements in here : use decision trees for this

				//check the whole sequence for continous movements (no break, same length) : index pos
				//check decision forest for matches for the continous subsequence
				//replace subsequences of continous subsequence from index pos to size of the match
				//this does replace the first match; any other match must be applied on all previous possible sequences
				//... big mess but must be done

				return result;
			}

			std::vector<std::shared_ptr<i_movement> > rewriting_forest::construct_replaced(
					std::vector<std::shared_ptr<i_movement> > sequence,
					std::vector<std::shared_ptr<i_movement> > replacement, int start_pos, unsigned int end_pos)
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

					//TODO continous movement
					unsigned int measure = (int) (((beats_replaced / replacement.size()) * i + start_beat)
							/ beats_per_measure_);
					double beat = ((beats_replaced / replacement.size()) * i + start_beat) / beats_per_measure_
							- measure;
					double duration = beats_replaced / replacement.size();

					if (std::shared_ptr<movement> rep_mov = std::dynamic_pointer_cast<movement>(rep))
					{

						std::shared_ptr<mv::i_symbol> symbol = rep_mov->get_symbol();
						bool hold = rep_mov->get_hold();
						movement = std::shared_ptr<i_movement>(
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
					std::vector<std::vector<std::shared_ptr<i_movement> > > replacements)
			{
				//TODO add rule to correct decision tree
			}

		} // namespace laban
	} // namespace fl
} // namespace mae
