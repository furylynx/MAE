/*
 * decision_tree.cpp
 *
 *  Created on: 12.08.2014
 *      Author: keks
 */

#include "decision_tree.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			decision_tree::decision_tree(int body_part, std::shared_ptr<i_decision_maker> decision_maker)
			{
				body_part_ = body_part;
				decision_maker_ = decision_maker;

				if (decision_maker_ == nullptr)
				{
					throw std::invalid_argument("Decision maker must not be null.");
				}
			}

			decision_tree::~decision_tree()
			{
			}

			std::shared_ptr<decision_node> decision_tree::get_root()
			{
				return root_;
			}

			void decision_tree::add_sequence(std::shared_ptr<laban_sequence> sequence)
			{
				std::shared_ptr<i_movement> back = sequence->get_column_movements(body_part_).back();

				if (root_ == nullptr)
				{
					root_ = std::shared_ptr<decision_node>(new decision_node(body_part_, decision_maker_, back));

					root_->add_sequence(sequence, 0);
				}
				else
				{
					if (decision_maker_->decide(back, root_->get_decision_item()))
					{
						root_->add_sequence(sequence, 0);
					}
				}

			}

			std::vector<std::shared_ptr<laban_sequence> > decision_tree::find_submatches(
					std::shared_ptr<laban_sequence> whole_sequence)
			{
				if (root_ == nullptr
						|| !decision_maker_->decide(root_->get_decision_item(),
								whole_sequence->get_column_movements(body_part_).back()))
				{
					return nullptr;
				}
				else
				{
					return root_->find_submatches(whole_sequence, 0);
				}
			}

		} // namespace laban
	} // namespace fl
} // namespace mae
