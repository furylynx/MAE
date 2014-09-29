/*
 * decision_maker.hpp
 *
 *  Created on: 15.08.2014
 *      Author: keks
 */

#ifndef DECISION_MAKER_HPP_
#define DECISION_MAKER_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
#include "i_decision_maker.hpp"
#include "i_movement.hpp"
#include "movement.hpp"
#include "path.hpp"
#include "room_direction.hpp"
#include "relationship_bow.hpp"

//global includes
#include <iostream>
#include <string>


namespace mae
{
	namespace fl
	{
		namespace laban
		{

			class decision_maker: public i_decision_maker<i_movement>
			{
				public:
					/**
					 * Creates a new decision maker.
					 *
					 * @param beats_per_measure The number of beats per measure for the present sequence of which movements are compared.
					 * @param tolerance The tolerance to be applied. It is given in beats and defines how many beats are accepted in deviance.
					 */
					decision_maker(int beats_per_measure, double tolerance = 0.5);
					virtual ~decision_maker();

					/**
					 * Sets the tolerance for the recognition. The tolerance is a value which represents the
					 * number of beats of the labanotation which are tolerated in deviation.
					 *
					 * @param tolerance The tolerance to be accepted.
					 */
					virtual void set_recognition_tolerance(double tolerance);

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
					virtual bool decide(std::shared_ptr<i_movement> a, std::shared_ptr<i_movement> a_predecessor, std::shared_ptr<i_movement> b, std::shared_ptr<i_movement> b_predecessor);

					/**
					 * Checks the distance between the first to parameters and then examines whether the third parameter is okay.
					 *
					 * @param dist_from The distance from.
					 * @param dist_to The distance to.
					 * @param check The element to be checked to have enough distance.
					 * @return True if distance is okay.
					 */
					virtual bool distance_okay(std::shared_ptr<i_movement> dist_from, std::shared_ptr<i_movement> dist_to, std::shared_ptr<i_movement> check);

					/**
					 * Checks the distances of the last element in this column to the last element of all columns.
					 *
					 * @param dist_to_last The distance to the last element of all columns.
					 * @param set_value The set value for the distance.
					 * @return True if accepted.
					 */
					virtual bool position_okay(double dist_to_last, double set_value);

				private:
					int beats_per_measure_;

					double tolerance_;

			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // DECISION_MAKER_HPP_
