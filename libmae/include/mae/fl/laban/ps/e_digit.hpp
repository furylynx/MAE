/*
 * e_digit.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef E_DIGIT_HPP_
#define E_DIGIT_HPP_

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

				enum class e_digit : int
				{
						NONE_DIGIT,
						THUMB,
						INDEXFINGER,
						MIDDLEFINGER,
						RINGFINGER,
						LITTLEFINGER,
						BIGTOE,
						LONGTOE,
						MIDDLETOE,
						RINGTOE,
						LITTLETOE
				};

				class e_digit_c
				{
					public:
						/**
						 * Returns the string representation for this enum value.
						 *
						 * @param digit The element.
						 * @return The string representation.
						 */
						static std::string str(e_digit digit);

						/**
						 * Returns a vector containing all possible enum values.
						 *
						 * @return A vector.
						 */
						static std::vector<e_digit> vec();

						/**
						 * Parses the string and returns the corresponding element.
						 *
						 * @param str The string to be parsed.
						 * @return The element.
						 */
						static e_digit parse(std::string str);
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_DIGIT_HPP_
