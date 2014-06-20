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
			this->hashmap_direction = std::unordered_map<int, int>();
			this->hashmap_distance = std::unordered_map<int, std::unordered_map<int, double> >();
		}

		general_pose::general_pose(std::unordered_map<int, int> hashmap_direction,
				std::unordered_map<int, std::unordered_map<int, double> > hashmap_distance)
		{
			this->hashmap_direction = hashmap_direction;
			this->hashmap_distance = hashmap_distance;
		}

		general_pose::~general_pose()
		{
			hashmap_direction.clear();
			hashmap_distance.clear();
		}

		void general_pose::set_direction(int body_part, int direction)
		{

			if (hashmap_direction.find(body_part) == hashmap_direction.end())
			{
				//key is not in map
				hashmap_direction.insert(std::make_pair(body_part, direction));

			}
			else
			{
				//key already exists and will therefore be overwritten
				hashmap_direction[body_part] = direction;
			}

		}

		int general_pose::get_direction(int body_part)
		{

			if (hashmap_direction.find(body_part) == hashmap_direction.end())
			{
				return 0;
			}
			else
			{
				return hashmap_direction[body_part];
			}

		}

		void general_pose::set_distance(int body_part, int direction, double distance)
		{
			if (hashmap_distance.find(body_part) == hashmap_distance.end())
			{
				//key is not in map
				std::unordered_map<int, double> hm_dist_val = std::unordered_map<int, double>();
				hm_dist_val.insert(std::make_pair(direction, distance));

				hashmap_distance.insert(std::make_pair(body_part, hm_dist_val));

			}
			else
			{
				//key already exists, load inner hashmap containing assignments of direction to distance

				std::unordered_map<int, double> hm_dist_val = hashmap_distance[body_part];

				if (hm_dist_val.find(direction) == hm_dist_val.end())
				{
					//no key present for the given direction therefore a new one will be created
					hm_dist_val.insert(std::make_pair(direction, distance));
					hashmap_distance[body_part] = hm_dist_val;
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

			if (hashmap_distance.find(body_part) == hashmap_distance.end())
			{
				return -1;
			}
			else
			{
				std::unordered_map<int, double> hm_dist_val = hashmap_distance[body_part];

				if (hm_dist_val.find(direction) == hm_dist_val.end())
				{
					return -1;
				}
				else
				{
					return hm_dist_val[direction];
				}
			}
		}

} // namespace mae
