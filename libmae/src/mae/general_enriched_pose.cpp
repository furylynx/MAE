#include "general_enriched_pose.hpp"

namespace mae
{

	general_enriched_pose::general_enriched_pose()
			: general_pose()
	{
		this->hashmap_keypose_ = std::unordered_map<int, bool>();
		this->hashmap_inmotion_ = std::unordered_map<int, bool>();
	}

	general_enriched_pose::general_enriched_pose(std::shared_ptr<general_pose> pose)
			: general_pose()
	{
		//fill hashmaps with pose's data
		std::list<int> body_parts = pose->get_body_parts();
		std::list<int> directions = pose->get_directions();
		for (std::list<int>::iterator bp_it = body_parts.begin(); bp_it != body_parts.end(); bp_it++)
		{
			set_direction(*bp_it, pose->get_direction(*bp_it));
			set_rotation(*bp_it, pose->get_rotation(*bp_it));

			for (std::list<int>::iterator d_it = directions.begin(); d_it != directions.end(); d_it++)
			{
				set_distance(*bp_it, *d_it, pose->get_distance(*bp_it, *d_it));
			}
		}
	}

	general_enriched_pose::~general_enriched_pose()
	{
		this->hashmap_keypose_.clear();
		this->hashmap_inmotion_.clear();
	}

	void general_enriched_pose::set_key_pose(int bodyPart, bool isKeyPose)
	{

		if (hashmap_keypose_.find(bodyPart) == hashmap_keypose_.end())
		{
			//key is not in map
			hashmap_keypose_.insert(std::make_pair(bodyPart, isKeyPose));

		}
		else
		{
			//key already exists and will therefore be overwritten
			hashmap_keypose_[bodyPart] = isKeyPose;
		}

	}

	bool general_enriched_pose::is_key_pose(int bodyPart)
	{
		if (hashmap_keypose_.find(bodyPart) == hashmap_keypose_.end())
		{
			throw std::invalid_argument("Body part not listed in the enriched pose's map.");
		}
		else
		{
			return hashmap_keypose_.at(bodyPart);
		}
	}

	void general_enriched_pose::set_in_motion(int bodyPart, bool isInMotion)
	{

		if (hashmap_inmotion_.find(bodyPart) == hashmap_inmotion_.end())
		{
			//key is not in map
			hashmap_inmotion_.insert(std::make_pair(bodyPart, isInMotion));

		}
		else
		{
			//key already exists and will therefore be overwritten
			hashmap_inmotion_[bodyPart] = isInMotion;
		}
	}

	bool general_enriched_pose::is_in_motion(int bodyPart)
	{

		if (hashmap_inmotion_.find(bodyPart) == hashmap_inmotion_.end())
		{
			throw std::invalid_argument("Body part not listed in the enriched pose's map.");
		}
		else
		{
			return hashmap_inmotion_.at(bodyPart);
		}
	}

} // namespace mae
