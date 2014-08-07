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

			decision_forest::decision_forest(std::vector<int> body_parts,
					std::shared_ptr<i_decision_maker> decision_maker)
			{
				body_parts_ = body_parts;
				decision_maker_ = decision_maker;
			}

			decision_forest::~decision_forest()
			{
			}

			void decision_forest::add_sequence(std::shared_ptr<laban_sequence> sequence)
			{
				for (unsigned int i = 0; i < body_parts_.size(); i++)
				{
					int body_part = body_parts_.at(i);

					std::shared_ptr<i_movement> decision_item = sequence->get_column_movements(body_part).back();

					std::vector<std::shared_ptr<decision_tree> > tree_list;
					bool listed = false;

					if (trees_.find(body_part) != trees_.end())
					{
						tree_list = trees_.at(body_part);

						for (unsigned int j = 0; j < tree_list.size(); j++)
						{
							if (decision_maker_->decide(decision_item,
									tree_list.at(j)->get_root()->get_decision_item()))
							{
								tree_list.at(j)->add_sequence(sequence);
								listed = true;
								break;
							}
						}
					}

					if (!listed)
					{
						tree_list.push_back(
								std::shared_ptr<decision_tree>(new decision_tree(body_part, decision_maker_)));
						tree_list.back()->add_sequence(sequence);

						if (trees_.find(body_part) != trees_.end())
						{
							trees_[body_part] = tree_list;
						}
						else
						{
							trees_.insert(std::make_pair(body_part, tree_list));
						}
					}

				}
			}

			std::vector<std::shared_ptr<laban_sequence> > decision_forest::find_submatches(
					std::shared_ptr<laban_sequence> whole_sequence)
			{
				std::vector<std::shared_ptr<laban_sequence> > result;

				for (unsigned int i = 0; i < body_parts_.size(); i++)
				{
					int body_part = body_parts_.at(i);

					std::shared_ptr<i_movement> decision_item = whole_sequence->get_column_movements(body_part).back();

					std::vector<std::shared_ptr<decision_tree> > tree_list = trees_.at(body_part);

					std::vector<std::shared_ptr<laban_sequence> > tmp_seqs;

					for (unsigned int j = 0; j < tree_list.size(); j++)
					{
						if (decision_maker_->decide(decision_item, tree_list.at(j)->get_root()->get_decision_item()))
						{
							tmp_seqs = tree_list.at(j)->find_submatches(whole_sequence);
						}
					}

					if (i == 0)
					{
						result = tmp_seqs;
					}
					else
					{
						std::vector<std::shared_ptr<laban_sequence> > tmp_result;
						tmp_result.reserve(result.size());

						for (unsigned int j = 0; j < tmp_seqs.size(); j++)
						{
							for (unsigned int k = 0; k < result.size(); k++)
							{
								if (result.at(k) == tmp_seqs.at(j))
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
