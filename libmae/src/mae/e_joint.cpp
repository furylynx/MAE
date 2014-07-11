/*
 * e_joint.cpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#include "e_joint.hpp"

namespace mae
{

	std::string e_joint_c::str(e_joint joint)
	{
		switch (joint)
		{
		case e_joint::INVALID  			: return "INVALID";
		case e_joint::HEAD         		: return "HEAD";
		case e_joint::NECK         		: return "NECK";
        case e_joint::LEFT_SHOULDER     : return "LEFT_SHOULDER";
        case e_joint::LEFT_ELBOW        : return "LEFT_ELBOW";
        case e_joint::LEFT_HAND    		: return "LEFT_HAND";
		case e_joint::RIGHT_SHOULDER	: return "RIGHT_SHOULDER";
		case e_joint::RIGHT_ELBOW  		: return "RIGHT_ELBOW";
		case e_joint::RIGHT_HAND   		: return "RIGHT_HAND";
		case e_joint::TORSO          	: return "TORSO";
		case e_joint::LEFT_HIP     		: return "LEFT_HIP";
		case e_joint::LEFT_KNEE    		: return "LEFT_KNEE";
		case e_joint::LEFT_FOOT       	: return "LEFT_FOOT";
		case e_joint::RIGHT_HIP         : return "RIGHT_HIP";
		case e_joint::RIGHT_KNEE   		: return "RIGHT_KNEE";
		case e_joint::RIGHT_FOOT   		: return "RIGHT_FOOT";
        case e_joint::TLS      			: return "TLS";
		case e_joint::TRS       		: return "TRS";
		case e_joint::TLH				: return "TLH";
		case e_joint::TRH				: return "TRH";
		case e_joint::TN				: return "TN";
		case e_joint::END_LH  			: return "End Site";
		case e_joint::END_RH			: return "End Site";
		case e_joint::END_LF			: return "End Site";
		case e_joint::END_RF   			: return "End Site";
		case e_joint::END_H       		: return "End Site";
		}

		throw std::invalid_argument("Enum value not listed in the str() method");
	}

	int e_joint_c::to_int(e_joint joint)
	{
		return (int) joint;
	}

	std::vector<e_joint> e_joint_c::vec()
	{
		std::vector<e_joint> result;
		result.push_back(e_joint::INVALID  		 );
		result.push_back(e_joint::HEAD         	 );
		result.push_back(e_joint::NECK         	 );
		result.push_back(e_joint::LEFT_SHOULDER  );
		result.push_back(e_joint::LEFT_ELBOW     );
		result.push_back(e_joint::LEFT_HAND    	 );
		result.push_back(e_joint::RIGHT_SHOULDER );
		result.push_back(e_joint::RIGHT_ELBOW  	 );
		result.push_back(e_joint::RIGHT_HAND   	 );
		result.push_back(e_joint::TORSO          );
		result.push_back(e_joint::LEFT_HIP     	 );
		result.push_back(e_joint::LEFT_KNEE    	 );
		result.push_back(e_joint::LEFT_FOOT      );
		result.push_back(e_joint::RIGHT_HIP      );
		result.push_back(e_joint::RIGHT_KNEE   	 );
		result.push_back(e_joint::RIGHT_FOOT   	 );
		result.push_back(e_joint::TLS      		 );
		result.push_back(e_joint::TRS       	 );
		result.push_back(e_joint::TLH			 );
		result.push_back(e_joint::TRH			 );
		result.push_back(e_joint::TN			 );
		result.push_back(e_joint::END_LH  		 );
		result.push_back(e_joint::END_RH		 );
		result.push_back(e_joint::END_LF		 );
		result.push_back(e_joint::END_RF   		 );
		result.push_back(e_joint::END_H       	 );

		return result;
	}

	bool e_joint_c::is_dummy(e_joint joint)
	{
		if (joint == e_joint::TLS || joint == e_joint::TRS || joint == e_joint::TLH || joint == e_joint::TRH
				|| joint == e_joint::TN || joint == e_joint::END_LH || joint == e_joint::END_RH
				|| joint == e_joint::END_LF || joint == e_joint::END_RF || joint == e_joint::END_H)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool e_joint_c::is_torso(e_joint joint)
	{
		if (joint == e_joint::TORSO || joint == e_joint::LEFT_SHOULDER || joint == e_joint::RIGHT_SHOULDER || joint == e_joint::LEFT_HIP
				|| joint == e_joint::RIGHT_HIP || joint == e_joint::NECK)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

} // namespace mae
