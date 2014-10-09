/*
 * e_joint.cpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#include "e_joint.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{

				std::string e_joint_c::str(e_joint joint_)
				{
					switch (joint_)
					{
					case e_joint::NONE_JOINT    	: return "none";
					case e_joint::SHOULDER	: return "shoulder";
					case e_joint::ELBOW   	: return "elbow";
					case e_joint::WRIST   	: return "wrist";
					case e_joint::HAND    	: return "hand";
					case e_joint::FINGERS 	: return "fingers";
					case e_joint::HIP     	: return "hip";
					case e_joint::KNEE    	: return "knee";
					case e_joint::ANKLE     : return "ankle";
				    case e_joint::FOOT      : return "foot";
                    case e_joint::TOES      : return "toes";
					}

					throw std::invalid_argument("Enum value not listed in the str() method");
				}

				std::vector<e_joint> e_joint_c::vec()
				{
					std::vector<e_joint> result;
					result.push_back(e_joint::NONE_JOINT    	);
					result.push_back(e_joint::SHOULDER 	);
					result.push_back(e_joint::ELBOW   	);
					result.push_back(e_joint::WRIST    	);
					result.push_back(e_joint::HAND    	);
					result.push_back(e_joint::FINGERS  	);
					result.push_back(e_joint::HIP     	);
					result.push_back(e_joint::KNEE     	);
					result.push_back(e_joint::ANKLE   	);
					result.push_back(e_joint::FOOT     	);
					result.push_back(e_joint::TOES    	);

					return result;
				}

				e_joint e_joint_c::parse(std::string str)
				{
					std::string str_l = mstr::to_lower(str);

					std::vector<e_joint> v = e_joint_c::vec();

					for (unsigned int i = 0; i < v.size(); i++)
					{
						std::string t = e_joint_c::str(v.at(i));
						if (str_l == mstr::to_lower(t))
						{
							return v.at(i);
						}
					}

					throw std::invalid_argument("Could not parse the given value since no match was found.");
				}

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae
