/*
 * e_fl_joint.cpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#include "e_fl_joint.hpp"

namespace mae
{
	namespace fl
	{

		std::string e_fl_joint_c::str(e_fl_joint joint)
		{
			switch (joint)
			{
			case e_fl_joint::INVALID_FL_JOINT		   	: return "INVALID";
			case e_fl_joint::HEAD          		: return "HEAD";
			case e_fl_joint::LEFT_UPPER_ARM		: return "LEFT_UPPER_ARM";
	        case e_fl_joint::LEFT_FOREARM      	: return "LEFT_FOREARM";
	        case e_fl_joint::LEFT_WHOLE_ARM    	: return "LEFT_WHOLE_ARM";
	        case e_fl_joint::RIGHT_UPPER_ARM	: return "RIGHT_UPPER_ARM";
			case e_fl_joint::RIGHT_FOREARM 		: return "RIGHT_FOREARM";
			case e_fl_joint::RIGHT_WHOLE_ARM	: return "RIGHT_WHOLE_ARM";
			case e_fl_joint::LEFT_THIGH			: return "LEFT_THIGH";
			case e_fl_joint::LEFT_SHANK			: return "LEFT_SHANK";
			case e_fl_joint::LEFT_WHOLE_LEG		: return "LEFT_WHOLE_LEG";
			case e_fl_joint::RIGHT_THIGH		: return "RIGHT_THIGH";
			case e_fl_joint::RIGHT_SHANK 		: return "RIGHT_SHANK";
			case e_fl_joint::RIGHT_WHOLE_LEG    : return "RIGHT_WHOLE_LEG";
			}

			throw std::invalid_argument("Enum value not listed in the str() method");
		}

		int e_fl_joint_c::to_int(e_fl_joint joint)
		{
			return (int) joint;
		}

		std::vector<e_fl_joint> e_fl_joint_c::vec()
		{
			std::vector<e_fl_joint> result;
			result.push_back(e_fl_joint::INVALID_FL_JOINT		 );
			result.push_back(e_fl_joint::HEAD          	 );
			result.push_back(e_fl_joint::LEFT_UPPER_ARM	 );
			result.push_back(e_fl_joint::LEFT_FOREARM    );
			result.push_back(e_fl_joint::LEFT_WHOLE_ARM  );
			result.push_back(e_fl_joint::RIGHT_UPPER_ARM );
			result.push_back(e_fl_joint::RIGHT_FOREARM 	 );
			result.push_back(e_fl_joint::RIGHT_WHOLE_ARM );
			result.push_back(e_fl_joint::LEFT_THIGH		 );
			result.push_back(e_fl_joint::LEFT_SHANK		 );
			result.push_back(e_fl_joint::LEFT_WHOLE_LEG	 );
			result.push_back(e_fl_joint::RIGHT_THIGH	 );
			result.push_back(e_fl_joint::RIGHT_SHANK 	 );
			result.push_back(e_fl_joint::RIGHT_WHOLE_LEG );

			return result;
		}

		e_fl_joint e_fl_joint_c::parse(std::string str)
		{
			std::string str_l = mstr::to_lower(str);

			std::vector<e_fl_joint> v = e_fl_joint_c::vec();

			for (unsigned int i = 0; i < v.size(); i++)
			{
				std::string t = e_fl_joint_c::str(v.at(i));
				if (str_l == mstr::to_lower(t))
				{
					return v.at(i);
				}
			}

			throw std::invalid_argument("Could not parse the given value since no match was found.");
		}


	} // namespace fl
} // namespace mae
