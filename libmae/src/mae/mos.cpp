/*
 * mos.cpp
 *
 *  Created on: 19.09.2014
 *      Author: keks
 */

#include "mos.hpp"

namespace mae
{

	char mos::path_separator()
	{
	#ifdef _WIN32
		return '\\';
	#else
		return '/';
	#endif
	}
} // namespace mae
