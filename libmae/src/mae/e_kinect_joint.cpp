/*
 * e_joint.cpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#include "e_kinect_joint.hpp"

namespace mae
{

	std::string e_kinect_joint_c::str(e_kinect_joint joint)
	{
		switch (joint)
		{
		case e_kinect_joint::INVALID_KINECTJOINT : return "INVALID";
		case e_kinect_joint::WAIST         		: return "WAIST";
		case e_kinect_joint::TORSO         		: return "TORSO";
        case e_kinect_joint::NECK          	   	: return "NECK";
        case e_kinect_joint::HEAD         	   	: return "HEAD";
        case e_kinect_joint::LEFT_SHOULDER 		: return "LEFT_SHOULDER";
		case e_kinect_joint::LEFT_ELBOW    		: return "LEFT_ELBOW";
		case e_kinect_joint::LEFT_WRIST   		: return "LEFT_WRIST";
		case e_kinect_joint::LEFT_HAND     		: return "LEFT_HAND";
		case e_kinect_joint::RIGHT_SHOULDER 	: return "RIGHT_SHOULDER";
		case e_kinect_joint::RIGHT_ELBOW   		: return "RIGHT_ELBOW";
		case e_kinect_joint::RIGHT_WRIST   		: return "RIGHT_WRIST";
		case e_kinect_joint::RIGHT_HAND      	: return "RIGHT_HAND";
		case e_kinect_joint::LEFT_HIP          	: return "LEFT_HIP";
		case e_kinect_joint::LEFT_KNEE     		: return "LEFT_KNEE";
		case e_kinect_joint::LEFT_ANKLE    		: return "LEFT_ANKLE";
        case e_kinect_joint::LEFT_FOOT    		: return "LEFT_FOOT";
		case e_kinect_joint::RIGHT_HIP    		: return "RIGHT_HIP";
		case e_kinect_joint::RIGHT_KNEE  		: return "RIGHT_KNEE";
		case e_kinect_joint::RIGHT_ANKLE  		: return "RIGHT_ANKLE";
		case e_kinect_joint::RIGHT_FOOT   		: return "RIGHT_FOOT";
		case e_kinect_joint::WRH 				: return "WRH";
		case e_kinect_joint::WLH				: return "WLH";
		case e_kinect_joint::WT 				: return "WT";
		case e_kinect_joint::NLS 				: return "NLS";
		case e_kinect_joint::NRS 				: return "NRS";
		case e_kinect_joint::NH 			    : return "NH";
		case e_kinect_joint::END_LH 		    : return "End Site";
		case e_kinect_joint::END_RH 		    : return "End Site";
		case e_kinect_joint::END_LF 		    : return "End Site";
		case e_kinect_joint::END_RF			    : return "End Site";
		case e_kinect_joint::END_H			    : return "End Site";
		}

		throw std::invalid_argument("Enum value not listed in the str() method");
	}

	int e_kinect_joint_c::to_int(e_kinect_joint joint)
	{
		return (int) joint;
	}

	std::vector<e_kinect_joint> e_kinect_joint_c::vec()
	{
		std::vector<e_kinect_joint> result;
		result.push_back(e_kinect_joint::INVALID_KINECTJOINT  		 );
		result.push_back(e_kinect_joint::WAIST         	 );
		result.push_back(e_kinect_joint::TORSO         	 );
		result.push_back(e_kinect_joint::NECK          	);
		result.push_back(e_kinect_joint::HEAD         	);
		result.push_back(e_kinect_joint::LEFT_SHOULDER 	 );
		result.push_back(e_kinect_joint::LEFT_ELBOW    	);
		result.push_back(e_kinect_joint::LEFT_WRIST   	 );
		result.push_back(e_kinect_joint::LEFT_HAND     	 );
		result.push_back(e_kinect_joint::RIGHT_SHOULDER );
		result.push_back(e_kinect_joint::RIGHT_ELBOW   	 );
		result.push_back(e_kinect_joint::RIGHT_WRIST   	 );
		result.push_back(e_kinect_joint::RIGHT_HAND      );
		result.push_back(e_kinect_joint::LEFT_HIP       );
		result.push_back(e_kinect_joint::LEFT_KNEE     	 );
		result.push_back(e_kinect_joint::LEFT_ANKLE    	 );
		result.push_back(e_kinect_joint::LEFT_FOOT    	 );
		result.push_back(e_kinect_joint::RIGHT_HIP    	);
		result.push_back(e_kinect_joint::RIGHT_KNEE  	 );
		result.push_back(e_kinect_joint::RIGHT_ANKLE  	 );
		result.push_back(e_kinect_joint::RIGHT_FOOT   	);
		result.push_back(e_kinect_joint::WRH 			);
		result.push_back(e_kinect_joint::WLH			);
		result.push_back(e_kinect_joint::WT 			 );
		result.push_back(e_kinect_joint::NLS 			 );
		result.push_back(e_kinect_joint::NRS 			);
		result.push_back(e_kinect_joint::NH 			 );
		result.push_back(e_kinect_joint::END_LH 		);
		result.push_back(e_kinect_joint::END_RH 		 );
		result.push_back(e_kinect_joint::END_LF 		 );
		result.push_back(e_kinect_joint::END_RF			);
		result.push_back(e_kinect_joint::END_H			);


		return result;
	}

	bool e_kinect_joint_c::is_dummy(e_kinect_joint joint)
	{
		if (joint == e_kinect_joint::WRH || joint == e_kinect_joint::WLH || joint == e_kinect_joint::WT || joint == e_kinect_joint::NLS
				|| joint == e_kinect_joint::NRS || joint == e_kinect_joint::NH || joint == e_kinect_joint::END_LH || joint == e_kinect_joint::END_RH
				|| joint == e_kinect_joint::END_LF || joint == e_kinect_joint::END_RF || joint == e_kinect_joint::END_H)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool e_kinect_joint_c::is_torso(e_kinect_joint joint)
	{
		if (joint == e_kinect_joint::TORSO || joint == e_kinect_joint::LEFT_SHOULDER || joint == e_kinect_joint::RIGHT_SHOULDER || joint == e_kinect_joint::LEFT_HIP
				|| joint == e_kinect_joint::RIGHT_HIP || joint == e_kinect_joint::NECK  || joint == e_kinect_joint::WAIST)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	e_kinect_joint e_kinect_joint_c::parse(std::string str)
	{
		std::string str_l = mstr::to_lower(str);

		std::vector<e_kinect_joint> v = e_kinect_joint_c::vec();

		for (unsigned int i = 0; i < v.size(); i++)
		{
			std::string t = e_kinect_joint_c::str(v.at(i));
			if (str_l == mstr::to_lower(t))
			{
				return v.at(i);
			}
		}

		throw std::invalid_argument("Could not parse the given value since no match was found.");
	}


} // namespace mae
