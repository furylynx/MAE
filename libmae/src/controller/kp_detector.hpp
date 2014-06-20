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
#include "i_kp_detector.hpp"

#include "../model/bone.hpp"

//global includes
#include <iostream>


namespace mae {

		class kp_detector : public i_kp_detector{
			public:
				kp_detector();
				virtual ~kp_detector();

				virtual std::shared_ptr<general_enriched_pose> estimate_frame(std::shared_ptr<general_pose> currentPose, std::queue<std::shared_ptr<general_enriched_pose> > previousSequence, std::vector<bone> body_parts);
		};

} // namespace mae

#endif // GENERALKEYPOSEDETECTOR_HPP_
