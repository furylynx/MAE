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

				std::string e_joint_str::str(e_joint joint_)
				{
					switch (joint_)
					{
					case e_joint::NONE    	: return "none";
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


			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae
