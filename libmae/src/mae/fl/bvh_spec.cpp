#include "bvh_spec.hpp"

namespace mae
{
	namespace fl
	{

		bvh_spec::bvh_spec(std::string left_anchor, std::string right_anchor, std::string top_anchor, std::string bottom_anchor, std::map<std::string, int> string_id_map,
				std::map<std::string, bool> string_basis_map)
		{
			left_anchor_ = left_anchor;
			right_anchor_ = right_anchor;
			top_anchor_ = top_anchor;
			bottom_anchor_ = bottom_anchor;

			string_id_map_ = string_id_map;
			string_basis_map_ = string_basis_map;
		}

		bvh_spec::~bvh_spec()
		{
		}

		std::map<std::string, int> bvh_spec::get_id_map() const
		{
			return string_id_map_;
		}

		std::map<std::string, bool> bvh_spec::get_torso_map() const
		{
			return get_basis_map();
		}

		std::map<std::string, bool> bvh_spec::get_basis_map() const
		{
			return string_basis_map_;
		}

		std::string bvh_spec::get_left_anchor()
		{
			return left_anchor_;
		}

		std::string bvh_spec::get_right_anchor()
		{
			return right_anchor_;
		}

		std::string bvh_spec::get_top_anchor()
		{
			return top_anchor_;
		}

		std::string bvh_spec::get_bottom_anchor()
		{
			return bottom_anchor_;
		}

		std::shared_ptr<bvh_spec> bvh_spec::default_spec()
		{
			std::map<std::string, int> string_id_map;
			std::map<std::string, bool> string_torso_map;

			//fill joint_str map
			for (e_joint j : e_joint_c::vec())
			{
				string_id_map.insert(std::make_pair(mstr::to_lower(e_joint_c::str(j)), e_joint_c::to_int(j)));

				if (e_joint_c::is_torso(j))
				{
					string_torso_map.insert(std::make_pair(mstr::to_lower(e_joint_c::str(j)), true));
				}
			}

			//IDs for end sites
			string_id_map.insert(std::make_pair("end site#1", e_joint_c::to_int(e_joint::END_LH)));
			string_id_map.insert(std::make_pair("end site#2", e_joint_c::to_int(e_joint::END_RH)));
			string_id_map.insert(std::make_pair("end site#3", e_joint_c::to_int(e_joint::END_LF)));
			string_id_map.insert(std::make_pair("end site#4", e_joint_c::to_int(e_joint::END_RF)));
			string_id_map.insert(std::make_pair("end site#5", e_joint_c::to_int(e_joint::END_H)));

			//left-right top-down directions
			std::string left_anchor = mstr::to_lower(e_joint_c::str(e_joint::LEFT_SHOULDER));
			std::string right_anchor = mstr::to_lower(e_joint_c::str(e_joint::RIGHT_SHOULDER));
			std::string top_anchor = mstr::to_lower(e_joint_c::str(e_joint::NECK));
			std::string bottom_anchor = mstr::to_lower(e_joint_c::str(e_joint::TORSO));

			return std::shared_ptr<bvh_spec>(new bvh_spec(left_anchor, right_anchor, top_anchor, bottom_anchor, string_id_map, string_torso_map));
		}

