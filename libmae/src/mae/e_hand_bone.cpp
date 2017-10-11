#include "e_hand_bone.hpp"

namespace mae
{

	std::string e_hand_bone_c::str(e_hand_bone bone)
	{
		switch (bone)
		{
		case e_hand_bone::INVALID_HAND_BONE    		: return "INVALID";
		case e_hand_bone::LEFT_THUMB           		: return "LEFT_THUMB";
		case e_hand_bone::LEFT_INDEX_FINGER 		: return "LEFT_INDEX_FINGER";
        case e_hand_bone::LEFT_MIDDLE_FINGER           : return "LEFT_MIDDLE_FINGER";
        case e_hand_bone::LEFT_RING_FINGER         		: return "LEFT_RING_FINGER";
        case e_hand_bone::LEFT_LITTLE_FINGER 				: return "LEFT_LITTLE_FINGER";
		case e_hand_bone::LEFT_THUMB_PROXIMAL_PHALANX  		: return "LEFT_THUMB_PROXIMAL_PHALANX";
		case e_hand_bone::LEFT_THUMB_INTERMEDIATE_PHALANX		: return "LEFT_THUMB_INTERMEDIATE_PHALANX";
		case e_hand_bone::LEFT_THUMB_DISTAL_PHALANX       		: return "LEFT_THUMB_DISTAL_PHALANX";
		case e_hand_bone::LEFT_INDEX_FINGER_PROXIMAL_PHALANX        		: return "LEFT_INDEX_FINGER_PROXIMAL_PHALANX";
		case e_hand_bone::LEFT_INDEX_FINGER_INTERMEDIATE_PHALANX 		: return "LEFT_INDEX_FINGER_INTERMEDIATE_PHALANX";
		case e_hand_bone::LEFT_INDEX_FINGER_DISTAL_PHALANX			: return "LEFT_INDEX_FINGER_DISTAL_PHALANX";
		case e_hand_bone::LEFT_MIDDLE_FINGER_PROXIMAL_PHALANX        	: return "LEFT_MIDDLE_FINGER_PROXIMAL_PHALANX";
		case e_hand_bone::LEFT_MIDDLE_FINGER_INTERMEDIATE_PHALANX        : return "LEFT_MIDDLE_FINGER_INTERMEDIATE_PHALANX";
		case e_hand_bone::LEFT_MIDDLE_FINGER_DISTAL_PHALANX 			: return "LEFT_MIDDLE_FINGER_DISTAL_PHALANX";
		case e_hand_bone::LEFT_RING_FINGER_PROXIMAL_PHALANX 			: return "LEFT_RING_FINGER_PROXIMAL_PHALANX";
		case e_hand_bone::LEFT_RING_FINGER_INTERMEDIATE_PHALANX 				: return "LEFT_RING_FINGER_INTERMEDIATE_PHALANX";
		case e_hand_bone::LEFT_RING_FINGER_DISTAL_PHALANX 				: return "LEFT_RING_FINGER_DISTAL_PHALANX";
		case e_hand_bone::LEFT_LITTLE_FINGER_PROXIMAL_PHALANX 				: return "LEFT_LITTLE_FINGER_PROXIMAL_PHALANX";
		case e_hand_bone::LEFT_LITTLE_FINGER_INTERMEDIATE_PHALANX 				: return "LEFT_LITTLE_FINGER_INTERMEDIATE_PHALANX";
		case e_hand_bone::LEFT_LITTLE_FINGER_DISTAL_PHALANX 				: return "LEFT_LITTLE_FINGER_DISTAL_PHALANX";
		case e_hand_bone::RIGHT_THUMB           		: return "RIGHT_THUMB";
		case e_hand_bone::RIGHT_INDEX_FINGER 		: return "RIGHT_INDEX_FINGER";
		case e_hand_bone::RIGHT_MIDDLE_FINGER           : return "RIGHT_MIDDLE_FINGER";
		case e_hand_bone::RIGHT_RING_FINGER         : return "RIGHT_RING_FINGER";
		case e_hand_bone::RIGHT_LITTLE_FINGER 		: return "RIGHT_LITTLE_FINGER";
		case e_hand_bone::RIGHT_THUMB_PROXIMAL_PHALANX  		: return "RIGHT_THUMB_PROXIMAL_PHALANX";
		case e_hand_bone::RIGHT_THUMB_INTERMEDIATE_PHALANX		: return "RIGHT_THUMB_INTERMEDIATE_PHALANX";
		case e_hand_bone::RIGHT_THUMB_DISTAL_PHALANX       		: return "RIGHT_THUMB_DISTAL_PHALANX";
		case e_hand_bone::RIGHT_INDEX_FINGER_PROXIMAL_PHALANX        		: return "RIGHT_INDEX_FINGER_PROXIMAL_PHALANX";
		case e_hand_bone::RIGHT_INDEX_FINGER_INTERMEDIATE_PHALANX 		: return "RIGHT_INDEX_FINGER_INTERMEDIATE_PHALANX";
		case e_hand_bone::RIGHT_INDEX_FINGER_DISTAL_PHALANX			: return "RIGHT_INDEX_FINGER_DISTAL_PHALANX";
		case e_hand_bone::RIGHT_MIDDLE_FINGER_PROXIMAL_PHALANX        	: return "RIGHT_MIDDLE_FINGER_PROXIMAL_PHALANX";
		case e_hand_bone::RIGHT_MIDDLE_FINGER_INTERMEDIATE_PHALANX        : return "RIGHT_MIDDLE_FINGER_INTERMEDIATE_PHALANX";
		case e_hand_bone::RIGHT_MIDDLE_FINGER_DISTAL_PHALANX 			: return "RIGHT_MIDDLE_FINGER_DISTAL_PHALANX";
		case e_hand_bone::RIGHT_RING_FINGER_PROXIMAL_PHALANX 			: return "RIGHT_RING_FINGER_PROXIMAL_PHALANX";
		case e_hand_bone::RIGHT_RING_FINGER_INTERMEDIATE_PHALANX 				: return "RIGHT_RING_FINGER_INTERMEDIATE_PHALANX";
		case e_hand_bone::RIGHT_RING_FINGER_DISTAL_PHALANX 				: return "RIGHT_RING_FINGER_DISTAL_PHALANX";
		case e_hand_bone::RIGHT_LITTLE_FINGER_PROXIMAL_PHALANX 				: return "RIGHT_LITTLE_FINGER_PROXIMAL_PHALANX";
		case e_hand_bone::RIGHT_LITTLE_FINGER_INTERMEDIATE_PHALANX 				: return "RIGHT_LITTLE_FINGER_INTERMEDIATE_PHALANX";
		case e_hand_bone::RIGHT_LITTLE_FINGER_DISTAL_PHALANX 				: return "RIGHT_LITTLE_FINGER_DISTAL_PHALANX";
		}

		throw std::invalid_argument("Enum value not listed in the str() method");
	}

