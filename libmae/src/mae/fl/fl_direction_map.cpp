#include "fl_direction_map.hpp"

namespace mae
{
	namespace fl
	{

		fl_direction_map::fl_direction_map()
		{

			//initialize directions on circle
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::P_H), std::make_shared<mae::math::vec3d>(-1, 0, 0)->normalize()));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::P_M), std::make_shared<mae::math::vec3d>(0, 0, 0)->normalize()));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::P_L), std::make_shared<mae::math::vec3d>(1, 0, 0)->normalize()));

			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::L_H), std::make_shared<mae::math::vec3d>(-1, 1, 0)->normalize()));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::L_M), std::make_shared<mae::math::vec3d>(0, 1, 0)->normalize()));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::L_L), std::make_shared<mae::math::vec3d>(1, 1, 0)->normalize()));

			map_directions_.insert(
					std::make_pair(e_fl_direction_c::to_int(e_fl_direction::D_F_L_H), std::make_shared<mae::math::vec3d>(-1, 1, 1)->normalize()));
			map_directions_.insert(
					std::make_pair(e_fl_direction_c::to_int(e_fl_direction::D_F_L_M), std::make_shared<mae::math::vec3d>(0, 1, 1)->normalize()));
			map_directions_.insert(
					std::make_pair(e_fl_direction_c::to_int(e_fl_direction::D_F_L_L), std::make_shared<mae::math::vec3d>(1, 1, 1)->normalize()));

			map_directions_.insert(
					std::make_pair(e_fl_direction_c::to_int(e_fl_direction::F_L_H), std::make_shared<mae::math::vec3d>(-1, 0, 1)->normalize()));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::F_L_M), std::make_shared<mae::math::vec3d>(0, 0, 1)->normalize()));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::F_L_L), std::make_shared<mae::math::vec3d>(1, 0, 1)->normalize()));

			map_directions_.insert(
					std::make_pair(e_fl_direction_c::to_int(e_fl_direction::F_R_H), std::make_shared<mae::math::vec3d>(-1, 0, 1)->normalize()));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::F_R_M), std::make_shared<mae::math::vec3d>(0, 0, 1)->normalize()));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::F_R_L), std::make_shared<mae::math::vec3d>(1, 0, 1)->normalize()));

			map_directions_.insert(
					std::make_pair(e_fl_direction_c::to_int(e_fl_direction::D_F_R_H), std::make_shared<mae::math::vec3d>(-1, -1, 1)->normalize()));
			map_directions_.insert(
					std::make_pair(e_fl_direction_c::to_int(e_fl_direction::D_F_R_M), std::make_shared<mae::math::vec3d>(0, -1, 1)->normalize()));
			map_directions_.insert(
					std::make_pair(e_fl_direction_c::to_int(e_fl_direction::D_F_R_L), std::make_shared<mae::math::vec3d>(1, -1, 1)->normalize()));

			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::R_H), std::make_shared<mae::math::vec3d>(-1, -1, 0)->normalize()));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::R_M), std::make_shared<mae::math::vec3d>(0, -1, 0)->normalize()));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::R_L), std::make_shared<mae::math::vec3d>(1, -1, 0)->normalize()));

			map_directions_.insert(
					std::make_pair(e_fl_direction_c::to_int(e_fl_direction::D_B_R_H), std::make_shared<mae::math::vec3d>(-1, -1, -1)->normalize()));
			map_directions_.insert(
					std::make_pair(e_fl_direction_c::to_int(e_fl_direction::D_B_R_M), std::make_shared<mae::math::vec3d>(0, -1, -1)->normalize()));
			map_directions_.insert(
					std::make_pair(e_fl_direction_c::to_int(e_fl_direction::D_B_R_L), std::make_shared<mae::math::vec3d>(1, -1, -1)->normalize()));

			map_directions_.insert(
					std::make_pair(e_fl_direction_c::to_int(e_fl_direction::B_R_H), std::make_shared<mae::math::vec3d>(-1, 0, -1)->normalize()));
			map_directions_.insert(
					std::make_pair(e_fl_direction_c::to_int(e_fl_direction::B_R_M), std::make_shared<mae::math::vec3d>(0, 0, -1)->normalize()));
			map_directions_.insert(
					std::make_pair(e_fl_direction_c::to_int(e_fl_direction::B_R_L), std::make_shared<mae::math::vec3d>(1, 0, -1)->normalize()));

			map_directions_.insert(
					std::make_pair(e_fl_direction_c::to_int(e_fl_direction::B_L_H), std::make_shared<mae::math::vec3d>(-1, 0, -1)->normalize()));
			map_directions_.insert(
					std::make_pair(e_fl_direction_c::to_int(e_fl_direction::B_L_M), std::make_shared<mae::math::vec3d>(0, 0, -1)->normalize()));
			map_directions_.insert(
					std::make_pair(e_fl_direction_c::to_int(e_fl_direction::B_L_L), std::make_shared<mae::math::vec3d>(1, 0, -1)->normalize()));

			map_directions_.insert(
					std::make_pair(e_fl_direction_c::to_int(e_fl_direction::D_B_L_H), std::make_shared<mae::math::vec3d>(-1, 1, -1)->normalize()));
			map_directions_.insert(
					std::make_pair(e_fl_direction_c::to_int(e_fl_direction::D_B_L_M), std::make_shared<mae::math::vec3d>(0, 1, -1)->normalize()));
			map_directions_.insert(
					std::make_pair(e_fl_direction_c::to_int(e_fl_direction::D_B_L_L), std::make_shared<mae::math::vec3d>(1, 1, -1)->normalize()));

		}

		fl_direction_map::~fl_direction_map()
		{
		}

		std::shared_ptr<mae::math::vec3d> fl_direction_map::get_vec(e_fl_direction fldirection) const
		{
			return map_directions_.at(e_fl_direction_c::to_int(fldirection));
		}

		std::shared_ptr<mae::math::vec3d> fl_direction_map::get_vec(laban::mv::e_direction direction, laban::mv::e_level level) const
		{
			return get_vec(e_fl_direction_c::dir(direction,level));
		}

	} // namespace fl
} // namespace mae
