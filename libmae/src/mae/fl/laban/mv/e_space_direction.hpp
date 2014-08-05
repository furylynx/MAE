/*
 * e_space_direction.h
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef E_SPACE_DIRECTION_H_
#define E_SPACE_DIRECTION_H_

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

				enum class e_space_direction
				{
						NONE,
						LEFT,
						FRONT_LEFT,
						FRONT,
						FRONT_RIGHT,
						RIGHT,
						BACK_RIGHT,
						BACK,
						BACK_LEFT
				};

				class e_space_direction_c
				{
					public:
						/**
						 * Returns the string representation for this enum value.
						 *
						 * @param space_direction The element.
						 * @return The string representation.
						 */
						static std::string str(e_space_direction space_direction);

						/**
						 * Returns a vector containing all possible enum values.
						 *
						 * @return A vector.
						 */
						static std::vector<e_space_direction> vec();

						/**
						 * Parses the string and returns the corresponding element.
						 *
						 * @param str The string to be parsed.
						 * @return The element.
						 */
						static e_space_direction parse(std::string str);

				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_SPACE_DIRECTION_H_
