/*
 * e_area.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef E_AREA_HPP_
#define E_AREA_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "../../../mstr.hpp"

//global includes
#include <string>
#include <vector>
#include <stdexcept>

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{

				enum class e_area
				{
						NONE,
						HEAD,
						CHEST,
						WAIST,
						PELVIS,
						TORSO
				};

				class e_area_c
				{
					public:
						/**
						 * Returns the string representation for this enum value.
						 *
						 * @param area The element.
						 * @return The string representation.
						 */
						static std::string str(e_area area);

						/**
						 * Returns a vector containing all possible enum values.
						 *
						 * @return A vector.
						 */
						static std::vector<e_area> vec();

						/**
						 * Parses the string and returns the corresponding element.
						 *
						 * @param str The string to be parsed.
						 * @return The element.
						 */
						static e_area parse(std::string str);
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_AREA_HPP_
