/*
 * GeneralSkeleton.cpp
 *
 * Created on: 15.05.2014
 * Author: keks
 */

#include "GeneralSkeleton.hpp"

namespace mae
{
	namespace model
	{

		GeneralSkeleton::~GeneralSkeleton()
		{
			hashmap_joints.clear();
		}

		GeneralSkeleton::GeneralSkeleton()
		{
			hashmap_joints = std::unordered_map<int, std::shared_ptr<mae::model::GeneralJoint> >();
		}

		void GeneralSkeleton::setJoint(int bodyPart, std::shared_ptr<mae::model::GeneralJoint> joint)
		{

			if (hashmap_joints.find(bodyPart) == hashmap_joints.end())
			{
				//key is not in map
				hashmap_joints.insert(std::make_pair(bodyPart, joint));

			}
			else
			{
				//key already exists and will therefore be overwritten
				hashmap_joints[bodyPart] = joint;
			}
		}

		std::shared_ptr<mae::model::GeneralJoint> GeneralSkeleton::getJoint(int bodyPart)
		{

			if (hashmap_joints.find(bodyPart) == hashmap_joints.end())
			{
				// returns an invalid joint which means that the joint is
				// not existing
				return std::shared_ptr<mae::model::GeneralJoint>(new mae::model::GeneralJoint());
			}
			else
			{
				// returns the joint
				return hashmap_joints[bodyPart];
			}

		}

//		std::vector<int> GeneralSkeleton::get_joint_ids()
//		{
//			std::vector<int> joint_ids;
//			joint_ids.push_back(GeneralSkeleton::SKEL_HEAD);
//			joint_ids.push_back(GeneralSkeleton::SKEL_NECK);
//			joint_ids.push_back(GeneralSkeleton::SKEL_LEFT_SHOULDER);
//			joint_ids.push_back(GeneralSkeleton::SKEL_LEFT_ELBOW);
//			joint_ids.push_back(GeneralSkeleton::SKEL_LEFT_HAND);
//			joint_ids.push_back(GeneralSkeleton::SKEL_RIGHT_SHOULDER);
//			joint_ids.push_back(GeneralSkeleton::SKEL_RIGHT_ELBOW);
//			joint_ids.push_back(GeneralSkeleton::SKEL_RIGHT_HAND);
//			joint_ids.push_back(GeneralSkeleton::SKEL_TORSO);
//			joint_ids.push_back(GeneralSkeleton::SKEL_LEFT_HIP);
//			joint_ids.push_back(GeneralSkeleton::SKEL_LEFT_KNEE);
//			joint_ids.push_back(GeneralSkeleton::SKEL_LEFT_FOOT);
//			joint_ids.push_back(GeneralSkeleton::SKEL_RIGHT_HIP);
//			joint_ids.push_back(GeneralSkeleton::SKEL_RIGHT_KNEE);
//			joint_ids.push_back(GeneralSkeleton::SKEL_RIGHT_FOOT);
//			return joint_ids;
//		}

		//const int defs
//		const int GeneralSkeleton::SKEL_HEAD = 1;
//		const int GeneralSkeleton::SKEL_NECK = 2;
//		const int GeneralSkeleton::SKEL_LEFT_SHOULDER = 3;
//		const int GeneralSkeleton::SKEL_LEFT_ELBOW = 4;
//		const int GeneralSkeleton::SKEL_LEFT_HAND = 5;
//		const int GeneralSkeleton::SKEL_RIGHT_SHOULDER = 6;
//		const int GeneralSkeleton::SKEL_RIGHT_ELBOW = 7;
//		const int GeneralSkeleton::SKEL_RIGHT_HAND = 8;
//		const int GeneralSkeleton::SKEL_TORSO = 9;
//		const int GeneralSkeleton::SKEL_LEFT_HIP = 10;
//		const int GeneralSkeleton::SKEL_LEFT_KNEE = 11;
//		const int GeneralSkeleton::SKEL_LEFT_FOOT = 12;
//		const int GeneralSkeleton::SKEL_RIGHT_HIP = 13;
//		const int GeneralSkeleton::SKEL_RIGHT_KNEE = 14;
//		const int GeneralSkeleton::SKEL_RIGHT_FOOT = 15;

	} // namespace model
} // namespace mae
