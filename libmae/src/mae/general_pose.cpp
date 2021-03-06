#include "general_pose.hpp"

namespace mae
{
		general_pose::general_pose()
		{
		}

		general_pose::~general_pose()
		{
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

		int general_pose::get_direction(int body_part) const
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

		void general_pose::set_distance(int body_part, int direction, double distance)
		{
			if (hashmap_directions_.find(direction) == hashmap_directions_.end())
			{
				hashmap_directions_.insert(std::make_pair(direction, 0));
				directions_.push_back(direction);
			}

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

		double general_pose::get_distance(int body_part, int direction) const
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
					return hm_dist_val.at(direction);
				}
			}
		}

		void general_pose::set_rotation(int body_part, double rotation)
		{
			hashmap_rotation_[body_part] = rotation;
		}

		double general_pose::get_rotation(int body_part) const
		{
			if (hashmap_rotation_.find(body_part) == hashmap_rotation_.end())
			{
				throw std::invalid_argument("Body part not listed in the pose's map.");
			}
			else
			{
				return hashmap_rotation_.at(body_part);
			}
		}

		std::list<int> general_pose::get_body_parts() const
		{
			return body_parts_;
		}

		std::list<int> general_pose::get_directions() const
		{
			return directions_;
		}

} // namespace mae
