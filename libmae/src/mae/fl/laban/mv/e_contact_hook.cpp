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

				std::vector<e_contact_hook> e_contact_hook_c::vec()
				{
					std::vector<e_contact_hook> result;
					result.push_back(e_contact_hook::NONE        );
					result.push_back(e_contact_hook::NAIL        );
					result.push_back(e_contact_hook::TIP         );
					result.push_back(e_contact_hook::PAD         );
					result.push_back(e_contact_hook::BALL        );
					result.push_back(e_contact_hook::HALF_BALL   );
					result.push_back(e_contact_hook::QUARTER_BALL);
					result.push_back(e_contact_hook::FOOT        );
					result.push_back(e_contact_hook::HALF_HEEL   );
					result.push_back(e_contact_hook::QUARTER_HEEL);
					result.push_back(e_contact_hook::FULL_HEEL   );
					result.push_back(e_contact_hook::FULL_BALL   );

					return result;
				}

				e_contact_hook e_contact_hook_c::parse(std::string str)
				{
					std::string str_l = mstr::to_lower(str);

					std::vector<e_contact_hook> v = e_contact_hook_c::vec();

					for (unsigned int i = 0; i < v.size(); i++)
					{
						std::string t = e_contact_hook_c::str(v.at(i));
						if (str_l == mstr::to_lower(t))
						{
							return v.at(i);
						}
					}

					throw std::invalid_argument("Could not parse the given value since no match was found.");
				}



			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
