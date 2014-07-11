/*
 * e_level.cpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#include "e_level.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{
				std::string e_level_str::str(e_level level)
				{
					switch (level)
					{
					case e_level::NONE 		: return "none";
					case e_level::HIGH  		: return "high";
					case e_level::MIDDLE		: return "middle";
					case e_level::LOW    		: return "low";
					}

					throw std::invalid_argument("Enum value not listed in the str() method");
				}



			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
