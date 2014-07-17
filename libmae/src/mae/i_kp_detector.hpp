/*
 * IKeyPoseDetector.hpp
 *
 *  Created on: 19.05.2014
 *      Author: keks
 */

#ifndef IKEYPOSEDETECTOR_HPP_
#define IKEYPOSEDETECTOR_HPP_

//eclipse indexer fix
#include "indexer_fix.hpp"

//custom includes
#include "general_pose.hpp"
#include "general_enriched_pose.hpp"
#include "bone.hpp"

//global includes
#include <vector>
#include <list>
#include <memory>

namespace mae {

		class i_kp_detector {
			public:
				virtual ~i_kp_detector(){}

				// edits the handed enriched poses, e.g. setKeyPose(false) but does not append the new enriched pose to the vector
				// instead the new enriched pose is returned
				virtual std::shared_ptr<general_enriched_pose> estimate_frame(std::shared_ptr<general_pose> currentPose, std::list<std::shared_ptr<general_enriched_pose> > previousSequence, std::vector<bone> bodyParts) = 0;
		};

} // namespace mae

#endif // IKEYPOSEDETECTOR_HPP_