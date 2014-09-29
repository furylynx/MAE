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
#include "i_movement.hpp"

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
					 * Checks whether the two elements match in order to provide the decision result. Their
					 * predecessors are provided in order to make more complex decisions.
					 *
					 * @param a The first element.
					 * @param a_predecessor The predecessor of a
					 * @param b The second element.
					 * @param b_predecessor The predecessor of b
					 * @return True if elements match.
					 */
					virtual bool decide(std::shared_ptr<T> a, std::shared_ptr<T> a_predecessor, std::shared_ptr<T> b, std::shared_ptr<T> b_predecessor) = 0;

					/**
					 * Checks the distance between the first to parameters and then examines whether the third parameter is okay.
					 *
					 * @param dist_from The distance from.
					 * @param dist_to The distance to.
					 * @param check The element to be checked to have enough distance.
					 * @return True if distance is okay.
					 */
					virtual bool distance_okay(std::shared_ptr<T> dist_from, std::shared_ptr<T> dist_to, std::shared_ptr<T> check) = 0;

					/**
					 * Checks the distances of the last element in this column to the last element of all columns.
					 *
					 * @param dist_to_last The distance to the last element of all columns.
					 * @param set_value The set value for the distance.
					 * @return True if accepted.
					 */
					virtual bool position_okay(double dist_to_last, double set_value) = 0;
			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // I_DECISION_MAKER_HPP_
