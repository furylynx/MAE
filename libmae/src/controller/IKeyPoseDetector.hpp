/*
 * IKeyPoseDetector.hpp
 *
 *  Created on: 19.05.2014
 *      Author: keks
 */

#ifndef IKEYPOSEDETECTOR_HPP_
#define IKEYPOSEDETECTOR_HPP_

#include "GeneralPose.hpp"
#include "GeneralEnrichedPose.hpp"

namespace mae {
	namespace controller {

		class IKeyPoseDetector {
			public:
				virtual ~IKeyPoseDetector();

				//TOOD GeneralEnrichedPose
				virtual mae::model::GeneralEnrichedPose* estimateFrame(mae::model::GeneralPose currentPose, mae::model::GeneralEnrichedPose previousSequence[], int previosSequenceSize, int bodyParts[], int bodyPartsSize);
		};

	} // namespace controller
} // namespace mae

#endif /* IKEYPOSEDETECTOR_HPP_ */
