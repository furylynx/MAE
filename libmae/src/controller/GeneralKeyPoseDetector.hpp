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
#include "IKeyPoseDetector.hpp"

//global includes
#include <iostream>


namespace mae {
	namespace controller {

		class GeneralKeyPoseDetector : public IKeyPoseDetector{
			public:
				GeneralKeyPoseDetector();
				virtual ~GeneralKeyPoseDetector();

				virtual std::shared_ptr<general_enriched_pose> estimateFrame(std::shared_ptr<general_pose> currentPose, std::queue<std::shared_ptr<general_enriched_pose> > previousSequence, std::vector<int> body_parts);
		};

	} // namespace controller
} // namespace mae

#endif // GENERALKEYPOSEDETECTOR_HPP_
