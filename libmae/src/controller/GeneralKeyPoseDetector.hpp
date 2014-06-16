/*
 * GeneralKeyPoseDetector.hpp
 *
 *  Created on: 29.05.2014
 *      Author: keks
 */

#ifndef GENERALKEYPOSEDETECTOR_HPP_
#define GENERALKEYPOSEDETECTOR_HPP_

//eclipse indexer fix
#include "indexer_fix.hpp"

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

				virtual std::shared_ptr<mae::model::GeneralEnrichedPose> estimateFrame(std::shared_ptr<mae::model::GeneralPose> currentPose, std::queue<std::shared_ptr<mae::model::GeneralEnrichedPose> > previousSequence, std::vector<int> bodyParts);
		};

	} // namespace controller
} // namespace mae

#endif // GENERALKEYPOSEDETECTOR_HPP_
