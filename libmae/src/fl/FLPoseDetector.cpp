/*
 * FLPoseDetector.cpp
 *
 *  Created on: 29.05.2014
 *      Author: keks
 */

#include "FLPoseDetector.hpp"

namespace mae {
	namespace fl {

		FLPoseDetector::FLPoseDetector() {
		}

		FLPoseDetector::~FLPoseDetector() {
		}


		std::shared_ptr<mae::model::GeneralPose> FLPoseDetector::detectPose(std::shared_ptr<FLSkeleton> skeleton, std::vector<int> bodyParts)
		{

			//todo remove (is here just to show this method is invoked)
			std::cout << "detecting pose for skeleton" << std::endl;
			std::cout << "ANGLE_LEFT_FOREARM: " << *skeleton->getJoint(mae::fl::FLSkeleton::ANGLE_LEFT_FOREARM) << std::endl;


			std::shared_ptr<mae::model::GeneralPose> result;

			//todo do stuff in here

			return result;
		}

	} // namespace fl
} // namespace mae
