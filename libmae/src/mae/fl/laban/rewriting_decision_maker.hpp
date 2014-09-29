/*
 * rewriting_decision_maker.hpp
 *
 *  Created on: 20.08.2014
 *      Author: keks
 */

#ifndef REWRITING_DECISION_MAKER_HPP_
#define REWRITING_DECISION_MAKER_HPP_

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
//...


namespace mae
{
	namespace fl
	{
		namespace laban
		{

			class rewriting_decision_maker: public i_decision_maker<i_movement>
			{
				public:
					/**
					 * Creates a new rewriting decision maker which is used to decide whether two movements are equal
					 * for sequences that are meant to be replaced. Therefore the timing does not matter but only the symbols.
					 */
					rewriting_decision_maker();
					virtual ~rewriting_decision_maker();

					/**
					 * Sets the tolerance for the recognition. The tolerance is a value which represents the
					 * number of beats of the labanotation which are tolerated in deviation.
					 *
					 * @param tolerance The tolerance to be accepted.
					 */
					virtual void set_recognition_tolerance(double tolerance);

					/**
					 * Checks whether the two elements match in order to provide the decision result.
					 *
					 * @param a The first element.
					 * @param b The second element.
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
			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // REWRITING_DECISION_MAKER_HPP_
