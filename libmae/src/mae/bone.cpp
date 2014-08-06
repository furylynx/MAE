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
		if (id == RESERVED_TOP_DOWN || id == RESERVED_RIGHT_LEFT)
		{
			throw std::invalid_argument("Reserved values cannot be used as ID.");
		}

		this->id_ = id;
		this->name_ = name;
		this->from_ = from;
		this->to_ = to;

		this->middle_joint_ = 0;
		this->middle_ = false;
	}

	bone::bone(int id, std::string name, int from, int to, int middle_joint)
	{
		if (id == RESERVED_TOP_DOWN || id == RESERVED_RIGHT_LEFT)
		{
			throw std::invalid_argument("Reserved values cannot be used as ID.");
		}

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

			result.push_back(bone(e_bone_c::to_int(e_bone::LEFT_UPPER_ARM), 	e_bone_c::str(e_bone::LEFT_UPPER_ARM), 	e_joint_c::to_int(e_joint::LEFT_SHOULDER), 		e_joint_c::to_int(e_joint::LEFT_ELBOW)));
			result.push_back(bone(e_bone_c::to_int(e_bone::LEFT_FOREARM), 		e_bone_c::str(e_bone::LEFT_FOREARM), 	e_joint_c::to_int(e_joint::LEFT_ELBOW), 		e_joint_c::to_int(e_joint::LEFT_HAND)));
			result.push_back(bone(e_bone_c::to_int(e_bone::LEFT_WHOLE_ARM), 	e_bone_c::str(e_bone::LEFT_WHOLE_ARM), 	e_joint_c::to_int(e_joint::LEFT_SHOULDER), 		e_joint_c::to_int(e_joint::LEFT_HAND), e_joint_c::to_int(e_joint::LEFT_ELBOW)));

			result.push_back(bone(e_bone_c::to_int(e_bone::RIGHT_UPPER_ARM),	e_bone_c::str(e_bone::RIGHT_UPPER_ARM), e_joint_c::to_int(e_joint::RIGHT_SHOULDER), 	e_joint_c::to_int(e_joint::RIGHT_ELBOW)));
			result.push_back(bone(e_bone_c::to_int(e_bone::RIGHT_FOREARM), 		e_bone_c::str(e_bone::RIGHT_FOREARM), 	e_joint_c::to_int(e_joint::RIGHT_ELBOW), 		e_joint_c::to_int(e_joint::RIGHT_HAND)));
			result.push_back(bone(e_bone_c::to_int(e_bone::RIGHT_WHOLE_ARM), 	e_bone_c::str(e_bone::RIGHT_WHOLE_ARM), e_joint_c::to_int(e_joint::RIGHT_SHOULDER), 	e_joint_c::to_int(e_joint::RIGHT_HAND), e_joint_c::to_int(e_joint::RIGHT_ELBOW)));

			result.push_back(bone(e_bone_c::to_int(e_bone::LEFT_THIGH), 		e_bone_c::str(e_bone::LEFT_THIGH), 		e_joint_c::to_int(e_joint::LEFT_HIP), 			e_joint_c::to_int(e_joint::LEFT_KNEE)));
			result.push_back(bone(e_bone_c::to_int(e_bone::LEFT_SHANK), 		e_bone_c::str(e_bone::LEFT_SHANK), 		e_joint_c::to_int(e_joint::LEFT_KNEE), 			e_joint_c::to_int(e_joint::LEFT_FOOT)));
			result.push_back(bone(e_bone_c::to_int(e_bone::LEFT_WHOLE_LEG), 	e_bone_c::str(e_bone::LEFT_WHOLE_LEG), 	e_joint_c::to_int(e_joint::LEFT_HIP), 			e_joint_c::to_int(e_joint::LEFT_FOOT), e_joint_c::to_int(e_joint::LEFT_KNEE)));

			result.push_back(bone(e_bone_c::to_int(e_bone::RIGHT_THIGH), 		e_bone_c::str(e_bone::RIGHT_THIGH), 	e_joint_c::to_int(e_joint::RIGHT_HIP), 			e_joint_c::to_int(e_joint::RIGHT_KNEE)));
			result.push_back(bone(e_bone_c::to_int(e_bone::RIGHT_SHANK), 		e_bone_c::str(e_bone::RIGHT_SHANK), 	e_joint_c::to_int(e_joint::RIGHT_KNEE), 		e_joint_c::to_int(e_joint::RIGHT_FOOT)));
			result.push_back(bone(e_bone_c::to_int(e_bone::RIGHT_WHOLE_LEG), 	e_bone_c::str(e_bone::RIGHT_WHOLE_LEG), e_joint_c::to_int(e_joint::RIGHT_HIP), 			e_joint_c::to_int(e_joint::RIGHT_FOOT), e_joint_c::to_int(e_joint::RIGHT_KNEE)));

			result.push_back(bone(e_bone_c::to_int(e_bone::HEAD), 				e_bone_c::str(e_bone::HEAD), 			e_joint_c::to_int(e_joint::NECK), 				e_joint_c::to_int(e_joint::HEAD)));

			default_bones_ = result;
			return result;
		}
	}


} // namespace mae
