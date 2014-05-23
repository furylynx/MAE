/*
 * GeneralSkeleton.cpp
 *
 *  Created on: 15.05.2014
 *      Author: keks
 */

#include "GeneralSkeleton.hpp"

namespace mae {
	namespace model {

		GeneralSkeleton::~GeneralSkeleton() {
			hashmap_joints.clear();
		}

		GeneralSkeleton::GeneralSkeleton(){
			hashmap_joints = std::unordered_map<int, std::shared_ptr<mae::model::GeneralJoint> >();
		}


		void GeneralSkeleton::setJoint(int bodyPart, std::shared_ptr<mae::model::GeneralJoint> joint){

			if (hashmap_joints.find(bodyPart) == hashmap_joints.end()){
				//key is not in map
				hashmap_joints.insert(std::make_pair(bodyPart, joint));

			}else{
				//key already exists and will therefore be overwritten
				hashmap_joints[bodyPart] = joint;
			}
		}

		std::shared_ptr<mae::model::GeneralJoint> GeneralSkeleton::getJoint(int bodyPart){

			if (hashmap_joints.find(bodyPart) == hashmap_joints.end()){
				// returns an invalid joint which means that the joint is
				// not existing
				return std::shared_ptr<mae::model::GeneralJoint>(new mae::model::GeneralJoint());
			}else{
				// returns the joint
				return hashmap_joints[bodyPart];
			}

		}

	} // namespace model
} // namespace mae
