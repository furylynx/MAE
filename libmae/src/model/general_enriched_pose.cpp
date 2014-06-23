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
		this->hashmap_keypose = std::unordered_map<int, bool>();
		this->hashmap_inmotion = std::unordered_map<int, bool>();
	}

	general_enriched_pose::general_enriched_pose(std::shared_ptr<general_pose> pose)
			: general_pose(pose->get_directions(), pose->get_distances())
	{
		this->hashmap_keypose = std::unordered_map<int, bool>();
		this->hashmap_inmotion = std::unordered_map<int, bool>();
	}

	general_enriched_pose::general_enriched_pose(std::unordered_map<int, bool> hashmap_keypose,
			std::unordered_map<int, bool> hashmap_inmotion)
	{
		this->hashmap_keypose = hashmap_keypose;
		this->hashmap_inmotion = hashmap_inmotion;
	}

	general_enriched_pose::~general_enriched_pose()
	{
		this->hashmap_keypose.clear();
		this->hashmap_inmotion.clear();
	}

	void general_enriched_pose::setKeyPose(int bodyPart, bool isKeyPose)
	{

		if (hashmap_keypose.find(bodyPart) == hashmap_keypose.end())
		{
			//key is not in map
			hashmap_keypose.insert(std::make_pair(bodyPart, isKeyPose));

		}
		else
		{
			//key already exists and will therefore be overwritten
			hashmap_keypose[bodyPart] = isKeyPose;
		}

	}

	bool general_enriched_pose::isKeyPose(int bodyPart)
	{
		if (hashmap_keypose.find(bodyPart) == hashmap_keypose.end())
		{
			return hashmap_keypose[bodyPart];
		}
		else
		{
			return false;
		}
	}

	void general_enriched_pose::setInMotion(int bodyPart, bool isInMotion)
	{

		if (hashmap_inmotion.find(bodyPart) == hashmap_inmotion.end())
		{
			//key is not in map
			hashmap_inmotion.insert(std::make_pair(bodyPart, isInMotion));

		}
		else
		{
			//key already exists and will therefore be overwritten
			hashmap_inmotion[bodyPart] = isInMotion;
		}
	}

	bool general_enriched_pose::isInMotion(int bodyPart)
	{

		if (hashmap_inmotion.find(bodyPart) == hashmap_inmotion.end())
		{
			return hashmap_inmotion[bodyPart];
		}
		else
		{
			return false;
		}
	}

} // namespace mae
