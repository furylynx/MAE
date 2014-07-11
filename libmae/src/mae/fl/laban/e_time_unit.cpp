/*
 * e_time_unit.cpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#include "e_time_unit.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			std::string e_time_unit_str::str(e_time_unit unit)
			{
				switch (unit)
				{
				case e_time_unit::NONE           		: return "none";
				case e_time_unit::MINUTE    			: return "minute";
				case e_time_unit::SECOND    			: return "second";
                case e_time_unit::MILLISECOND        	: return "millisecond";
				}

				throw std::invalid_argument("Enum value not listed in the str() method");
			}

		} // namespace laban
	} // namespace fl
} // namespace mae