	int e_hand_bone_c::to_int(e_hand_bone bone)
	{
		return (int) bone;
	}

	std::vector<e_hand_bone> e_hand_bone_c::vec()
	{
		std::vector<e_hand_bone> result;
		result.push_back(e_hand_bone::INVALID_HAND_BONE    	);
		result.push_back(e_hand_bone::LEFT_THUMB     	);
		result.push_back(e_hand_bone::LEFT_INDEX_FINGER 	    	);
		result.push_back(e_hand_bone::LEFT_MIDDLE_FINGER              	);
		result.push_back(e_hand_bone::LEFT_RING_FINGER         		    	);
		result.push_back(e_hand_bone::LEFT_LITTLE_FINGER 				    	);
		result.push_back(e_hand_bone::LEFT_THUMB_PROXIMAL_PHALANX  		    	);
		result.push_back(e_hand_bone::LEFT_THUMB_INTERMEDIATE_PHALANX		    	);
		result.push_back(e_hand_bone::LEFT_THUMB_DISTAL_PHALANX       		    	);
		result.push_back(e_hand_bone::LEFT_INDEX_FINGER_PROXIMAL_PHALANX        		    	);
		result.push_back(e_hand_bone::LEFT_INDEX_FINGER_INTERMEDIATE_PHALANX 		    	);
		result.push_back(e_hand_bone::LEFT_INDEX_FINGER_DISTAL_PHALANX			    	);
		result.push_back(e_hand_bone::LEFT_MIDDLE_FINGER_PROXIMAL_PHALANX        	    	);
		result.push_back(e_hand_bone::LEFT_MIDDLE_FINGER_INTERMEDIATE_PHALANX            	);
		result.push_back(e_hand_bone::LEFT_MIDDLE_FINGER_DISTAL_PHALANX 			    	);
		result.push_back(e_hand_bone::LEFT_RING_FINGER_PROXIMAL_PHALANX 			    	);
		result.push_back(e_hand_bone::LEFT_RING_FINGER_INTERMEDIATE_PHALANX 				    	);
		result.push_back(e_hand_bone::LEFT_RING_FINGER_DISTAL_PHALANX 				    	);
		result.push_back(e_hand_bone::LEFT_LITTLE_FINGER_PROXIMAL_PHALANX 				    	);
		result.push_back(e_hand_bone::LEFT_LITTLE_FINGER_INTERMEDIATE_PHALANX 				    	);
		result.push_back(e_hand_bone::LEFT_LITTLE_FINGER_DISTAL_PHALANX 				    	);
		result.push_back(e_hand_bone::RIGHT_THUMB           		    	);
		result.push_back(e_hand_bone::RIGHT_INDEX_FINGER 		    	);
		result.push_back(e_hand_bone::RIGHT_MIDDLE_FINGER               	);
		result.push_back(e_hand_bone::RIGHT_RING_FINGER             	);
		result.push_back(e_hand_bone::RIGHT_LITTLE_FINGER 		    	);
		result.push_back(e_hand_bone::RIGHT_THUMB_PROXIMAL_PHALANX  		    	);
		result.push_back(e_hand_bone::RIGHT_THUMB_INTERMEDIATE_PHALANX		    	);
		result.push_back(e_hand_bone::RIGHT_THUMB_DISTAL_PHALANX       		    	);
		result.push_back(e_hand_bone::RIGHT_INDEX_FINGER_PROXIMAL_PHALANX        		    	);
		result.push_back(e_hand_bone::RIGHT_INDEX_FINGER_INTERMEDIATE_PHALANX 		    	);
		result.push_back(e_hand_bone::RIGHT_INDEX_FINGER_DISTAL_PHALANX			    	);
		result.push_back(e_hand_bone::RIGHT_MIDDLE_FINGER_PROXIMAL_PHALANX        	    	);
		result.push_back(e_hand_bone::RIGHT_MIDDLE_FINGER_INTERMEDIATE_PHALANX            	);
		result.push_back(e_hand_bone::RIGHT_MIDDLE_FINGER_DISTAL_PHALANX 			    	);
		result.push_back(e_hand_bone::RIGHT_RING_FINGER_PROXIMAL_PHALANX 			    	);
		result.push_back(e_hand_bone::RIGHT_RING_FINGER_INTERMEDIATE_PHALANX 				    	);
		result.push_back(e_hand_bone::RIGHT_RING_FINGER_DISTAL_PHALANX 				    	);
		result.push_back(e_hand_bone::RIGHT_LITTLE_FINGER_PROXIMAL_PHALANX 				    	);
		result.push_back(e_hand_bone::RIGHT_LITTLE_FINGER_INTERMEDIATE_PHALANX 				    	);
		result.push_back(e_hand_bone::RIGHT_LITTLE_FINGER_DISTAL_PHALANX 				    	);

		return result;
	}

	std::vector<e_hand_bone> e_hand_bone_c::vec_side(bool is_left)
	{
		std::vector<e_hand_bone> result;


		result.push_back(e_hand_bone::INVALID_HAND_BONE);

		if (is_left) {
			result.push_back(e_hand_bone::LEFT_THUMB);
			result.push_back(e_hand_bone::LEFT_INDEX_FINGER);
			result.push_back(e_hand_bone::LEFT_MIDDLE_FINGER);
			result.push_back(e_hand_bone::LEFT_RING_FINGER);
			result.push_back(e_hand_bone::LEFT_LITTLE_FINGER);
			result.push_back(e_hand_bone::LEFT_THUMB_PROXIMAL_PHALANX);
			result.push_back(e_hand_bone::LEFT_THUMB_INTERMEDIATE_PHALANX);
			result.push_back(e_hand_bone::LEFT_THUMB_DISTAL_PHALANX);
			result.push_back(e_hand_bone::LEFT_INDEX_FINGER_PROXIMAL_PHALANX);
			result.push_back(e_hand_bone::LEFT_INDEX_FINGER_INTERMEDIATE_PHALANX);
			result.push_back(e_hand_bone::LEFT_INDEX_FINGER_DISTAL_PHALANX);
			result.push_back(e_hand_bone::LEFT_MIDDLE_FINGER_PROXIMAL_PHALANX);
			result.push_back(e_hand_bone::LEFT_MIDDLE_FINGER_INTERMEDIATE_PHALANX);
			result.push_back(e_hand_bone::LEFT_MIDDLE_FINGER_DISTAL_PHALANX);
			result.push_back(e_hand_bone::LEFT_RING_FINGER_PROXIMAL_PHALANX);
			result.push_back(e_hand_bone::LEFT_RING_FINGER_INTERMEDIATE_PHALANX);
			result.push_back(e_hand_bone::LEFT_RING_FINGER_DISTAL_PHALANX);
			result.push_back(e_hand_bone::LEFT_LITTLE_FINGER_PROXIMAL_PHALANX);
			result.push_back(e_hand_bone::LEFT_LITTLE_FINGER_INTERMEDIATE_PHALANX);
			result.push_back(e_hand_bone::LEFT_LITTLE_FINGER_DISTAL_PHALANX);
		}
		else
		{
			result.push_back(e_hand_bone::RIGHT_THUMB);
			result.push_back(e_hand_bone::RIGHT_INDEX_FINGER);
			result.push_back(e_hand_bone::RIGHT_MIDDLE_FINGER);
			result.push_back(e_hand_bone::RIGHT_RING_FINGER);
			result.push_back(e_hand_bone::RIGHT_LITTLE_FINGER);
			result.push_back(e_hand_bone::RIGHT_THUMB_PROXIMAL_PHALANX);
			result.push_back(e_hand_bone::RIGHT_THUMB_INTERMEDIATE_PHALANX);
			result.push_back(e_hand_bone::RIGHT_THUMB_DISTAL_PHALANX);
			result.push_back(e_hand_bone::RIGHT_INDEX_FINGER_PROXIMAL_PHALANX);
			result.push_back(e_hand_bone::RIGHT_INDEX_FINGER_INTERMEDIATE_PHALANX);
			result.push_back(e_hand_bone::RIGHT_INDEX_FINGER_DISTAL_PHALANX);
			result.push_back(e_hand_bone::RIGHT_MIDDLE_FINGER_PROXIMAL_PHALANX);
			result.push_back(e_hand_bone::RIGHT_MIDDLE_FINGER_INTERMEDIATE_PHALANX);
			result.push_back(e_hand_bone::RIGHT_MIDDLE_FINGER_DISTAL_PHALANX);
			result.push_back(e_hand_bone::RIGHT_RING_FINGER_PROXIMAL_PHALANX);
			result.push_back(e_hand_bone::RIGHT_RING_FINGER_INTERMEDIATE_PHALANX);
			result.push_back(e_hand_bone::RIGHT_RING_FINGER_DISTAL_PHALANX);
			result.push_back(e_hand_bone::RIGHT_LITTLE_FINGER_PROXIMAL_PHALANX);
			result.push_back(e_hand_bone::RIGHT_LITTLE_FINGER_INTERMEDIATE_PHALANX);
			result.push_back(e_hand_bone::RIGHT_LITTLE_FINGER_DISTAL_PHALANX);
		}

		return result;
	}

