/*
 * mbool.hpp
 *
 *  Created on: 28.07.2014
 *      Author: keks
 */

#ifndef MBOOL_HPP_
#define MBOOL_HPP_

//eclipse indexer fix
#include "indexer_fix.hpp"

//custom includes
#include "mstr.hpp"

//global includes
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>

namespace mae
{

	class mbool
	{
		public:
			/**
			 * Parses the string and returns the boolean value.
			 *
			 * @param str The string.
			 * @return The value.
			 */
			static bool parse(std::string str);

			/**
			 * Returns the string representation for the boolean, i.e. "true" or "false".
			 *
			 * @param value The boolean value.
			 * @return The string.
			 */
			static std::string str(bool value);
	};

} // namespace mae

#endif // MBOOL_HPP_
