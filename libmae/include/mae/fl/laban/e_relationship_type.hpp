/*
 * e_relationship_type.hpp
 *
 *  Created on: 22.08.2014
 *      Author: keks
 */

#ifndef E_RELATIONSHIP_TYPE_HPP_
#define E_RELATIONSHIP_TYPE_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
#include "../../mstr.hpp"

//global includes
#include <vector>
#include <string>
#include <stdexcept>

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			enum class e_relationship_type : int
			{
					NONE_RELATIONSHIP_TYPE,
					ADDRESS,
					NEAR_RELATIONSHIP_TYPE,
					TOUCH,
					SUPPORT
			};

			class e_relationship_type_c
			{
				public:
					/**
					 * Returns the string representation for this enum value.
					 *
					 * @param type The element.
					 * @return The string representation.
					 */
					static std::string str(e_relationship_type type);

					/**
					 * Returns a vector containing all possible enum values.
					 *
					 * @return A vector.
					 */
					static std::vector<e_relationship_type> vec();

					/**
					 * Parses the string and returns the corresponding element.
					 *
					 * @param str The string to be parsed.
					 * @return The element.
					 */
					static e_relationship_type parse(std::string str);
			};
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_RELATIONSHIP_TYPE_HPP_