	e_hand_bone e_hand_bone_c::parse(std::string str)
	{
		std::string str_l = mstr::to_lower(str);

		std::vector<e_hand_bone> v = e_hand_bone_c::vec();

		for (unsigned int i = 0; i < v.size(); i++)
		{
			std::string t = e_hand_bone_c::str(v.at(i));
			if (str_l == mstr::to_lower(t))
			{
				return v.at(i);
			}
		}

		throw std::invalid_argument("Could not parse the given value since no match was found.");
	}

	bool e_hand_bone_c::is_left(e_hand_bone bone)
	{

		if ( e_hand_bone::LEFT_THUMB == bone
		|| e_hand_bone::LEFT_INDEX_FINGER == bone
		|| e_hand_bone::LEFT_MIDDLE_FINGER == bone
		|| e_hand_bone::LEFT_RING_FINGER == bone
		|| e_hand_bone::LEFT_LITTLE_FINGER == bone
		|| e_hand_bone::LEFT_THUMB_PROXIMAL_PHALANX == bone
		|| e_hand_bone::LEFT_THUMB_INTERMEDIATE_PHALANX == bone
		|| e_hand_bone::LEFT_THUMB_DISTAL_PHALANX == bone
		|| e_hand_bone::LEFT_INDEX_FINGER_PROXIMAL_PHALANX == bone
		|| e_hand_bone::LEFT_INDEX_FINGER_INTERMEDIATE_PHALANX == bone
		|| e_hand_bone::LEFT_INDEX_FINGER_DISTAL_PHALANX == bone
		|| e_hand_bone::LEFT_MIDDLE_FINGER_PROXIMAL_PHALANX == bone
		|| e_hand_bone::LEFT_MIDDLE_FINGER_INTERMEDIATE_PHALANX == bone
		|| e_hand_bone::LEFT_MIDDLE_FINGER_DISTAL_PHALANX == bone
		|| e_hand_bone::LEFT_RING_FINGER_PROXIMAL_PHALANX == bone
		|| e_hand_bone::LEFT_RING_FINGER_INTERMEDIATE_PHALANX == bone
		|| e_hand_bone::LEFT_RING_FINGER_DISTAL_PHALANX == bone
		|| e_hand_bone::LEFT_LITTLE_FINGER_PROXIMAL_PHALANX == bone
		|| e_hand_bone::LEFT_LITTLE_FINGER_INTERMEDIATE_PHALANX == bone
		|| e_hand_bone::LEFT_LITTLE_FINGER_DISTAL_PHALANX == bone
				)
		{
			return true;
		}
		else
		{
			return false;
		}

	}

