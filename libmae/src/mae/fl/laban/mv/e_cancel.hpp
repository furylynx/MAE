/*
 * e_cancel.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef E_CANCEL_HPP_
#define E_CANCEL_HPP_

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

				enum class e_cancel
				{
						NONE,
						BACK_NORMAL,
						RELEASE_CONTACT
				};

				class e_cancel_c
				{
					public:
						/**
						 * Returns the string representation for this enum value.
						 *
						 * @param cancel The element.
						 * @return The string representation.
						 */
						static std::string str(e_cancel cancel);

						/**
						 * Returns a vector containing all possible enum values.
						 *
						 * @return A vector.
						 */
						static std::vector<e_cancel> vec();

						/**
						 * Parses the string and returns the corresponding element.
						 *
						 * @param str The string to be parsed.
						 * @return The element.
						 */
						static e_cancel parse(std::string str);

				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_CANCEL_HPP_
