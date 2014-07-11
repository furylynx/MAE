/*
 * e_limb_side.cpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#include "e_limb_side.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{
				std::string e_limb_side_str::str(e_limb_side lside)
				{
					switch (lside)
					{
					case e_limb_side::NONE             		: return "none";
					case e_limb_side::INNER            		: return "inner";
					case e_limb_side::OUTER            		: return "outer";
					case e_limb_side::LITTLEFINGER     		: return "littleFinger";
					case e_limb_side::THUMB            		: return "thumb";
					case e_limb_side::OUTERLITTLEFINGER		: return "outer-littleFinger";
					case e_limb_side::INNERLITTLEFINGER		: return "inner-littleFinger";
					case e_limb_side::OUTERTHUMB       		: return "outer-thumb";
					case e_limb_side::INNERTHUMB        	: return "inner-thumb";
					}
				}
			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae
