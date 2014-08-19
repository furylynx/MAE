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

			bool rewriting_decision_maker::decide(std::shared_ptr<i_movement> a, std::shared_ptr<i_movement> b)
			{
				//check type equal
				std::shared_ptr<movement> a_mov;
				std::shared_ptr<movement> b_mov;
				std::shared_ptr<room_direction> a_rd;
				std::shared_ptr<room_direction> b_rd;
				std::shared_ptr<path> a_p;
				std::shared_ptr<path> b_p;

				if ((a_mov = std::dynamic_pointer_cast<movement>(a))
						&& (b_mov = std::dynamic_pointer_cast<movement>(b)))
				{
					if (a_mov->get_symbol()->equals(b_mov->get_symbol()))
					{
						return true;
					}
				}
				else if ((a_rd = std::dynamic_pointer_cast<room_direction>(a))
						&& (b_rd = std::dynamic_pointer_cast<room_direction>(b)))
				{
					if (a_rd->get_direction()->equals(b_rd->get_direction()))
					{
						return true;
					}
				}
				else if ((a_p = std::dynamic_pointer_cast<path>(a)) && (b_p = std::dynamic_pointer_cast<path>(b)))
				{
					if (a_p->get_type() == b_p->get_type())
					{
						return true;
					}
				}

				return false;

			}

			bool rewriting_decision_maker::distance_okay(std::shared_ptr<i_movement> dist_from, std::shared_ptr<i_movement> dist_to, std::shared_ptr<i_movement> check)
			{
				return true;
			}

		} // namespace laban
	} // namespace fl
} // namespace mae
