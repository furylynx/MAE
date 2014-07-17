/*
 * e_area.cpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#include "e_area.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{
				std::string e_area_c::str(e_area area)
				{
					switch (area)
					{
					case e_area::NONE 		: return "none";
					case e_area::HEAD 		: return "head";
					case e_area::CHEST		: return "chest";
					case e_area::WAIST		: return "waist";
					case e_area::PELVIS		: return "pelvis";
					case e_area::TORSO 		: return "torso";
					}

					throw std::invalid_argument("Enum value not listed in the str() method");
				}



			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae
