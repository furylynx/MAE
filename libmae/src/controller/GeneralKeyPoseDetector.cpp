/*
 * GeneralKeyPoseDetector.cpp
 *
 *  Created on: 29.05.2014
 *      Author: keks
 */

#include "GeneralKeyPoseDetector.hpp"

namespace mae {
	namespace controller {

		GeneralKeyPoseDetector::GeneralKeyPoseDetector() {
			// TODO Auto-generated constructor stub

		}

		GeneralKeyPoseDetector::~GeneralKeyPoseDetector() {
			// TODO Auto-generated destructor stub
		}


		std::shared_ptr<mae::model::GeneralEnrichedPose> GeneralKeyPoseDetector::estimateFrame(std::shared_ptr<mae::model::GeneralPose> currentPose, std::queue<std::shared_ptr<mae::model::GeneralEnrichedPose> > previousSequence, std::vector<int> bodyParts){

			//todo do stuff in here

			std::shared_ptr<mae::model::GeneralEnrichedPose> result;

			return result;
		}

	} // namespace controller
} // namespace mae
