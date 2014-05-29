/*
 * FLSkeleton.cpp
 *
 *  Created on: 20.05.2014
 *      Author: keks
 */

#include "FLSkeleton.hpp"

namespace mae {
	namespace fl {

		FLSkeleton::FLSkeleton() {
			this->hashmap_joints = std::unordered_map<int, std::shared_ptr<mae::fl::FLJoint> >();
		}

		FLSkeleton::~FLSkeleton() {
			hashmap_joints.clear();
		}

		void FLSkeleton::setJoint(int bodyPart, std::shared_ptr<mae::fl::FLJoint> joint){

			if (hashmap_joints.find(bodyPart) == hashmap_joints.end()){
				//key is not in map
				hashmap_joints.insert(std::make_pair(bodyPart, joint));

			}else{
				//key already exists and will therefore be overwritten
				hashmap_joints[bodyPart] = joint;
			}
		}

		std::shared_ptr<mae::fl::FLJoint> FLSkeleton::getJoint(int bodyPart){

			if (hashmap_joints.find(bodyPart) == hashmap_joints.end()){
				// returns an invalid joint which means that the joint is
				// not existing
				return std::shared_ptr<mae::fl::FLJoint>(new mae::fl::FLJoint());
			}else{
				// returns the joint
				return hashmap_joints[bodyPart];
			}

		}



		//throws invalid_argument exception if sizes are incorrect
		void FLSkeleton::setCoordSys(std::vector<double> u, std::vector<double> r, std::vector<double> t){

			if (u.size() == 3 && r.size() == 3 && t.size() == 3){
				this->u = u;
				this->r = r;
				this->t = t;
			}else{
				throw std::invalid_argument("At least one parameter does not match the expected 3 dimensional vector.");
			}
		}

		std::vector<std::vector<double> > FLSkeleton::getCoordSys(){
			std::vector<std::vector<double> > coord_sys = std::vector<std::vector<double> >();
			coord_sys.push_back(u);
			coord_sys.push_back(r);
			coord_sys.push_back(t);

			return coord_sys;
		}

		void FLSkeleton::setRelativeSkeleton(std::shared_ptr<mae::model::GeneralSkeleton> relative_skeleton){
			this->relative_skeleton = relative_skeleton;
		}

		std::shared_ptr<mae::model::GeneralSkeleton> FLSkeleton::getRelativeSkeleton(){
			return relative_skeleton;
		}


		std::vector<int> FLSkeleton::get_joint_ids(){
			std::vector<int> joint_ids;
			joint_ids.push_back(FLSkeleton::ANGLE_HEAD);
			joint_ids.push_back(FLSkeleton::ANGLE_LEFT_UPPER_ARM);
			joint_ids.push_back(FLSkeleton::ANGLE_LEFT_FOREARM);
			joint_ids.push_back(FLSkeleton::ANGLE_LEFT_WHOLE_ARM);
			joint_ids.push_back(FLSkeleton::ANGLE_RIGHT_UPPER_ARM);
			joint_ids.push_back(FLSkeleton::ANGLE_RIGHT_FOREARM);
			joint_ids.push_back(FLSkeleton::ANGLE_RIGHT_WHOLE_ARM);
			joint_ids.push_back(FLSkeleton::ANGLE_LEFT_THIGH);
			joint_ids.push_back(FLSkeleton::ANGLE_LEFT_SHANK);
			joint_ids.push_back(FLSkeleton::ANGLE_LEFT_WHOLE_LEG);
			joint_ids.push_back(FLSkeleton::ANGLE_RIGHT_THIGH);
			joint_ids.push_back(FLSkeleton::ANGLE_RIGHT_SHANK);
			joint_ids.push_back(FLSkeleton::ANGLE_RIGHT_WHOLE_LEG);
			return joint_ids;
		}

		//angle representations
		const int FLSkeleton::ANGLE_HEAD = 16;
		const int FLSkeleton::ANGLE_LEFT_UPPER_ARM = 17;
		const int FLSkeleton::ANGLE_LEFT_FOREARM = 18;
		const int FLSkeleton::ANGLE_LEFT_WHOLE_ARM = 19;
		const int FLSkeleton::ANGLE_RIGHT_UPPER_ARM = 20;
		const int FLSkeleton::ANGLE_RIGHT_FOREARM = 21;
		const int FLSkeleton::ANGLE_RIGHT_WHOLE_ARM = 22;
		const int FLSkeleton::ANGLE_LEFT_THIGH = 23; //Oberschenkel
		const int FLSkeleton::ANGLE_LEFT_SHANK = 24; //Unterschenkel
		const int FLSkeleton::ANGLE_LEFT_WHOLE_LEG = 25;
		const int FLSkeleton::ANGLE_RIGHT_THIGH = 26; //Oberschenkel
		const int FLSkeleton::ANGLE_RIGHT_SHANK = 27; //Unterschenkel
		const int FLSkeleton::ANGLE_RIGHT_WHOLE_LEG = 28;

	} // namespace fl
} // namespace mae
