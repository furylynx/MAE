/*
 * IKeyPoseDetector.hpp
 *
 *  Created on: 19.05.2014
 *      Author: keks
 */

#ifndef IKEYPOSEDETECTOR_HPP_
#define IKEYPOSEDETECTOR_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "../model/general_pose.hpp"
#include "../model/general_enriched_pose.hpp"

//global includes
#include <vector>
#include <queue>
#include <memory>

namespace mae {

		class i_key_pose_detector {
			public:
				virtual ~i_key_pose_detector(){}

				// edits the handed enriched poses, e.g. setKeyPose(false) but does not append the new enriched pose to the vector
				// instead the new enriched pose is returned
				virtual std::shared_ptr<general_enriched_pose> estimate_frame(std::shared_ptr<general_pose> currentPose, std::queue<std::shared_ptr<general_enriched_pose> > previousSequence, std::vector<int> bodyParts) = 0;
		};

} // namespace mae

#endif // IKEYPOSEDETECTOR_HPP_
