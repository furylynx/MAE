/*
 * e_limb.cpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#include "e_limb.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{
				std::string e_limb_str::str(e_limb limb)
				{
					switch (limb)
					{
					case e_limb::NONE     		: return "none";
					case e_limb::ARM      		: return "arm";
					case e_limb::LEG      		: return "leg";
					case e_limb::NECK     		: return "neck";
					case e_limb::UPPER_ARM		: return "upper_arm";
					case e_limb::LOWER_ARM		: return "lower_arm";
					case e_limb::THIGH    		: return "thigh";
					case e_limb::LOWER_LEG 		: return "lower_leg";
					}
				}

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae
