/*
 * e_side.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef E_SIDE_HPP_
#define E_SIDE_HPP_

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
			namespace ps
			{

				enum class e_side : int
				{
						NONE,
						LEFT,
						RIGHT
				};

				class e_side_c
				{
					public:
						/**
						 * Returns the string representation for this enum value.
						 *
						 * @param side The element.
						 * @return The string representation.
						 */
						static std::string str(e_side side);

						/**
						 * Returns a vector containing all possible enum values.
						 *
						 * @return A vector.
						 */
						static std::vector<e_side> vec();

						/**
						 * Parses the string and returns the corresponding element.
						 *
						 * @param str The string to be parsed.
						 * @return The element.
						 */
						static e_side parse(std::string vec);
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_SIDE_HPP_
