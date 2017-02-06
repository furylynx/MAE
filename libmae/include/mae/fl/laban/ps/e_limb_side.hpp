/*
 * e_limb_side.h
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef E_LIMB_SIDE_H_
#define E_LIMB_SIDE_H_

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

				enum class e_limb_side : int
				{
						NONE_LIMB_SIDE,
						INNER,
						OUTER,
						LITTLEFINGER,
						THUMB,
						OUTERLITTLEFINGER,
						INNERLITTLEFINGER,
						OUTERTHUMB,
						INNERTHUMB
				};

				class e_limb_side_c
				{
					public:
						/**
						 * Returns the string representation for this enum value.
						 *
						 * @param lside The element.
						 * @return The string representation.
						 */
						static std::string str(e_limb_side lside);

						/**
						 * Returns a vector containing all possible enum values.
						 *
						 * @return A vector.
						 */
						static std::vector<e_limb_side> vec();

						/**
						 * Parses the string and returns the corresponding element.
						 *
						 * @param str The string to be parsed.
						 * @return The element.
						 */
						static e_limb_side parse(std::string str);
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_LIMB_SIDE_H_
