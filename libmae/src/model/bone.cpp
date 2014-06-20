/*
 * bone.cpp
 *
 *  Created on: 18.06.2014
 *      Author: keks
 */

#include "bone.hpp"

namespace mae
{

	std::vector<bone> bone::default_bones_ = std::vector<bone>();

	bone::bone(int id, std::string name, int from, int to)
	{
		this->id_ = id;
		this->name_ = name;
		this->from_ = from;
		this->to_ = to;

		this->middle_joint_ = 0;
		this->middle_ = false;
	}

	bone::bone(int id, std::string name, int from, int to, int middle_joint)
	{
		this->id_ = id;
		this->name_ = name;
		this->from_ = from;
		this->to_ = to;

		this->middle_joint_ = middle_joint;
		this->middle_ = true;
	}

	bone::~bone()
	{
	}

	int bone::get_id() const
	{
		return id_;
	}

	std::string bone::get_name() const
	{
		return name_;
	}

	int bone::get_from() const
	{
		return from_;
	}

	int bone::get_to() const
	{
		return to_;
	}

	bool bone::has_middle_joint() const
	{
		return middle_;
	}

	int bone::get_middle_joint() const
	{
		return middle_joint_;
	}

	std::vector<bone> bone::default_bones()
	{
		if (default_bones_.size() > 0)
		{
			return default_bones_;
		}
		else
		{
			std::vector<bone> result;

			result.push_back(bone(MAEB_LEFT_UPPER_ARM, 	maeb_str[MAEB_LEFT_UPPER_ARM], 	MAEJ_LEFT_SHOULDER, 	MAEJ_LEFT_ELBOW));
			result.push_back(bone(MAEB_LEFT_FOREARM, 	maeb_str[MAEB_LEFT_FOREARM], 	MAEJ_LEFT_ELBOW, 		MAEJ_LEFT_HAND));
			result.push_back(bone(MAEB_LEFT_WHOLE_ARM, 	maeb_str[MAEB_LEFT_WHOLE_ARM], 	MAEJ_LEFT_SHOULDER, 	MAEJ_LEFT_HAND, MAEJ_LEFT_ELBOW));

			result.push_back(bone(MAEB_RIGHT_UPPER_ARM, maeb_str[MAEB_RIGHT_UPPER_ARM], MAEJ_RIGHT_SHOULDER, 	MAEJ_RIGHT_ELBOW));
			result.push_back(bone(MAEB_RIGHT_FOREARM, 	maeb_str[MAEB_RIGHT_FOREARM], 	MAEJ_RIGHT_ELBOW, 		MAEJ_RIGHT_HAND));
			result.push_back(bone(MAEB_RIGHT_WHOLE_ARM, maeb_str[MAEB_RIGHT_WHOLE_ARM], MAEJ_RIGHT_SHOULDER, 	MAEJ_RIGHT_HAND, MAEJ_RIGHT_ELBOW));

			result.push_back(bone(MAEB_LEFT_THIGH, 		maeb_str[MAEB_LEFT_THIGH], 		MAEJ_LEFT_HIP, 			MAEJ_LEFT_KNEE));
			result.push_back(bone(MAEB_LEFT_SHANK, 		maeb_str[MAEB_LEFT_SHANK], 		MAEJ_LEFT_KNEE, 		MAEJ_LEFT_FOOT));
			result.push_back(bone(MAEB_LEFT_WHOLE_LEG, 	maeb_str[MAEB_LEFT_WHOLE_LEG], 	MAEJ_LEFT_HIP, 			MAEJ_LEFT_FOOT, MAEJ_LEFT_KNEE));

			result.push_back(bone(MAEB_RIGHT_THIGH, 	maeb_str[MAEB_RIGHT_THIGH], 	MAEJ_RIGHT_HIP, 		MAEJ_RIGHT_KNEE));
			result.push_back(bone(MAEB_RIGHT_SHANK, 	maeb_str[MAEB_RIGHT_SHANK], 	MAEJ_RIGHT_KNEE, 		MAEJ_RIGHT_FOOT));
			result.push_back(bone(MAEB_RIGHT_WHOLE_LEG, maeb_str[MAEB_RIGHT_WHOLE_LEG], MAEJ_RIGHT_HIP, 		MAEJ_RIGHT_FOOT, MAEJ_RIGHT_KNEE));

			result.push_back(bone(MAEB_HEAD, 			maeb_str[MAEB_HEAD], 			MAEJ_NECK, 				MAEJ_HEAD));

			default_bones_ = result;
			return result;
		}
	}


} // namespace mae
