/*
 * GeneralKeyPoseDetector.cpp
 *
 *  Created on: 29.05.2014
 *      Author: keks
 */

#include "general_key_pose_detector.hpp"

namespace mae {

		general_key_pose_detector::general_key_pose_detector() {
			// TODO Auto-generated constructor stub

		}

		general_key_pose_detector::~general_key_pose_detector() {
			// TODO Auto-generated destructor stub
		}


		std::shared_ptr<general_enriched_pose> general_key_pose_detector::estimate_frame(std::shared_ptr<general_pose> currentPose, std::queue<std::shared_ptr<general_enriched_pose> > previousSequence, std::vector<int> bodyParts){

			//todo do stuff in here

			std::shared_ptr<general_enriched_pose> result;

			//last local minimum of distance denotes  the start of the motion
			// probably do a low pass filtering in here

			//first local maximum of distance denotes the key pose (key pose is moved when new frames come in)

			std::cout << "estimate frame (key pose detection)" << std::endl;

			return result;
		}

} // namespace mae
