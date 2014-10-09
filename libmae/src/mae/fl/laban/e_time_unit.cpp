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
			std::string e_time_unit_c::str(e_time_unit unit)
			{
				switch (unit)
				{
				case e_time_unit::NONE_TIME_UNIT           		: return "none";
				case e_time_unit::MINUTE    			: return "minute";
				case e_time_unit::SECOND    			: return "second";
                case e_time_unit::MILLISECOND        	: return "millisecond";
				}

				throw std::invalid_argument("Enum value not listed in the str() method");
			}

			std::vector<e_time_unit> e_time_unit_c::vec()
			{
				std::vector<e_time_unit> result;
				result.push_back(e_time_unit::NONE_TIME_UNIT  		);
				result.push_back(e_time_unit::MINUTE       	);
				result.push_back(e_time_unit::SECOND      	);
				result.push_back(e_time_unit::MILLISECOND  	);

				return result;
			}

			e_time_unit e_time_unit_c::parse(std::string str)
			{
				std::string str_l = mstr::to_lower(str);

				std::vector<e_time_unit> v = e_time_unit_c::vec();

				for (unsigned int i = 0; i < v.size(); i++)
				{
					std::string t = e_time_unit_c::str(v.at(i));
					if (str_l == mstr::to_lower(t))
					{
						return v.at(i);
					}
				}

				throw std::invalid_argument("Could not parse the given value since no match was found.");
			}



		} // namespace laban
	} // namespace fl
} // namespace mae
