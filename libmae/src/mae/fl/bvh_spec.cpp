/*
 * bvhspec.cpp
 *
 *  Created on: 20.06.2014
 *      Author: keks
 */

#include "bvh_spec.hpp"

namespace mae
{
	namespace fl
	{

		bvh_spec::bvh_spec(std::string left_anchor, std::string right_anchor, std::string top_anchor, std::string bottom_anchor, std::unordered_map<std::string, int> string_id_map,
				std::unordered_map<std::string, bool> string_torso_map)
		{
			left_anchor_ = left_anchor;
			right_anchor_ = right_anchor;
			top_anchor_ = top_anchor;
			bottom_anchor_ = bottom_anchor;

			string_id_map_ = string_id_map;
			string_torso_map_ = string_torso_map;
		}

		bvh_spec::~bvh_spec()
		{
		}

		std::unordered_map<std::string, int> bvh_spec::get_id_map() const
		{
			return string_id_map_;
		}

		std::unordered_map<std::string, bool> bvh_spec::get_torso_map() const
		{
			return string_torso_map_;
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
			std::unordered_map<std::string, int> string_id_map;

			//fill joint_str map
			for (e_joint j : e_joint_c::vec())
			{
				string_id_map.insert(std::make_pair(mstr::to_lower(e_joint_c::str(j)), e_joint_c::to_int(j)));
			}

			//IDs for end sites
			string_id_map.insert(std::make_pair("end site#1", e_joint_c::to_int(e_joint::END_LH)));
			string_id_map.insert(std::make_pair("end site#2", e_joint_c::to_int(e_joint::END_RH)));
			string_id_map.insert(std::make_pair("end site#3", e_joint_c::to_int(e_joint::END_LF)));
			string_id_map.insert(std::make_pair("end site#4", e_joint_c::to_int(e_joint::END_RF)));
			string_id_map.insert(std::make_pair("end site#5", e_joint_c::to_int(e_joint::END_H)));

			std::unordered_map<std::string, bool> string_torso_map;
			string_torso_map.insert(std::make_pair(mstr::to_lower(e_joint_c::str(e_joint::TORSO)), true));
			string_torso_map.insert(std::make_pair(mstr::to_lower(e_joint_c::str(e_joint::LEFT_SHOULDER)), true));
			string_torso_map.insert(std::make_pair(mstr::to_lower(e_joint_c::str(e_joint::RIGHT_SHOULDER)), true));
			string_torso_map.insert(std::make_pair(mstr::to_lower(e_joint_c::str(e_joint::LEFT_HIP)), true));
			string_torso_map.insert(std::make_pair(mstr::to_lower(e_joint_c::str(e_joint::RIGHT_HIP)), true));
			string_torso_map.insert(std::make_pair(mstr::to_lower(e_joint_c::str(e_joint::NECK)), true));

			std::string left_anchor = mstr::to_lower(e_joint_c::str(e_joint::LEFT_SHOULDER));
			std::string right_anchor = mstr::to_lower(e_joint_c::str(e_joint::RIGHT_SHOULDER));
			std::string top_anchor = mstr::to_lower(e_joint_c::str(e_joint::NECK));
			std::string bottom_anchor = mstr::to_lower(e_joint_c::str(e_joint::TORSO));

			return std::shared_ptr<bvh_spec>(new bvh_spec(left_anchor, right_anchor, top_anchor, bottom_anchor, string_id_map, string_torso_map));
		}

	} // namespace fl
} // namespace mae