		std::shared_ptr<bvh_spec> bvh_spec::default_hand_spec(bool is_left)
		{
			std::map<std::string, int> string_id_map;
			std::map<std::string, bool> string_palm_map;

			//fill joint_str map
			for (e_hand_joint j : e_hand_joint_c::vec())
			{
				string_id_map.insert(std::make_pair(mstr::to_lower(e_hand_joint_c::str(j)), e_hand_joint_c::to_int(j)));

				if (e_hand_joint_c::is_palm(j))
				{
					string_palm_map.insert(std::make_pair(mstr::to_lower(e_hand_joint_c::str(j)), true));
				}
			}

			//IDs for end sites
			string_id_map.insert(std::make_pair("end site#1", e_hand_joint_c::to_int(e_hand_joint::END_LT)));
			string_id_map.insert(std::make_pair("end site#2", e_hand_joint_c::to_int(e_hand_joint::END_LI)));
			string_id_map.insert(std::make_pair("end site#3", e_hand_joint_c::to_int(e_hand_joint::END_LM)));
			string_id_map.insert(std::make_pair("end site#4", e_hand_joint_c::to_int(e_hand_joint::END_LR)));
			string_id_map.insert(std::make_pair("end site#5", e_hand_joint_c::to_int(e_hand_joint::END_LL)));
			string_id_map.insert(std::make_pair("end site#6", e_hand_joint_c::to_int(e_hand_joint::END_LT)));
			string_id_map.insert(std::make_pair("end site#7", e_hand_joint_c::to_int(e_hand_joint::END_LI)));
			string_id_map.insert(std::make_pair("end site#8", e_hand_joint_c::to_int(e_hand_joint::END_LM)));
			string_id_map.insert(std::make_pair("end site#9", e_hand_joint_c::to_int(e_hand_joint::END_LR)));
			string_id_map.insert(std::make_pair("end site#10",e_hand_joint_c::to_int(e_hand_joint::END_LL)));

			std::string left_anchor;
			std::string right_anchor;
			std::string top_anchor;
			std::string bottom_anchor;

			if (is_left)
			{
				left_anchor = mstr::to_lower(e_hand_joint_c::str(e_hand_joint::LEFT_INDEX_FINGER_METACARPOPHALANGEAL_JOINT));
				right_anchor = mstr::to_lower(e_hand_joint_c::str(e_hand_joint::LEFT_LITTLE_FINGER_METACARPOPHALANGEAL_JOINT));
				top_anchor = mstr::to_lower(e_hand_joint_c::str(e_hand_joint::LEFT_MIDDLE_FINGER_METACARPOPHALANGEAL_JOINT));
				bottom_anchor = mstr::to_lower(e_hand_joint_c::str(e_hand_joint::LEFT_WRIST));
			}
			else
			{
				left_anchor = mstr::to_lower(e_hand_joint_c::str(e_hand_joint::RIGHT_LITTLE_FINGER_METACARPOPHALANGEAL_JOINT));
				right_anchor = mstr::to_lower(e_hand_joint_c::str(e_hand_joint::RIGHT_INDEX_FINGER_METACARPOPHALANGEAL_JOINT));
				top_anchor = mstr::to_lower(e_hand_joint_c::str(e_hand_joint::RIGHT_MIDDLE_FINGER_METACARPOPHALANGEAL_JOINT));
				bottom_anchor = mstr::to_lower(e_hand_joint_c::str(e_hand_joint::RIGHT_WRIST));
			}

			return std::shared_ptr<bvh_spec>(new bvh_spec(left_anchor, right_anchor, top_anchor, bottom_anchor, string_id_map, string_palm_map));
		}
        
        
        std::shared_ptr<bvh_spec> bvh_spec::motion_builder_spec()
        {
            std::map<std::string, int> string_id_map;
            std::map<std::string, bool> string_torso_map;
            
            //fill joint_str map
            for (e_joint j : e_joint_c::vec())
            {
                string_id_map.insert(std::make_pair(mstr::to_lower(e_joint_c::str(j)), e_joint_c::to_int(j)));
                
                if (e_joint_c::is_torso(j))
                {
                    string_torso_map.insert(std::make_pair(mstr::to_lower(e_joint_c::str(j)), true));
                }
            }
            string_id_map.insert(std::make_pair("lshoulder", e_joint_c::to_int(e_joint::LEFT_SHOULDER)));
            string_id_map.insert(std::make_pair("rshoulder", e_joint_c::to_int(e_joint::RIGHT_SHOULDER)));
            string_id_map.insert(std::make_pair("middlespine", e_joint_c::to_int(e_joint::TORSO)));
    
            string_torso_map.insert(std::make_pair("lshoulder", true));
            string_torso_map.insert(std::make_pair("rshoulder", true));
            string_torso_map.insert(std::make_pair("lthigh", true));
            string_torso_map.insert(std::make_pair("rthigh", true));
            string_torso_map.insert(std::make_pair("middlespine", true));
            
            //IDs for end sites
//            string_id_map.insert(std::make_pair("end site#1", e_joint_c::to_int(e_joint::END_LH)));
//            string_id_map.insert(std::make_pair("end site#2", e_joint_c::to_int(e_joint::END_RH)));
//            string_id_map.insert(std::make_pair("end site#3", e_joint_c::to_int(e_joint::END_LF)));
//            string_id_map.insert(std::make_pair("end site#4", e_joint_c::to_int(e_joint::END_RF)));
//            string_id_map.insert(std::make_pair("end site#5", e_joint_c::to_int(e_joint::END_H)));
            
            //left-right top-down directions
            std::string left_anchor = "lshoulder";
            std::string right_anchor = "rshoulder";
            std::string top_anchor = mstr::to_lower(e_joint_c::str(e_joint::NECK));
            std::string bottom_anchor = "middlespine";
            
            return std::shared_ptr<bvh_spec>(new bvh_spec(left_anchor, right_anchor, top_anchor, bottom_anchor, string_id_map, string_torso_map));
        }
		
	} // namespace fl
} // namespace mae
