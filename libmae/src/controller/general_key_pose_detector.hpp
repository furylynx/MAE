/*
 * GeneralKeyPoseDetector.hpp
 *
 *  Created on: 29.05.2014
 *      Author: keks
 */

#ifndef GENERALKEYPOSEDETECTOR_HPP_
#define GENERALKEYPOSEDETECTOR_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "i_key_pose_detector.hpp"

//global includes
#include <iostream>


namespace mae {

		class general_key_pose_detector : public i_key_pose_detector{
			public:
				general_key_pose_detector();
				virtual ~general_key_pose_detector();

				virtual std::shared_ptr<general_enriched_pose> estimate_frame(std::shared_ptr<general_pose> currentPose, std::queue<std::shared_ptr<general_enriched_pose> > previousSequence, std::vector<int> body_parts);
		};

} // namespace mae

#endif // GENERALKEYPOSEDETECTOR_HPP_
