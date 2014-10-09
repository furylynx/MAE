/*
 * e_limb.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef E_LIMB_HPP_
#define E_LIMB_HPP_

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
				enum class e_limb : int
				{
						NONE_LIMB,
						ARM,
						LEG,
						NECK,
						UPPER_ARM,
						LOWER_ARM,
						THIGH,
						LOWER_LEG
				};


				class e_limb_c
				{
					public:
						/**
						 * Returns the string representation for this enum value.
						 *
						 * @param limb The element.
						 * @return The string representation.
						 */
						static std::string str(e_limb limb);

						/**
						 * Returns a vector containing all possible enum values.
						 *
						 * @return A vector.
						 */
						static std::vector<e_limb> vec();

						/**
						 * Parses the string and returns the corresponding element.
						 *
						 * @param str The string to be parsed.
						 * @return The element.
						 */
						static e_limb parse(std::string str);
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_LIMB_HPP_
