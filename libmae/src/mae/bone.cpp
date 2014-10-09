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

	bone::bone()
	{
		id_ = -1;
		name_ = "";
		from_ = -1;
		to_ = -1;
		middle_joint_ = -1;
		middle_ = false;
	}

	bone::bone(int id, std::string name, int from, int to)
	{
		id_ = id;
		name_ = name;
		from_ = from;
		to_ = to;

		middle_joint_ = 0;
		middle_ = false;
	}

	bone::bone(int id, std::string name, int from, int to, int middle_joint)
	{
		id_ = id;
		name_ = name;
		from_ = from;
		to_ = to;

		middle_joint_ = middle_joint;
		middle_ = true;
	}

	bone::bone(e_bone eb)
	{
		std::vector<bone> def_bones = bone::default_bones();

		bool e_bone_found = false;

		//using for loop here and the default bone minimizes the effort for maintenance at cost of runtime
		for (unsigned int i = 0; i < def_bones.size(); i++)
		{
			if (def_bones.at(i).get_id() == e_bone_c::to_int(eb))
			{
				bone b = def_bones.at(i);

				id_ = b.get_id();
				from_ = b.get_from();
				to_ = b.get_to();
				middle_ = b.has_middle_joint();
				middle_joint_ = b.get_middle_joint();

				e_bone_found = true;
				break;
			}
		}

		if (!e_bone_found)
		{
			throw std::invalid_argument("The bone was not found in default bones. Therefore, it could not be created.");
		}
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

			result.push_back(
					bone(e_bone_c::to_int(e_bone::LEFT_UPPER_ARM), e_bone_c::str(e_bone::LEFT_UPPER_ARM),
							e_joint_c::to_int(e_joint::LEFT_SHOULDER), e_joint_c::to_int(e_joint::LEFT_ELBOW)));
			result.push_back(
					bone(e_bone_c::to_int(e_bone::LEFT_FOREARM), e_bone_c::str(e_bone::LEFT_FOREARM),
							e_joint_c::to_int(e_joint::LEFT_ELBOW), e_joint_c::to_int(e_joint::LEFT_HAND)));
			result.push_back(
					bone(e_bone_c::to_int(e_bone::LEFT_WHOLE_ARM), e_bone_c::str(e_bone::LEFT_WHOLE_ARM),
							e_joint_c::to_int(e_joint::LEFT_SHOULDER), e_joint_c::to_int(e_joint::LEFT_HAND),
							e_joint_c::to_int(e_joint::LEFT_ELBOW)));

			result.push_back(
					bone(e_bone_c::to_int(e_bone::RIGHT_UPPER_ARM), e_bone_c::str(e_bone::RIGHT_UPPER_ARM),
							e_joint_c::to_int(e_joint::RIGHT_SHOULDER), e_joint_c::to_int(e_joint::RIGHT_ELBOW)));
			result.push_back(
					bone(e_bone_c::to_int(e_bone::RIGHT_FOREARM), e_bone_c::str(e_bone::RIGHT_FOREARM),
							e_joint_c::to_int(e_joint::RIGHT_ELBOW), e_joint_c::to_int(e_joint::RIGHT_HAND)));
			result.push_back(
					bone(e_bone_c::to_int(e_bone::RIGHT_WHOLE_ARM), e_bone_c::str(e_bone::RIGHT_WHOLE_ARM),
							e_joint_c::to_int(e_joint::RIGHT_SHOULDER), e_joint_c::to_int(e_joint::RIGHT_HAND),
							e_joint_c::to_int(e_joint::RIGHT_ELBOW)));

			result.push_back(
					bone(e_bone_c::to_int(e_bone::LEFT_THIGH), e_bone_c::str(e_bone::LEFT_THIGH),
							e_joint_c::to_int(e_joint::LEFT_HIP), e_joint_c::to_int(e_joint::LEFT_KNEE)));
			result.push_back(
					bone(e_bone_c::to_int(e_bone::LEFT_SHANK), e_bone_c::str(e_bone::LEFT_SHANK),
							e_joint_c::to_int(e_joint::LEFT_KNEE), e_joint_c::to_int(e_joint::LEFT_FOOT)));
			result.push_back(
					bone(e_bone_c::to_int(e_bone::LEFT_WHOLE_LEG), e_bone_c::str(e_bone::LEFT_WHOLE_LEG),
							e_joint_c::to_int(e_joint::LEFT_HIP), e_joint_c::to_int(e_joint::LEFT_FOOT),
							e_joint_c::to_int(e_joint::LEFT_KNEE)));

			result.push_back(
					bone(e_bone_c::to_int(e_bone::RIGHT_THIGH), e_bone_c::str(e_bone::RIGHT_THIGH),
							e_joint_c::to_int(e_joint::RIGHT_HIP), e_joint_c::to_int(e_joint::RIGHT_KNEE)));
			result.push_back(
					bone(e_bone_c::to_int(e_bone::RIGHT_SHANK), e_bone_c::str(e_bone::RIGHT_SHANK),
							e_joint_c::to_int(e_joint::RIGHT_KNEE), e_joint_c::to_int(e_joint::RIGHT_FOOT)));
			result.push_back(
					bone(e_bone_c::to_int(e_bone::RIGHT_WHOLE_LEG), e_bone_c::str(e_bone::RIGHT_WHOLE_LEG),
							e_joint_c::to_int(e_joint::RIGHT_HIP), e_joint_c::to_int(e_joint::RIGHT_FOOT),
							e_joint_c::to_int(e_joint::RIGHT_KNEE)));

			result.push_back(
					bone(e_bone_c::to_int(e_bone::HEAD), e_bone_c::str(e_bone::HEAD), e_joint_c::to_int(e_joint::NECK),
							e_joint_c::to_int(e_joint::HEAD)));

			default_bones_ = result;
			return result;
		}
	}


} // namespace mae