	bool e_hand_bone_c::is_right(e_hand_bone bone)
	{

		if ( e_hand_bone::RIGHT_THUMB  == bone
		 || e_hand_bone::RIGHT_INDEX_FINGER  == bone
		 || e_hand_bone::RIGHT_MIDDLE_FINGER  == bone
		 || e_hand_bone::RIGHT_RING_FINGER  == bone
		 || e_hand_bone::RIGHT_LITTLE_FINGER  == bone
		 || e_hand_bone::RIGHT_THUMB_PROXIMAL_PHALANX  == bone
		 || e_hand_bone::RIGHT_THUMB_INTERMEDIATE_PHALANX  == bone
		 || e_hand_bone::RIGHT_THUMB_DISTAL_PHALANX  == bone
		 || e_hand_bone::RIGHT_INDEX_FINGER_PROXIMAL_PHALANX  == bone
		 || e_hand_bone::RIGHT_INDEX_FINGER_INTERMEDIATE_PHALANX  == bone
		 || e_hand_bone::RIGHT_INDEX_FINGER_DISTAL_PHALANX  == bone
		 || e_hand_bone::RIGHT_MIDDLE_FINGER_PROXIMAL_PHALANX  == bone
		 || e_hand_bone::RIGHT_MIDDLE_FINGER_INTERMEDIATE_PHALANX  == bone
		 || e_hand_bone::RIGHT_MIDDLE_FINGER_DISTAL_PHALANX  == bone
		 || e_hand_bone::RIGHT_RING_FINGER_PROXIMAL_PHALANX  == bone
		 || e_hand_bone::RIGHT_RING_FINGER_INTERMEDIATE_PHALANX  == bone
		 || e_hand_bone::RIGHT_RING_FINGER_DISTAL_PHALANX  == bone
		 || e_hand_bone::RIGHT_LITTLE_FINGER_PROXIMAL_PHALANX  == bone
		 || e_hand_bone::RIGHT_LITTLE_FINGER_INTERMEDIATE_PHALANX  == bone
		 || e_hand_bone::RIGHT_LITTLE_FINGER_DISTAL_PHALANX  == bone
				)
		{
			return true;
		}
		else
		{
			return false;
		}

	}



} // namespace mae
