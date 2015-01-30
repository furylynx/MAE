/*
 * i_decision_maker.hpp
 *
 *  Created on: 12.08.2014
 *      Author: keks
 */

#ifndef I_DECISION_MAKER_HPP_
#define I_DECISION_MAKER_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes

//global includes
#include <memory>
#include <stdexcept>


namespace mae
{
	namespace fl
	{
		namespace laban
		{

			template <typename T>
			class i_decision_maker
			{
				public:
					virtual ~i_decision_maker(){}

					/**
					 * Sets the tolerance for the recognition. The tolerance is a value which represents the
					 * number of beats of the labanotation which are tolerated in deviation.
					 *
					 * @param tolerance The tolerance to be accepted.
					 */
					virtual void set_recognition_tolerance(double tolerance) = 0;

					/**
					 * Returns the tolerance for the recognition. The tolerance is a value which represents the
					 * number of beats of the labanotation which are tolerated in deviation.
					 *
					 * @return The tolerance.
					 */
					virtual double get_recognition_tolerance() = 0;

					/**
					 * Checks whether the two elements match in order to provide the decision result for a match. Their
					 * predecessors are provided in order to make more complex decisions.
					 *
					 * @param stream_item The element for the sequence to be matched.
					 * @param stream_item_predecessor The predecessor element for the sequence to be matched.
					 * @param tree_item The decision tree's element.
					 * @param tree_item_predecessor The predecessor of the decision tree's element.
					 * @return True if elements match.
					 */
					virtual bool decide_match(std::shared_ptr<T> stream_item, std::shared_ptr<T> stream_item_predecessor, std::shared_ptr<T> tree_item, std::shared_ptr<T> tree_item_predecessor) = 0;

					/**
					 * Checks whether the two elements match in order to provide the decision result for an insertion. Their
					 * predecessors are provided in order to make more complex decisions.
					 *
					 * @param stream_item The element for the sequence to be added.
					 * @param stream_item_predecessor The predecessor element for the sequence to be added.
					 * @param tree_item The decision tree's element.
					 * @param tree_item_predecessor The predecessor of the decision tree's element.
					 * @return
					 */
					virtual bool decide_insertion(std::shared_ptr<T> add_item, std::shared_ptr<T> add_item_predecessor, std::shared_ptr<T> tree_item, std::shared_ptr<T> tree_item_predecessor) = 0;

					/**
					 * Checks the distances of the last element in this column to the last element of all columns. The method takes
					 * care of start poses on the set value side, so that only minimum distance must match and not an interval.
					 *
					 * @param dist_to_last The distance to the last element of all columns.
					 * @param set_value The set value for the distance.
					 * @param check_startpose True if set value is to start pose but dist is not.
					 * @return True if accepted.
					 */
					virtual bool position_okay(double dist_to_last, double set_value, bool check_startpose) = 0;
			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // I_DECISION_MAKER_HPP_
