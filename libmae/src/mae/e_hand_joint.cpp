	#include "e_hand_joint.hpp"

	namespace mae
	{

		std::string e_hand_joint_c::str(e_hand_joint joint)
		{
			switch (joint)
			{
				case e_hand_joint::INVALID_HAND_JOINT : return "INVALID";
				case e_hand_joint::LEFT_WRIST : return "LEFT_WRIST";
				case e_hand_joint::LEFT_THUMB_PROXIMAL_INTERPHALANGEAL_JOINT : return "LEFT_THUMB_PROXIMAL_INTERPHALANGEAL_JOINT";
				case e_hand_joint::LEFT_THUMB_DISTAL_INTERPHALANGEAL_JOINT : return "LEFT_THUMB_DISTAL_INTERPHALANGEAL_JOINT";
				case e_hand_joint::LEFT_THUMB_TIP : return "LEFT_THUMB_TIP";
				case e_hand_joint::LEFT_INDEX_FINGER_METACARPOPHALANGEAL_JOINT : return "LEFT_INDEX_FINGER_METACARPOPHALANGEAL_JOINT";
				case e_hand_joint::LEFT_INDEX_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT : return "LEFT_INDEX_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT";
				case e_hand_joint::LEFT_INDEX_FINGER_DISTAL_INTERPHALANGEAL_JOINT: return "LEFT_INDEX_FINGER_DISTAL_INTERPHALANGEAL_JOINT";
				case e_hand_joint::LEFT_INDEX_FINGER_TIP: return "LEFT_INDEX_FINGER_TIP";
				case e_hand_joint::LEFT_MIDDLE_FINGER_METACARPOPHALANGEAL_JOINT: return "LEFT_MIDDLE_FINGER_METACARPOPHALANGEAL_JOINT";
				case e_hand_joint::LEFT_MIDDLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT: return "LEFT_MIDDLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT";
				case e_hand_joint::LEFT_MIDDLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT: return "LEFT_MIDDLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT";
				case e_hand_joint::LEFT_MIDDLE_FINGER_TIP: return "LEFT_MIDDLE_FINGER_TIP";
				case e_hand_joint::LEFT_RING_FINGER_METACARPOPHALANGEAL_JOINT: return "LEFT_RING_FINGER_METACARPOPHALANGEAL_JOINT";
				case e_hand_joint::LEFT_RING_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT: return "LEFT_RING_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT";
				case e_hand_joint::LEFT_RING_FINGER_DISTAL_INTERPHALANGEAL_JOINT: return "LEFT_RING_FINGER_DISTAL_INTERPHALANGEAL_JOINT";
				case e_hand_joint::LEFT_RING_FINGER_TIP: return "LEFT_RING_FINGER_TIP";
				case e_hand_joint::LEFT_LITTLE_FINGER_METACARPOPHALANGEAL_JOINT: return "LEFT_LITTLE_FINGER_METACARPOPHALANGEAL_JOINT";
				case e_hand_joint::LEFT_LITTLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT: return "LEFT_LITTLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT";
				case e_hand_joint::LEFT_LITTLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT: return "LEFT_LITTLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT";
				case e_hand_joint::LEFT_LITTLE_FINGER_TIP: return "LEFT_LITTLE_FINGER_TIP";
				case e_hand_joint::RIGHT_WRIST: return "RIGHT_WRIST";
				case e_hand_joint::RIGHT_THUMB_PROXIMAL_INTERPHALANGEAL_JOINT: return "RIGHT_THUMB_PROXIMAL_INTERPHALANGEAL_JOINT";
				case e_hand_joint::RIGHT_THUMB_DISTAL_INTERPHALANGEAL_JOINT: return "RIGHT_THUMB_DISTAL_INTERPHALANGEAL_JOINT";
				case e_hand_joint::RIGHT_THUMB_TIP: return "RIGHT_THUMB_TIP";
				case e_hand_joint::RIGHT_INDEX_FINGER_METACARPOPHALANGEAL_JOINT: return "RIGHT_INDEX_FINGER_METACARPOPHALANGEAL_JOINT";
				case e_hand_joint::RIGHT_INDEX_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT: return "RIGHT_INDEX_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT";
				case e_hand_joint::RIGHT_INDEX_FINGER_DISTAL_INTERPHALANGEAL_JOINT: return "RIGHT_INDEX_FINGER_DISTAL_INTERPHALANGEAL_JOINT";
				case e_hand_joint::RIGHT_INDEX_FINGER_TIP: return "RIGHT_INDEX_FINGER_TIP";
				case e_hand_joint::RIGHT_MIDDLE_FINGER_METACARPOPHALANGEAL_JOINT: return "RIGHT_MIDDLE_FINGER_METACARPOPHALANGEAL_JOINT";
				case e_hand_joint::RIGHT_MIDDLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT: return "RIGHT_MIDDLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT";
				case e_hand_joint::RIGHT_MIDDLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT: return "RIGHT_MIDDLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT";
				case e_hand_joint::RIGHT_MIDDLE_FINGER_TIP: return "RIGHT_MIDDLE_FINGER_TIP";
				case e_hand_joint::RIGHT_RING_FINGER_METACARPOPHALANGEAL_JOINT: return "RIGHT_RING_FINGER_METACARPOPHALANGEAL_JOINT";
				case e_hand_joint::RIGHT_RING_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT: return "RIGHT_RING_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT";
				case e_hand_joint::RIGHT_RING_FINGER_DISTAL_INTERPHALANGEAL_JOINT: return "RIGHT_RING_FINGER_DISTAL_INTERPHALANGEAL_JOINT";
				case e_hand_joint::RIGHT_RING_FINGER_TIP: return "RIGHT_RING_FINGER_TIP";
				case e_hand_joint::RIGHT_LITTLE_FINGER_METACARPOPHALANGEAL_JOINT: return "RIGHT_LITTLE_FINGER_METACARPOPHALANGEAL_JOINT";
				case e_hand_joint::RIGHT_LITTLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT: return "RIGHT_LITTLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT";
				case e_hand_joint::RIGHT_LITTLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT: return "RIGHT_LITTLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT";
				case e_hand_joint::RIGHT_LITTLE_FINGER_TIP: return "RIGHT_LITTLE_FINGER_TIP";
				case e_hand_joint::LPT: return "LPT";
				case e_hand_joint::LPI: return "LPI";
				case e_hand_joint::LPM: return "LPM";
				case e_hand_joint::LPR: return "LPR";
				case e_hand_joint::LPL: return "LPL";
				case e_hand_joint::RPT: return "RPT";
				case e_hand_joint::RPI: return "RPI";
				case e_hand_joint::RPM: return "RPM";
				case e_hand_joint::RPR: return "RPR";
				case e_hand_joint::RPL: return "RPL";
				case e_hand_joint::END_LT: return "End Site";
				case e_hand_joint::END_LI: return "End Site";
				case e_hand_joint::END_LM: return "End Site";
				case e_hand_joint::END_LR: return "End Site";
				case e_hand_joint::END_LL: return "End Site";
				case e_hand_joint::END_RT: return "End Site";
				case e_hand_joint::END_RI: return "End Site";
				case e_hand_joint::END_RM: return "End Site";
				case e_hand_joint::END_RR: return "End Site";
				case e_hand_joint::END_RL: return "End Site";
			}

			throw std::invalid_argument("Enum value not listed in the str() method");
		}

		int e_hand_joint_c::to_int(e_hand_joint joint)
		{
			return (int) joint;
		}

		std::vector<e_hand_joint> e_hand_joint_c::vec()
		{
			std::vector<e_hand_joint> result;
			result.push_back(e_hand_joint::INVALID_HAND_JOINT);
			result.push_back(e_hand_joint::LEFT_WRIST);
			result.push_back(e_hand_joint::LEFT_THUMB_PROXIMAL_INTERPHALANGEAL_JOINT);
			result.push_back(e_hand_joint::LEFT_THUMB_DISTAL_INTERPHALANGEAL_JOINT);
			result.push_back(e_hand_joint::LEFT_THUMB_TIP);
			result.push_back(e_hand_joint::LEFT_INDEX_FINGER_METACARPOPHALANGEAL_JOINT);
			result.push_back(e_hand_joint::LEFT_INDEX_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT);
			result.push_back(e_hand_joint::LEFT_INDEX_FINGER_DISTAL_INTERPHALANGEAL_JOINT);
			result.push_back(e_hand_joint::LEFT_INDEX_FINGER_TIP);
			result.push_back(e_hand_joint::LEFT_MIDDLE_FINGER_METACARPOPHALANGEAL_JOINT);
			result.push_back(e_hand_joint::LEFT_MIDDLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT);
			result.push_back(e_hand_joint::LEFT_MIDDLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT);
			result.push_back(e_hand_joint::LEFT_MIDDLE_FINGER_TIP);
			result.push_back(e_hand_joint::LEFT_RING_FINGER_METACARPOPHALANGEAL_JOINT);
			result.push_back(e_hand_joint::LEFT_RING_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT);
			result.push_back(e_hand_joint::LEFT_RING_FINGER_DISTAL_INTERPHALANGEAL_JOINT);
			result.push_back(e_hand_joint::LEFT_RING_FINGER_TIP);
			result.push_back(e_hand_joint::LEFT_LITTLE_FINGER_METACARPOPHALANGEAL_JOINT);
			result.push_back(e_hand_joint::LEFT_LITTLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT);
			result.push_back(e_hand_joint::LEFT_LITTLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT);
			result.push_back(e_hand_joint::LEFT_LITTLE_FINGER_TIP);
			result.push_back(e_hand_joint::RIGHT_WRIST);
			result.push_back(e_hand_joint::RIGHT_THUMB_PROXIMAL_INTERPHALANGEAL_JOINT);
			result.push_back(e_hand_joint::RIGHT_THUMB_DISTAL_INTERPHALANGEAL_JOINT);
			result.push_back(e_hand_joint::RIGHT_THUMB_TIP);
			result.push_back(e_hand_joint::RIGHT_INDEX_FINGER_METACARPOPHALANGEAL_JOINT);
			result.push_back(e_hand_joint::RIGHT_INDEX_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT);
			result.push_back(e_hand_joint::RIGHT_INDEX_FINGER_DISTAL_INTERPHALANGEAL_JOINT);
			result.push_back(e_hand_joint::RIGHT_INDEX_FINGER_TIP);
			result.push_back(e_hand_joint::RIGHT_MIDDLE_FINGER_METACARPOPHALANGEAL_JOINT);
			result.push_back(e_hand_joint::RIGHT_MIDDLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT);
			result.push_back(e_hand_joint::RIGHT_MIDDLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT);
			result.push_back(e_hand_joint::RIGHT_MIDDLE_FINGER_TIP);
			result.push_back(e_hand_joint::RIGHT_RING_FINGER_METACARPOPHALANGEAL_JOINT);
			result.push_back(e_hand_joint::RIGHT_RING_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT);
			result.push_back(e_hand_joint::RIGHT_RING_FINGER_DISTAL_INTERPHALANGEAL_JOINT);
			result.push_back(e_hand_joint::RIGHT_RING_FINGER_TIP);
			result.push_back(e_hand_joint::RIGHT_LITTLE_FINGER_METACARPOPHALANGEAL_JOINT);
			result.push_back(e_hand_joint::RIGHT_LITTLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT);
			result.push_back(e_hand_joint::RIGHT_LITTLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT);
			result.push_back(e_hand_joint::RIGHT_LITTLE_FINGER_TIP);
			result.push_back(e_hand_joint::LPT);
			result.push_back(e_hand_joint::LPI);
			result.push_back(e_hand_joint::LPM);
			result.push_back(e_hand_joint::LPR);
			result.push_back(e_hand_joint::LPL);
			result.push_back(e_hand_joint::RPT);
			result.push_back(e_hand_joint::RPI);
			result.push_back(e_hand_joint::RPM);
			result.push_back(e_hand_joint::RPR);
			result.push_back(e_hand_joint::RPL);
			result.push_back(e_hand_joint::END_LT);
			result.push_back(e_hand_joint::END_LI);
			result.push_back(e_hand_joint::END_LM);
			result.push_back(e_hand_joint::END_LR);
			result.push_back(e_hand_joint::END_LL);
			result.push_back(e_hand_joint::END_RT);
			result.push_back(e_hand_joint::END_RI);
			result.push_back(e_hand_joint::END_RM);
			result.push_back(e_hand_joint::END_RR);
			result.push_back(e_hand_joint::END_RL);

			return result;
		}

		bool e_hand_joint_c::is_dummy(e_hand_joint joint)
		{
			if (   joint == e_hand_joint::LPT
				|| joint == e_hand_joint::LPI
				|| joint == e_hand_joint::LPM
				|| joint == e_hand_joint::LPR
				|| joint == e_hand_joint::LPL
			   	|| joint == e_hand_joint::RPT
			   	|| joint == e_hand_joint::RPI
			   	|| joint == e_hand_joint::RPM
			   	|| joint == e_hand_joint::RPR
			   	|| joint == e_hand_joint::RPL
				|| joint == e_hand_joint::END_LT
				|| joint == e_hand_joint::END_LI
				|| joint == e_hand_joint::END_LM
				|| joint == e_hand_joint::END_LR
				|| joint == e_hand_joint::END_LL
			   	|| joint == e_hand_joint::END_RT
			   	|| joint == e_hand_joint::END_RI
			   	|| joint == e_hand_joint::END_RM
			   	|| joint == e_hand_joint::END_RR
			   	|| joint == e_hand_joint::END_RL
					)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		bool e_hand_joint_c::is_palm(e_hand_joint joint)
		{
			if (   joint == e_hand_joint::LEFT_WRIST
				|| joint == e_hand_joint::LEFT_INDEX_FINGER_METACARPOPHALANGEAL_JOINT
				|| joint == e_hand_joint::LEFT_MIDDLE_FINGER_METACARPOPHALANGEAL_JOINT
				|| joint == e_hand_joint::LEFT_RING_FINGER_METACARPOPHALANGEAL_JOINT
				|| joint == e_hand_joint::LEFT_LITTLE_FINGER_METACARPOPHALANGEAL_JOINT
				|| joint == e_hand_joint::RIGHT_WRIST
			   	|| joint == e_hand_joint::RIGHT_INDEX_FINGER_METACARPOPHALANGEAL_JOINT
			   	|| joint == e_hand_joint::RIGHT_MIDDLE_FINGER_METACARPOPHALANGEAL_JOINT
			   	|| joint == e_hand_joint::RIGHT_RING_FINGER_METACARPOPHALANGEAL_JOINT
			   	|| joint == e_hand_joint::RIGHT_LITTLE_FINGER_METACARPOPHALANGEAL_JOINT
					)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		e_hand_joint e_hand_joint_c::parse(std::string str)
		{
			std::string str_l = mstr::to_lower(str);

			std::vector<e_hand_joint> v = e_hand_joint_c::vec();

			for (unsigned int i = 0; i < v.size(); i++)
			{
				std::string t = e_hand_joint_c::str(v.at(i));
				if (str_l == mstr::to_lower(t))
				{
					return v.at(i);
				}
			}

			throw std::invalid_argument("Could not parse the given value since no match was found.");
		}


	} // namespace mae
