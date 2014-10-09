/*
 * e_contact_hook.hpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#ifndef E_CONTACT_HOOK_HPP_
#define E_CONTACT_HOOK_HPP_

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

				enum class e_contact_hook : int
				{
						NONE,
						NAIL,
						TIP,
						PAD,
						BALL,
						HALF_BALL,
						QUARTER_BALL,
						FOOT,
						HALF_HEEL,
						QUARTER_HEEL,
						FULL_HEEL,
						FULL_BALL
				};

				class e_contact_hook_c
				{
					public:
						/**
						 * Returns the string representation for this enum value.
						 *
						 * @param hook The element.
						 * @return The string representation.
						 */
						static std::string str(e_contact_hook hook);

						/**
						 * Returns a vector containing all possible enum values.
						 *
						 * @return A vector.
						 */
						static std::vector<e_contact_hook> vec();

						/**
						 * Parses the string and returns the corresponding element.
						 *
						 * @param str The string to be parsed.
						 * @return The element.
						 */
						static e_contact_hook parse(std::string str);

				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_CONTACT_HOOK_HPP_
