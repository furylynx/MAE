/*
 * GeneralPose.cpp
 *
 *  Created on: 19.05.2014
 *      Author: keks
 */

#include "general_pose.hpp"

namespace mae
{
		general_pose::general_pose()
		{
			this->hashmap_direction_ = std::unordered_map<int, int>();
			this->hashmap_distance_ = std::unordered_map<int, std::unordered_map<int, double> >();
		}

		general_pose::general_pose(std::unordered_map<int, int> hashmap_direction,
				std::unordered_map<int, std::unordered_map<int, double> > hashmap_distance)
		{
			this->hashmap_direction_ = hashmap_direction;
			this->hashmap_distance_ = hashmap_distance;
		}

		general_pose::~general_pose()
		{
			hashmap_direction_.clear();
			hashmap_distance_.clear();
		}

		void general_pose::set_direction(int body_part, int direction)
		{

			if (hashmap_direction_.find(body_part) == hashmap_direction_.end())
			{
				//key is not in map
				hashmap_direction_.insert(std::make_pair(body_part, direction));
				body_parts_.push_back(body_part);

			}
			else
			{
				//key already exists and will therefore be overwritten
				hashmap_direction_[body_part] = direction;
			}

		}

		int general_pose::get_direction(int body_part)
		{

			if (hashmap_direction_.find(body_part) == hashmap_direction_.end())
			{
				throw std::invalid_argument("Body part not listed in the pose's map.");
			}
			else
			{
				return hashmap_direction_.at(body_part);
			}

		}

		std::unordered_map<int, int> general_pose::get_directions()
		{
			return hashmap_direction_;
		}

		void general_pose::set_distance(int body_part, int direction, double distance)
		{
			if (hashmap_distance_.find(body_part) == hashmap_distance_.end())
			{
				//key is not in map
				std::unordered_map<int, double> hm_dist_val = std::unordered_map<int, double>();
				hm_dist_val.insert(std::make_pair(direction, distance));

				hashmap_distance_.insert(std::make_pair(body_part, hm_dist_val));

			}
			else
			{
				//key already exists, load inner hashmap containing assignments of direction to distance

				std::unordered_map<int, double> hm_dist_val = hashmap_distance_[body_part];

				if (hm_dist_val.find(direction) == hm_dist_val.end())
				{
					//no key present for the given direction therefore a new one will be created
					hm_dist_val.insert(std::make_pair(direction, distance));
					hashmap_distance_[body_part] = hm_dist_val;
				}
				else
				{
					//update distance value for direction
					hm_dist_val[direction] = distance;
				}
			}

		}

		double general_pose::get_distance(int body_part, int direction)
		{

			if (hashmap_distance_.find(body_part) == hashmap_distance_.end())
			{
				throw std::invalid_argument("Body part not listed in the pose's map.");
			}
			else
			{
				std::unordered_map<int, double> hm_dist_val = hashmap_distance_.at(body_part);

				if (hm_dist_val.find(direction) == hm_dist_val.end())
				{
					throw std::invalid_argument("Direction not listed in the map.");
				}
				else
				{
					return hm_dist_val[direction];
				}
			}
		}

		std::unordered_map<int, std::unordered_map<int, double> > general_pose::get_distances()
		{
			return hashmap_distance_;
		}

		std::list<int> general_pose::get_body_parts()
		{
			return body_parts_;
		}

} // namespace mae
