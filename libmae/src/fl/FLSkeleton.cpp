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
			this->hashmap_joints = std::unordered_map<int, mae::fl::FLJoint>();
		}

		FLSkeleton::~FLSkeleton() {
			hashmap_joints.clear();
		}

		void FLSkeleton::setJoint(int bodyPart, mae::fl::FLJoint joint){

			if (hashmap_joints.find(bodyPart) == hashmap_joints.end()){
				//key is not in map
				hashmap_joints.insert(std::make_pair(bodyPart, joint));

			}else{
				//key already exists and will therefore be overwritten
				hashmap_joints[bodyPart] = joint;
			}
		}

		mae::fl::FLJoint FLSkeleton::getJoint(int bodyPart){

			if (hashmap_joints.find(bodyPart) == hashmap_joints.end()){
				// returns an invalid joint which means that the joint is
				// not existing
				return mae::fl::FLJoint();
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

		void FLSkeleton::setRelativeSkeleton(mae::model::GeneralSkeleton relative_skeleton){
			this->relative_skeleton = relative_skeleton;
		}

		mae::model::GeneralSkeleton FLSkeleton::getRelativeSkeleton(){
			return relative_skeleton;
		}

	} // namespace fl
} // namespace mae
