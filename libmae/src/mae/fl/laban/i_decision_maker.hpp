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
					 * Checks whether the two elements match in order to provide the decision result.
					 *
					 * @param a The first element.
					 * @param b The second element.
					 * @return True if elements match.
					 */
					virtual bool decide(std::shared_ptr<T> a, std::shared_ptr<T> b);

					/**
					 * Checks the distance between the first to parameters and then examines whether the third parameter is okay.
					 *
					 * @param dist_from The distance from.
					 * @param dist_to The distance to.
					 * @param check The element to be checked to have enough distance.
					 * @return True if distance is okay.
					 */
					virtual bool distance_okay(std::shared_ptr<T> dist_from, std::shared_ptr<T> dist_to, std::shared_ptr<T> check);
			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // I_DECISION_MAKER_HPP_
