/*
 * e_contact_hook.cpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#include "e_contact_hook.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{
				std::string e_contact_hook_c::str(e_contact_hook hook)
				{
					switch (hook)
					{
					case e_contact_hook::NONE        		: return "none";
					case e_contact_hook::NAIL        		: return "nail";
					case e_contact_hook::TIP         		: return "tip";
					case e_contact_hook::PAD         		: return "pad";
					case e_contact_hook::BALL        		: return "ball";
					case e_contact_hook::HALF_BALL   		: return "halfBall";
                    case e_contact_hook::QUARTER_BALL   	: return "quarterBall";
                    case e_contact_hook::FOOT           	: return "foot";
                    case e_contact_hook::HALF_HEEL      	: return "halfHeel";
                    case e_contact_hook::QUARTER_HEEL    	: return "quarterHeel";
                    case e_contact_hook::FULL_HEEL          : return "fullHeel";
                    case e_contact_hook::FULL_BALL          : return "fullBall";
					}

					throw std::invalid_argument("Enum value not listed in the str() method");

				}



			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
