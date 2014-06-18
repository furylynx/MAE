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

		bvh_spec::bvh_spec(std::unordered_map<std::string, int> string_id_map,
				std::unordered_map<std::string, bool> string_torso_map)
		{
			this->string_id_map_ = string_id_map;
			this->string_torso_map_ = string_torso_map;
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

		std::shared_ptr<bvh_spec> bvh_spec::default_spec()
		{
			std::unordered_map<std::string, int> string_id_map;

			//fill joint_str map
			for (int i = MAEJ_INVALID + 1; i < MAEJ_SIZE; i++)
			{
				string_id_map.insert(std::make_pair(mstr::to_lower(maej_str[i]), i));
			}

			//IDs for end sites
			string_id_map.insert(std::make_pair("end site#1", MAEJ_END_LH));
			string_id_map.insert(std::make_pair("end site#2", MAEJ_END_RH));
			string_id_map.insert(std::make_pair("end site#3", MAEJ_END_LF));
			string_id_map.insert(std::make_pair("end site#4", MAEJ_END_RF));
			string_id_map.insert(std::make_pair("end site#5", MAEJ_END_H));

			return std::shared_ptr<bvh_spec>(new bvh_spec(string_id_map, std::unordered_map<std::string, bool>()));
		}

	} // namespace fl
} // namespace mae
