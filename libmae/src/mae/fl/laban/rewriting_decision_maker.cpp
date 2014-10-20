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
				return a->symbol_equals(b);
			}

			bool rewriting_decision_maker::position_okay(double dist_to_last, double set_value, bool check_startpose)
			{
				return true;
			}

		} // namespace laban
	} // namespace fl
} // namespace mae
