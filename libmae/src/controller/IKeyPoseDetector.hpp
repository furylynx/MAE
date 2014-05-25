/*
 * IKeyPoseDetector.hpp
 *
 *  Created on: 19.05.2014
 *      Author: keks
 */

#ifndef IKEYPOSEDETECTOR_HPP_
#define IKEYPOSEDETECTOR_HPP_

//custom includes
#include "GeneralPose.hpp"
#include "GeneralEnrichedPose.hpp"

//global includes
#include <vector>
#include <memory>

namespace mae {
	namespace controller {

		class IKeyPoseDetector {
			public:
				virtual ~IKeyPoseDetector(){}

				// edits the handed enriched poses, e.g. setKeyPose(false) but does not append the new enriched pose to the vector
				// instead the new enriched pose is returned
				virtual std::shared_ptr<mae::model::GeneralEnrichedPose> estimateFrame(std::shared_ptr<mae::model::GeneralPose> currentPose, std::vector<std::shared_ptr<mae::model::GeneralEnrichedPose> > previousSequence[], std::vector<int> bodyParts) = 0;
		};

	} // namespace controller
} // namespace mae

#endif // IKEYPOSEDETECTOR_HPP_
