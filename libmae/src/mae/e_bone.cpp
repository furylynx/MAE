/*
 * e_bone.cpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#include "e_bone.hpp"

namespace mae
{

	std::string e_bone_c::str(e_bone bone)
	{
		switch (bone)
		{
		case e_bone::INVALID    			: return "INVALID";
		case e_bone::HEAD           		: return "HEAD";
		case e_bone::LEFT_UPPER_ARM 		: return "LEFT_UPPER_ARM";
        case e_bone::LEFT_FOREARM           : return "LEFT_FOREARM";
        case e_bone::LEFT_WHOLE_ARM         : return "LEFT_WHOLE_ARM";
        case e_bone::RIGHT_UPPER_ARM 		: return "RIGHT_UPPER_ARM";
		case e_bone::RIGHT_FOREARM  		: return "RIGHT_FOREARM";
		case e_bone::RIGHT_WHOLE_ARM		: return "RIGHT_WHOLE_ARM";
		case e_bone::LEFT_THIGH       		: return "LEFT_THIGH";
		case e_bone::LEFT_SHANK        		: return "LEFT_SHANK";
		case e_bone::LEFT_WHOLE_LEG 		: return "LEFT_WHOLE_LEG";
		case e_bone::RIGHT_THIGH			: return "RIGHT_THIGH";
		case e_bone::RIGHT_SHANK        	: return "RIGHT_SHANK";
		case e_bone::RIGHT_WHOLE_LEG        : return "RIGHT_WHOLE_LEG";
		}

		throw std::invalid_argument("Enum value not listed in the str() method");
	}

	int e_bone_c::to_int(e_bone bone)
	{
		return (int) bone;
	}

	std::vector<e_bone> e_bone_c::vec()
	{
		std::vector<e_bone> result;
		result.push_back(e_bone::INVALID    		);
		result.push_back(e_bone::HEAD           	);
		result.push_back(e_bone::LEFT_UPPER_ARM 	);
		result.push_back(e_bone::LEFT_FOREARM    	);
		result.push_back(e_bone::LEFT_WHOLE_ARM  	);
		result.push_back(e_bone::RIGHT_UPPER_ARM 	);
		result.push_back(e_bone::RIGHT_FOREARM  	);
		result.push_back(e_bone::RIGHT_WHOLE_ARM	);
		result.push_back(e_bone::LEFT_THIGH      	);
		result.push_back(e_bone::LEFT_SHANK      	);
		result.push_back(e_bone::LEFT_WHOLE_LEG 	);
		result.push_back(e_bone::RIGHT_THIGH		);
		result.push_back(e_bone::RIGHT_SHANK     	);
		result.push_back(e_bone::RIGHT_WHOLE_LEG 	);

		return result;
	}



} // namespace mae
