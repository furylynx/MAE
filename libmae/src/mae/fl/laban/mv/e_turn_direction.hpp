/*
 * e_turn_direction.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef E_TURN_DIRECTION_HPP_
#define E_TURN_DIRECTION_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "../../../mstr.hpp"

//global includes
#include <string>
#include <stdexcept>
#include <vector>

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				enum class e_turn_direction : int
				{
						NONE,
						COUNTER_CLOCKWISE,
						CLOCKWISE,
						ANY
				};

				class e_turn_direction_c
				{
					public:
						/**
						 * Returns the string representation for this enum value.
						 *
						 * @param turn The element.
						 * @return The string representation.
						 */
						static std::string str(e_turn_direction turn);

						/**
						 * Returns a vector containing all possible enum values.
						 *
						 * @return A vector.
						 */
						static std::vector<e_turn_direction> vec();

						/**
						 * Parses the string and returns the corresponding element.
						 *
						 * @param str The string to be parsed.
						 * @return The element.
						 */
						static e_turn_direction parse(std::string str);
				};


			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_TURN_DIRECTION_HPP_
