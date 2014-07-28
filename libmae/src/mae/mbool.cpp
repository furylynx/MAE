/*
 * mbool.cpp
 *
 *  Created on: 28.07.2014
 *      Author: keks
 */

#include "mbool.hpp"

namespace mae
{

	bool mbool::parse(std::string str)
	{
		std::string str_l = mstr::to_lower(str);
	    std::stringstream sstr;
	    sstr << str;
	    bool result;
	    sstr >> std::boolalpha >> result;
	    return result;
	}

	std::string mbool::str(bool value)
	{
		std::stringstream sstr;
		sstr << std::boolalpha << value;
		return sstr.str();
	}

} // namespace mae
