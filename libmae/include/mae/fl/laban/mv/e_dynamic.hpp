/*
 * e_dynamic.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef E_DYNAMIC_HPP_
#define E_DYNAMIC_HPP_

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

				enum class e_dynamic : int
				{
						NONE_DYNAMIC,
						STRONG,
						GENTLE,
						EMPHASIZED,
						RELAXED,
						LIMP,
						UNEMPHASIZED,
						RESILIENT,
						VERY_RESILIENT
				};

				class e_dynamic_c
				{
					public:
						/**
						 * Returns the string representation for this enum value.
						 *
						 * @param dynamic The element.
						 * @return The string representation.
						 */
						static std::string str(e_dynamic dynamic);

						/**
						 * Returns a vector containing all possible enum values.
						 *
						 * @return A vector.
						 */
						static std::vector<e_dynamic> vec();

						/**
						 * Parses the string and returns the corresponding element.
						 *
						 * @param str The string to be parsed.
						 * @return The element.
						 */
						static e_dynamic parse(std::string str);

				};


			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_DYNAMIC_HPP_
