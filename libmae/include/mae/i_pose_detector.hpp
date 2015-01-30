/*
 * IPoseDetector.hpp
 *
 *  Created on: 15.05.2014
 *      Author: keks
 */

#ifndef IPOSEDETECTOR_HPP_
#define IPOSEDETECTOR_HPP_

//eclipse indexer fix
#include "indexer_fix.hpp"

//custom includes
#include "general_pose.hpp"
#include "bone.hpp"

//global includes
#include <vector>
#include <memory>

namespace mae {
		template <typename T>
		class i_pose_detector {
			public:
				virtual ~i_pose_detector(){}

				/**
				 * Processes the skeleton in order to return the pose for each body part.
				 *
				 * @param framerate The framerate.
				 * @param skeleton The skeleton.
				 * @param body_parts The processed body parts.
				 * @param previous_pose The previous pose that can be used for hysteresis.
				 * @return The pose.
				 */
				virtual std::shared_ptr<general_pose> pose(double framerate, std::shared_ptr<T> skeleton, std::vector<bone> body_parts, std::shared_ptr<general_pose> previous_pose) = 0;
		};

} // namespace mae

#endif // IPOSEDETECTOR_HPP_
