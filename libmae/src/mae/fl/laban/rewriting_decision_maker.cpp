/*
 * rewriting_decision_maker.cpp
 *
 *  Created on: 20.08.2014
 *      Author: keks
 */

#include "rewriting_decision_maker.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			rewriting_decision_maker::rewriting_decision_maker()
			{
			}

			rewriting_decision_maker::~rewriting_decision_maker()
			{
			}

			void rewriting_decision_maker::set_recognition_tolerance(double tolerance)
			{
				//do nothing
			}

			double rewriting_decision_maker::get_recognition_tolerance()
			{
				return 0.0;
			}

			bool rewriting_decision_maker::decide_match(std::shared_ptr<i_movement> stream_item, std::shared_ptr<i_movement> stream_item_predecessor, std::shared_ptr<i_movement> tree_item, std::shared_ptr<i_movement> tree_item_predecessor)
			{
				return check_type(stream_item, tree_item);
			}

			bool rewriting_decision_maker::decide_insertion(std::shared_ptr<i_movement> add_item, std::shared_ptr<i_movement> add_item_predecessor, std::shared_ptr<i_movement> tree_item, std::shared_ptr<i_movement> tree_item_predecessor)
			{
				return check_type(add_item, tree_item);
			}

			bool rewriting_decision_maker::check_type(std::shared_ptr<i_movement> a, std::shared_ptr<i_movement> b)
			{
				//check type equal
				std::shared_ptr<movement> a_mov;
				std::shared_ptr<movement> b_mov;
				std::shared_ptr<room_direction> a_rd;
				std::shared_ptr<room_direction> b_rd;
				std::shared_ptr<path> a_p;
				std::shared_ptr<path> b_p;
				std::shared_ptr<relationship_bow> a_rb;
				std::shared_ptr<relationship_bow> b_rb;

				if ((a_mov = std::dynamic_pointer_cast<movement>(a))
						&& (b_mov = std::dynamic_pointer_cast<movement>(b)))
				{

					if (a_mov->get_symbol()->equals(b_mov->get_symbol()) && a_mov->get_hold() == b_mov->get_hold()
							&& ((a_mov->get_pre_sign() == nullptr && b_mov->get_pre_sign() == nullptr)
									|| (a_mov->get_pre_sign() != nullptr
											&& a_mov->get_pre_sign()->equals(b_mov->get_pre_sign()))))
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else if ((a_rd = std::dynamic_pointer_cast<room_direction>(a)) && (b_rd =
						std::dynamic_pointer_cast<room_direction>(b)))
				{
					if (a_rd->get_direction()->equals(b_rd->get_direction()))
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else if ((a_p = std::dynamic_pointer_cast<path>(a))
						&& (b_p = std::dynamic_pointer_cast<path>(b)))
				{
					if (a_p->get_type() == b_p->get_type())
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else if ((a_rb = std::dynamic_pointer_cast<relationship_bow>(a)) && (b_rb =
						std::dynamic_pointer_cast<relationship_bow>(b)))
				{
					if (a_rb->get_type() == b_rb->get_type() && a_rb->get_grasping() == b_rb->get_grasping()
							&& a_rb->get_passing() == b_rb->get_passing() && a_rb->get_hold() == b_rb->get_hold()
							&& a_rb->get_left_endpoint()->equals(b_rb->get_left_endpoint())
							&& a_rb->get_right_endpoint()->equals(b_rb->get_right_endpoint()))
					{
						return true;
					}
					else
					{
						return false;
					}
				}

				return false;
			}

			bool rewriting_decision_maker::position_okay(double dist_to_last, double set_value, bool check_startpose)
			{
				return true;
			}

		} // namespace laban
	} // namespace fl
} // namespace mae
