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
			static bool parse(std::string str);
			static std::string str(bool value);
	};

} // namespace mae

#endif // MBOOL_HPP_
