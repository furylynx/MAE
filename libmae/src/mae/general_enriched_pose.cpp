/*
 * GeneralEnrichedPose.cpp
 *
 *  Created on: 19.05.2014
 *      Author: keks
 */

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
			: general_pose(pose->get_directions(), pose->get_distances())
	{
		this->hashmap_keypose_ = std::unordered_map<int, bool>();
		this->hashmap_inmotion_ = std::unordered_map<int, bool>();
	}

	general_enriched_pose::general_enriched_pose(std::unordered_map<int, bool> hashmap_keypose,
			std::unordered_map<int, bool> hashmap_inmotion)
	{
		this->hashmap_keypose_ = hashmap_keypose;
		this->hashmap_inmotion_ = hashmap_inmotion;
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
