/*
 * decision_forest.cpp
 *
 *  Created on: 12.08.2014
 *      Author: keks
 */

#include "decision_forest.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			decision_forest::decision_forest(std::vector<std::shared_ptr<column_definition> > column_definitions, std::vector<int> reserved_columns, unsigned int beats_per_measure, unsigned int beat_duration, e_time_unit time_unit, std::shared_ptr<i_decision_maker<i_movement> > dec_maker)
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

				if (decision_maker != nullptr)
				{
					decision_maker_ = decision_maker;
				}
				else
				{
					decision_maker_ = std::shared_ptr<i_decision_maker<i_movement> >(new decision_maker(beats_per_measure_));
				}

			}

			decision_forest::~decision_forest()
			{
			}

			void decision_forest::add_sequence(std::shared_ptr<laban_sequence> sequence)
			{
				//TODO insert not only the sequence but all rewritten sequences


				for (unsigned int i = 0; i < column_ids_.size(); i++)
				{
					int column = column_ids_.at(i);

					std::shared_ptr<i_movement> decision_item = sequence->get_column_movements(column).back();

					std::vector<std::shared_ptr<decision_tree<i_movement, laban_sequence> > > tree_list;
					bool listed = false;

					if (trees_.find(column) != trees_.end())
					{
						tree_list = trees_.at(column);

						for (unsigned int j = 0; j < tree_list.size(); j++)
						{
							if (decision_maker_->decide(decision_item,
									tree_list.at(j)->get_root()->get_decision_item()))
							{
								tree_list.at(j)->add_sequence(
										std::shared_ptr<decision_value<i_movement, laban_sequence> >(
												new decision_value<i_movement, laban_sequence>(
														sequence->get_column_movements(column), sequence)));
								listed = true;
								break;
							}
						}
					}

					if (!listed)
					{
						tree_list.push_back(
								std::shared_ptr<decision_tree<i_movement, laban_sequence> >(
										new decision_tree<i_movement, laban_sequence>(decision_maker_)));
						tree_list.back()->add_sequence(
								std::shared_ptr<decision_value<i_movement, laban_sequence> >(
										new decision_value<i_movement, laban_sequence>(
												sequence->get_column_movements(column), sequence)));

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

			std::vector<std::shared_ptr<laban_sequence> > decision_forest::find_submatches(
					std::shared_ptr<laban_sequence> whole_sequence)
			{
				std::vector<std::shared_ptr<laban_sequence> > result;

				for (unsigned int i = 0; i < column_ids_.size(); i++)
				{
					int body_part = column_ids_.at(i);

					std::shared_ptr<i_movement> decision_item = whole_sequence->get_column_movements(body_part).back();

					std::vector<std::shared_ptr<decision_tree<i_movement, laban_sequence> > > tree_list = trees_.at(
							body_part);

					std::vector<std::shared_ptr<decision_value<i_movement, laban_sequence> > > tmp_seqs;

					for (unsigned int j = 0; j < tree_list.size(); j++)
					{
						if (decision_maker_->decide(decision_item, tree_list.at(j)->get_root()->get_decision_item()))
						{
							tmp_seqs = tree_list.at(j)->find_submatches(
									whole_sequence->get_column_movements(body_part));
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
