#include "bone.hpp"

namespace mae
{

	std::vector<bone> bone::default_bones_ = std::vector<bone>();
	std::vector<bone> bone::default_kinect_bones_ = std::vector<bone>();
	std::vector<bone> bone::default_left_hand_bones_ = std::vector<bone>();
	std::vector<bone> bone::default_right_hand_bones_ = std::vector<bone>();

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

		initialize_by_e_bone(eb, def_bones);
	}

	bone::bone(e_hand_bone ehb)
	{
		std::vector<bone> def_bones = bone::default_hand_bones(true);
		std::vector<bone> def_bones_right = bone::default_hand_bones(false);
		def_bones.insert(def_bones.end(), def_bones_right.begin(), def_bones_right.end());

		initialize_by_e_hand_bone(ehb, def_bones);
	}

	bone::bone(e_bone eb, std::vector<bone> bones_set)
	{
		initialize_by_e_bone(eb, bones_set);
	}

	bone::~bone()
	{
	}

	void bone::initialize_by_e_bone(e_bone eb, std::vector<bone> bones_set)
	{
		bool e_bone_found = false;

		//using for loop here and the default bone minimizes the effort for maintenance at cost of runtime
		for (unsigned int i = 0; i < bones_set.size(); i++)
		{
			if (bones_set.at(i).get_id() == e_bone_c::to_int(eb))
			{
				bone b = bones_set.at(i);

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
            std::stringstream sstr;
            sstr << "The bone (" << e_bone_c::str(eb) << ") was not found in default bones. Therefore, it could not be created.";
            throw std::invalid_argument(sstr.str());
		}
	}

	void bone::initialize_by_e_hand_bone(e_hand_bone ehb, std::vector<bone> bones_set)
	{
		bool e_bone_found = false;

		//using for loop here and the default bone minimizes the effort for maintenance at cost of runtime
		for (unsigned int i = 0; i < bones_set.size(); i++)
		{
			if (bones_set.at(i).get_id() == e_hand_bone_c::to_int(ehb))
			{
				bone b = bones_set.at(i);

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
			std::stringstream sstr;
			sstr << "The bone (" << e_hand_bone_c::str(ehb) << ") was not found in default bones. Therefore, it could not be created.";
			throw std::invalid_argument(sstr.str());
		}
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
		if (0 == default_bones_.size())
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
		}

		return default_bones_;
	}

	std::vector<bone> bone::default_kinect_bones()
	{
		if (0 == default_kinect_bones_.size() > 0)
		{
			std::vector<bone> result;

			result.push_back(
					bone(e_bone_c::to_int(e_bone::LEFT_UPPER_ARM), e_bone_c::str(e_bone::LEFT_UPPER_ARM),
							e_kinect_joint_c::to_int(e_kinect_joint::LEFT_SHOULDER), e_kinect_joint_c::to_int(e_kinect_joint::LEFT_ELBOW)));
			result.push_back(
					bone(e_bone_c::to_int(e_bone::LEFT_FOREARM), e_bone_c::str(e_bone::LEFT_FOREARM),
							e_kinect_joint_c::to_int(e_kinect_joint::LEFT_ELBOW), e_kinect_joint_c::to_int(e_kinect_joint::LEFT_WRIST)));
			result.push_back(
					bone(e_bone_c::to_int(e_bone::LEFT_WHOLE_ARM), e_bone_c::str(e_bone::LEFT_WHOLE_ARM),
							e_kinect_joint_c::to_int(e_kinect_joint::LEFT_SHOULDER), e_kinect_joint_c::to_int(e_kinect_joint::LEFT_WRIST),
							e_kinect_joint_c::to_int(e_kinect_joint::LEFT_ELBOW)));

			result.push_back(
					bone(e_bone_c::to_int(e_bone::RIGHT_UPPER_ARM), e_bone_c::str(e_bone::RIGHT_UPPER_ARM),
							e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_SHOULDER), e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_ELBOW)));
			result.push_back(
					bone(e_bone_c::to_int(e_bone::RIGHT_FOREARM), e_bone_c::str(e_bone::RIGHT_FOREARM),
							e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_ELBOW), e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_WRIST)));
			result.push_back(
					bone(e_bone_c::to_int(e_bone::RIGHT_WHOLE_ARM), e_bone_c::str(e_bone::RIGHT_WHOLE_ARM),
							e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_SHOULDER), e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_WRIST),
							e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_ELBOW)));

			result.push_back(
					bone(e_bone_c::to_int(e_bone::LEFT_THIGH), e_bone_c::str(e_bone::LEFT_THIGH),
							e_kinect_joint_c::to_int(e_kinect_joint::LEFT_HIP), e_kinect_joint_c::to_int(e_kinect_joint::LEFT_KNEE)));
			result.push_back(
					bone(e_bone_c::to_int(e_bone::LEFT_SHANK), e_bone_c::str(e_bone::LEFT_SHANK),
							e_kinect_joint_c::to_int(e_kinect_joint::LEFT_KNEE), e_kinect_joint_c::to_int(e_kinect_joint::LEFT_ANKLE)));
			result.push_back(
					bone(e_bone_c::to_int(e_bone::LEFT_WHOLE_LEG), e_bone_c::str(e_bone::LEFT_WHOLE_LEG),
							e_kinect_joint_c::to_int(e_kinect_joint::LEFT_HIP), e_kinect_joint_c::to_int(e_kinect_joint::LEFT_ANKLE),
							e_kinect_joint_c::to_int(e_kinect_joint::LEFT_KNEE)));

			result.push_back(
					bone(e_bone_c::to_int(e_bone::RIGHT_THIGH), e_bone_c::str(e_bone::RIGHT_THIGH),
							e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_HIP), e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_KNEE)));
			result.push_back(
					bone(e_bone_c::to_int(e_bone::RIGHT_SHANK), e_bone_c::str(e_bone::RIGHT_SHANK),
							e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_KNEE), e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_ANKLE)));
			result.push_back(
					bone(e_bone_c::to_int(e_bone::RIGHT_WHOLE_LEG), e_bone_c::str(e_bone::RIGHT_WHOLE_LEG),
							e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_HIP), e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_ANKLE),
							e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_KNEE)));

			result.push_back(
					bone(e_bone_c::to_int(e_bone::HEAD), e_bone_c::str(e_bone::HEAD), e_kinect_joint_c::to_int(e_kinect_joint::NECK),
							e_kinect_joint_c::to_int(e_kinect_joint::HEAD)));

			//other bones not in the default set
			result.push_back(
					bone(e_bone_c::to_int(e_bone::LEFT_HAND), e_bone_c::str(e_bone::LEFT_HAND),
							e_kinect_joint_c::to_int(e_kinect_joint::LEFT_WRIST), e_kinect_joint_c::to_int(e_kinect_joint::LEFT_HAND)));

			result.push_back(
					bone(e_bone_c::to_int(e_bone::RIGHT_HAND), e_bone_c::str(e_bone::RIGHT_HAND),
							e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_WRIST), e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_HAND)));

			result.push_back(
					bone(e_bone_c::to_int(e_bone::LEFT_FOOT), e_bone_c::str(e_bone::LEFT_FOOT),
							e_kinect_joint_c::to_int(e_kinect_joint::LEFT_ANKLE), e_kinect_joint_c::to_int(e_kinect_joint::LEFT_FOOT)));

			result.push_back(
					bone(e_bone_c::to_int(e_bone::RIGHT_FOOT), e_bone_c::str(e_bone::RIGHT_FOOT),
							e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_ANKLE), e_kinect_joint_c::to_int(e_kinect_joint::RIGHT_FOOT)));


			default_kinect_bones_ = result;
		}

		return default_kinect_bones_;
	}


	std::vector<bone> bone::default_hand_bones(bool is_left)
	{
		if (default_left_hand_bones_.size() == 0 || default_right_hand_bones_.size() == 0)
		{

            std::vector<bone> left_hand;

            left_hand.push_back(
                    bone(e_hand_bone_c::to_int(e_hand_bone::LEFT_THUMB), e_hand_bone_c::str(e_hand_bone::LEFT_THUMB),
                         e_hand_joint_c::to_int(e_hand_joint::LEFT_WRIST),
                         e_hand_joint_c::to_int(e_hand_joint::LEFT_THUMB_TIP)));
            left_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::LEFT_INDEX_FINGER),
                                     e_hand_bone_c::str(e_hand_bone::LEFT_INDEX_FINGER),
                                     e_hand_joint_c::to_int(e_hand_joint::LEFT_INDEX_FINGER_METACARPOPHALANGEAL_JOINT),
                                     e_hand_joint_c::to_int(e_hand_joint::LEFT_INDEX_FINGER_TIP)));
            left_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::LEFT_MIDDLE_FINGER),
                                     e_hand_bone_c::str(e_hand_bone::LEFT_MIDDLE_FINGER),
                                     e_hand_joint_c::to_int(e_hand_joint::LEFT_MIDDLE_FINGER_METACARPOPHALANGEAL_JOINT),
                                     e_hand_joint_c::to_int(e_hand_joint::LEFT_MIDDLE_FINGER_TIP)));
            left_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::LEFT_RING_FINGER),
                                     e_hand_bone_c::str(e_hand_bone::LEFT_RING_FINGER),
                                     e_hand_joint_c::to_int(e_hand_joint::LEFT_RING_FINGER_METACARPOPHALANGEAL_JOINT),
                                     e_hand_joint_c::to_int(e_hand_joint::LEFT_RING_FINGER_TIP)));
            left_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::LEFT_LITTLE_FINGER),
                                     e_hand_bone_c::str(e_hand_bone::LEFT_LITTLE_FINGER),
                                     e_hand_joint_c::to_int(e_hand_joint::LEFT_LITTLE_FINGER_METACARPOPHALANGEAL_JOINT),
                                     e_hand_joint_c::to_int(e_hand_joint::LEFT_LITTLE_FINGER_TIP)));

            left_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::LEFT_THUMB_PROXIMAL_PHALANX),
                                     e_hand_bone_c::str(e_hand_bone::LEFT_THUMB_PROXIMAL_PHALANX),
                                     e_hand_joint_c::to_int(e_hand_joint::LEFT_WRIST),
                                     e_hand_joint_c::to_int(e_hand_joint::LEFT_THUMB_PROXIMAL_INTERPHALANGEAL_JOINT)));
            left_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::LEFT_THUMB_INTERMEDIATE_PHALANX),
                                     e_hand_bone_c::str(e_hand_bone::LEFT_THUMB_INTERMEDIATE_PHALANX),
                                     e_hand_joint_c::to_int(e_hand_joint::LEFT_THUMB_PROXIMAL_INTERPHALANGEAL_JOINT),
                                     e_hand_joint_c::to_int(e_hand_joint::LEFT_THUMB_DISTAL_INTERPHALANGEAL_JOINT)));
            left_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::LEFT_THUMB_DISTAL_PHALANX),
                                     e_hand_bone_c::str(e_hand_bone::LEFT_THUMB_DISTAL_PHALANX),
                                     e_hand_joint_c::to_int(e_hand_joint::LEFT_THUMB_DISTAL_INTERPHALANGEAL_JOINT),
                                     e_hand_joint_c::to_int(e_hand_joint::LEFT_THUMB_TIP)));

            left_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::LEFT_INDEX_FINGER_PROXIMAL_PHALANX),
                                     e_hand_bone_c::str(e_hand_bone::LEFT_INDEX_FINGER_PROXIMAL_PHALANX),
                                     e_hand_joint_c::to_int(e_hand_joint::LEFT_INDEX_FINGER_METACARPOPHALANGEAL_JOINT),
                                     e_hand_joint_c::to_int(
                                             e_hand_joint::LEFT_INDEX_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT)));
            left_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::LEFT_INDEX_FINGER_INTERMEDIATE_PHALANX),
                                     e_hand_bone_c::str(e_hand_bone::LEFT_INDEX_FINGER_INTERMEDIATE_PHALANX),
                                     e_hand_joint_c::to_int(
                                             e_hand_joint::LEFT_INDEX_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT),
                                     e_hand_joint_c::to_int(
                                             e_hand_joint::LEFT_INDEX_FINGER_DISTAL_INTERPHALANGEAL_JOINT)));
            left_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::LEFT_INDEX_FINGER_DISTAL_PHALANX),
                                     e_hand_bone_c::str(e_hand_bone::LEFT_INDEX_FINGER_DISTAL_PHALANX),
                                     e_hand_joint_c::to_int(
                                             e_hand_joint::LEFT_INDEX_FINGER_DISTAL_INTERPHALANGEAL_JOINT),
                                     e_hand_joint_c::to_int(e_hand_joint::LEFT_INDEX_FINGER_TIP)));

            left_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::LEFT_MIDDLE_FINGER_PROXIMAL_PHALANX),
                                     e_hand_bone_c::str(e_hand_bone::LEFT_MIDDLE_FINGER_PROXIMAL_PHALANX),
                                     e_hand_joint_c::to_int(e_hand_joint::LEFT_MIDDLE_FINGER_METACARPOPHALANGEAL_JOINT),
                                     e_hand_joint_c::to_int(
                                             e_hand_joint::LEFT_MIDDLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT)));
            left_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::LEFT_MIDDLE_FINGER_INTERMEDIATE_PHALANX),
                                     e_hand_bone_c::str(e_hand_bone::LEFT_MIDDLE_FINGER_INTERMEDIATE_PHALANX),
                                     e_hand_joint_c::to_int(
                                             e_hand_joint::LEFT_MIDDLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT),
                                     e_hand_joint_c::to_int(
                                             e_hand_joint::LEFT_MIDDLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT)));
            left_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::LEFT_MIDDLE_FINGER_DISTAL_PHALANX),
                                     e_hand_bone_c::str(e_hand_bone::LEFT_MIDDLE_FINGER_DISTAL_PHALANX),
                                     e_hand_joint_c::to_int(
                                             e_hand_joint::LEFT_MIDDLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT),
                                     e_hand_joint_c::to_int(e_hand_joint::LEFT_MIDDLE_FINGER_TIP)));

            left_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::LEFT_RING_FINGER_PROXIMAL_PHALANX),
                                     e_hand_bone_c::str(e_hand_bone::LEFT_RING_FINGER_PROXIMAL_PHALANX),
                                     e_hand_joint_c::to_int(e_hand_joint::LEFT_RING_FINGER_METACARPOPHALANGEAL_JOINT),
                                     e_hand_joint_c::to_int(
                                             e_hand_joint::LEFT_RING_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT)));
            left_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::LEFT_RING_FINGER_INTERMEDIATE_PHALANX),
                                     e_hand_bone_c::str(e_hand_bone::LEFT_RING_FINGER_INTERMEDIATE_PHALANX),
                                     e_hand_joint_c::to_int(
                                             e_hand_joint::LEFT_RING_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT),
                                     e_hand_joint_c::to_int(
                                             e_hand_joint::LEFT_RING_FINGER_DISTAL_INTERPHALANGEAL_JOINT)));
            left_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::LEFT_RING_FINGER_DISTAL_PHALANX),
                                     e_hand_bone_c::str(e_hand_bone::LEFT_RING_FINGER_DISTAL_PHALANX),
                                     e_hand_joint_c::to_int(
                                             e_hand_joint::LEFT_RING_FINGER_DISTAL_INTERPHALANGEAL_JOINT),
                                     e_hand_joint_c::to_int(e_hand_joint::LEFT_RING_FINGER_TIP)));

            left_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::LEFT_LITTLE_FINGER_PROXIMAL_PHALANX),
                                     e_hand_bone_c::str(e_hand_bone::LEFT_LITTLE_FINGER_PROXIMAL_PHALANX),
                                     e_hand_joint_c::to_int(e_hand_joint::LEFT_LITTLE_FINGER_METACARPOPHALANGEAL_JOINT),
                                     e_hand_joint_c::to_int(
                                             e_hand_joint::LEFT_LITTLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT)));
            left_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::LEFT_LITTLE_FINGER_INTERMEDIATE_PHALANX),
                                     e_hand_bone_c::str(e_hand_bone::LEFT_LITTLE_FINGER_INTERMEDIATE_PHALANX),
                                     e_hand_joint_c::to_int(
                                             e_hand_joint::LEFT_LITTLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT),
                                     e_hand_joint_c::to_int(
                                             e_hand_joint::LEFT_LITTLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT)));
            left_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::LEFT_LITTLE_FINGER_DISTAL_PHALANX),
                                     e_hand_bone_c::str(e_hand_bone::LEFT_LITTLE_FINGER_DISTAL_PHALANX),
                                     e_hand_joint_c::to_int(
                                             e_hand_joint::LEFT_LITTLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT),
                                     e_hand_joint_c::to_int(e_hand_joint::LEFT_LITTLE_FINGER_TIP)));

            default_left_hand_bones_ = left_hand;

            std::vector<bone> right_hand;

            right_hand.push_back(
                    bone(e_hand_bone_c::to_int(e_hand_bone::RIGHT_THUMB), e_hand_bone_c::str(e_hand_bone::RIGHT_THUMB),
                         e_hand_joint_c::to_int(e_hand_joint::RIGHT_WRIST),
                         e_hand_joint_c::to_int(e_hand_joint::RIGHT_THUMB_TIP)));
            right_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::RIGHT_INDEX_FINGER),
                                      e_hand_bone_c::str(e_hand_bone::RIGHT_INDEX_FINGER), e_hand_joint_c::to_int(
                            e_hand_joint::RIGHT_INDEX_FINGER_METACARPOPHALANGEAL_JOINT),
                                      e_hand_joint_c::to_int(e_hand_joint::RIGHT_INDEX_FINGER_TIP)));
            right_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::RIGHT_MIDDLE_FINGER),
                                      e_hand_bone_c::str(e_hand_bone::RIGHT_MIDDLE_FINGER), e_hand_joint_c::to_int(
                            e_hand_joint::RIGHT_MIDDLE_FINGER_METACARPOPHALANGEAL_JOINT),
                                      e_hand_joint_c::to_int(e_hand_joint::RIGHT_MIDDLE_FINGER_TIP)));
            right_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::RIGHT_RING_FINGER),
                                      e_hand_bone_c::str(e_hand_bone::RIGHT_RING_FINGER),
                                      e_hand_joint_c::to_int(e_hand_joint::RIGHT_RING_FINGER_METACARPOPHALANGEAL_JOINT),
                                      e_hand_joint_c::to_int(e_hand_joint::RIGHT_RING_FINGER_TIP)));
            right_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::RIGHT_LITTLE_FINGER),
                                      e_hand_bone_c::str(e_hand_bone::RIGHT_LITTLE_FINGER), e_hand_joint_c::to_int(
                            e_hand_joint::RIGHT_LITTLE_FINGER_METACARPOPHALANGEAL_JOINT),
                                      e_hand_joint_c::to_int(e_hand_joint::RIGHT_LITTLE_FINGER_TIP)));

            right_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::RIGHT_THUMB_PROXIMAL_PHALANX),
                                      e_hand_bone_c::str(e_hand_bone::RIGHT_THUMB_PROXIMAL_PHALANX),
                                      e_hand_joint_c::to_int(e_hand_joint::RIGHT_WRIST), e_hand_joint_c::to_int(
                            e_hand_joint::RIGHT_THUMB_PROXIMAL_INTERPHALANGEAL_JOINT)));
            right_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::RIGHT_THUMB_INTERMEDIATE_PHALANX),
                                      e_hand_bone_c::str(e_hand_bone::RIGHT_THUMB_INTERMEDIATE_PHALANX),
                                      e_hand_joint_c::to_int(e_hand_joint::RIGHT_THUMB_PROXIMAL_INTERPHALANGEAL_JOINT),
                                      e_hand_joint_c::to_int(e_hand_joint::RIGHT_THUMB_DISTAL_INTERPHALANGEAL_JOINT)));
            right_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::RIGHT_THUMB_DISTAL_PHALANX),
                                      e_hand_bone_c::str(e_hand_bone::RIGHT_THUMB_DISTAL_PHALANX),
                                      e_hand_joint_c::to_int(e_hand_joint::RIGHT_THUMB_DISTAL_INTERPHALANGEAL_JOINT),
                                      e_hand_joint_c::to_int(e_hand_joint::RIGHT_THUMB_TIP)));

            right_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::RIGHT_INDEX_FINGER_PROXIMAL_PHALANX),
                                      e_hand_bone_c::str(e_hand_bone::RIGHT_INDEX_FINGER_PROXIMAL_PHALANX),
                                      e_hand_joint_c::to_int(
                                              e_hand_joint::RIGHT_INDEX_FINGER_METACARPOPHALANGEAL_JOINT),
                                      e_hand_joint_c::to_int(
                                              e_hand_joint::RIGHT_INDEX_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT)));
            right_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::RIGHT_INDEX_FINGER_INTERMEDIATE_PHALANX),
                                      e_hand_bone_c::str(e_hand_bone::RIGHT_INDEX_FINGER_INTERMEDIATE_PHALANX),
                                      e_hand_joint_c::to_int(
                                              e_hand_joint::RIGHT_INDEX_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT),
                                      e_hand_joint_c::to_int(
                                              e_hand_joint::RIGHT_INDEX_FINGER_DISTAL_INTERPHALANGEAL_JOINT)));
            right_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::RIGHT_INDEX_FINGER_DISTAL_PHALANX),
                                      e_hand_bone_c::str(e_hand_bone::RIGHT_INDEX_FINGER_DISTAL_PHALANX),
                                      e_hand_joint_c::to_int(
                                              e_hand_joint::RIGHT_INDEX_FINGER_DISTAL_INTERPHALANGEAL_JOINT),
                                      e_hand_joint_c::to_int(e_hand_joint::RIGHT_INDEX_FINGER_TIP)));

            right_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::RIGHT_MIDDLE_FINGER_PROXIMAL_PHALANX),
                                      e_hand_bone_c::str(e_hand_bone::RIGHT_MIDDLE_FINGER_PROXIMAL_PHALANX),
                                      e_hand_joint_c::to_int(
                                              e_hand_joint::RIGHT_MIDDLE_FINGER_METACARPOPHALANGEAL_JOINT),
                                      e_hand_joint_c::to_int(
                                              e_hand_joint::RIGHT_MIDDLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT)));
            right_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::RIGHT_MIDDLE_FINGER_INTERMEDIATE_PHALANX),
                                      e_hand_bone_c::str(e_hand_bone::RIGHT_MIDDLE_FINGER_INTERMEDIATE_PHALANX),
                                      e_hand_joint_c::to_int(
                                              e_hand_joint::RIGHT_MIDDLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT),
                                      e_hand_joint_c::to_int(
                                              e_hand_joint::RIGHT_MIDDLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT)));
            right_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::RIGHT_MIDDLE_FINGER_DISTAL_PHALANX),
                                      e_hand_bone_c::str(e_hand_bone::RIGHT_MIDDLE_FINGER_DISTAL_PHALANX),
                                      e_hand_joint_c::to_int(
                                              e_hand_joint::RIGHT_MIDDLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT),
                                      e_hand_joint_c::to_int(e_hand_joint::RIGHT_MIDDLE_FINGER_TIP)));

            right_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::RIGHT_RING_FINGER_PROXIMAL_PHALANX),
                                      e_hand_bone_c::str(e_hand_bone::RIGHT_RING_FINGER_PROXIMAL_PHALANX),
                                      e_hand_joint_c::to_int(e_hand_joint::RIGHT_RING_FINGER_METACARPOPHALANGEAL_JOINT),
                                      e_hand_joint_c::to_int(
                                              e_hand_joint::RIGHT_RING_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT)));
            right_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::RIGHT_RING_FINGER_INTERMEDIATE_PHALANX),
                                      e_hand_bone_c::str(e_hand_bone::RIGHT_RING_FINGER_INTERMEDIATE_PHALANX),
                                      e_hand_joint_c::to_int(
                                              e_hand_joint::RIGHT_RING_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT),
                                      e_hand_joint_c::to_int(
                                              e_hand_joint::RIGHT_RING_FINGER_DISTAL_INTERPHALANGEAL_JOINT)));
            right_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::RIGHT_RING_FINGER_DISTAL_PHALANX),
                                      e_hand_bone_c::str(e_hand_bone::RIGHT_RING_FINGER_DISTAL_PHALANX),
                                      e_hand_joint_c::to_int(
                                              e_hand_joint::RIGHT_RING_FINGER_DISTAL_INTERPHALANGEAL_JOINT),
                                      e_hand_joint_c::to_int(e_hand_joint::RIGHT_RING_FINGER_TIP)));

            right_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::RIGHT_LITTLE_FINGER_PROXIMAL_PHALANX),
                                      e_hand_bone_c::str(e_hand_bone::RIGHT_LITTLE_FINGER_PROXIMAL_PHALANX),
                                      e_hand_joint_c::to_int(
                                              e_hand_joint::RIGHT_LITTLE_FINGER_METACARPOPHALANGEAL_JOINT),
                                      e_hand_joint_c::to_int(
                                              e_hand_joint::RIGHT_LITTLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT)));
            right_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::RIGHT_LITTLE_FINGER_INTERMEDIATE_PHALANX),
                                      e_hand_bone_c::str(e_hand_bone::RIGHT_LITTLE_FINGER_INTERMEDIATE_PHALANX),
                                      e_hand_joint_c::to_int(
                                              e_hand_joint::RIGHT_LITTLE_FINGER_PROXIMAL_INTERPHALANGEAL_JOINT),
                                      e_hand_joint_c::to_int(
                                              e_hand_joint::RIGHT_LITTLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT)));
            right_hand.push_back(bone(e_hand_bone_c::to_int(e_hand_bone::RIGHT_LITTLE_FINGER_DISTAL_PHALANX),
                                      e_hand_bone_c::str(e_hand_bone::RIGHT_LITTLE_FINGER_DISTAL_PHALANX),
                                      e_hand_joint_c::to_int(
                                              e_hand_joint::RIGHT_LITTLE_FINGER_DISTAL_INTERPHALANGEAL_JOINT),
                                      e_hand_joint_c::to_int(e_hand_joint::RIGHT_LITTLE_FINGER_TIP)));

            default_right_hand_bones_ = right_hand;

		}

        if (is_left)
        {
            return default_left_hand_bones_;
        }
        else
        {
            return default_right_hand_bones_;
        }
	}

} // namespace mae
