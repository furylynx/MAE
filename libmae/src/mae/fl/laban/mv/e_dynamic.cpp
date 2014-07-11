/*
 * e_dynamic.cpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#include "e_dynamic.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{
				std::string e_dynamic_str::str(e_dynamic dynamic)
				{
					switch (dynamic)
					{
					case e_dynamic::NONE 					: return "none";
					case e_dynamic::STRONG           		: return "strong";
					case e_dynamic::GENTLE           		: return "gentle";
					case e_dynamic::EMPHASIZED       		: return "emphasized";
					case e_dynamic::RELAXED          		: return "relaxed";
					case e_dynamic::LIMP            		: return "limp";
                    case e_dynamic::UNEMPHASIZED           	: return "unemphasized";
                    case e_dynamic::RESILIENT              	: return "resilient";
                    case e_dynamic::VERY_RESILIENT          : return "veryResilient";
					}

					throw std::invalid_argument("Enum value not listed in the str() method");

				}



			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
