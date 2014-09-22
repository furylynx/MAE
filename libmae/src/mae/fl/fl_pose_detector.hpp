/*
 * FLPoseDetector.hpp
 *
 *  Created on: 29.05.2014
 *      Author: keks
 */

#ifndef FLPOSEDETECTOR_HPP_
#define FLPOSEDETECTOR_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "../i_pose_detector.hpp"
#include "../bone.hpp"

#include "laban/laban_sequence.hpp"

#include "fl_skeleton.hpp"
#include "math.hpp"
#include "e_fl_direction.hpp"

//global includes
#include <opencv2/opencv.hpp>
#include <unordered_map>
#include <memory>
#include <vector>
#include <iostream>


namespace mae
{
	namespace fl
	{

		class fl_pose_detector: public mae::i_pose_detector<fl_skeleton>
		{
			public:
				/**
				 * Creates a new pose detector.
				 *
				 * @param debug (optional) If true debug output on the console is done.
				 */
				fl_pose_detector(bool debug = false);
				virtual ~fl_pose_detector();

				/**
				 * Processes the skeleton in order to return the pose for each body part.
				 *
				 * @param skeleton The skeleton.
				 * @param body_parts The processed body parts.
				 * @return The pose.
				 */
				virtual std::shared_ptr<mae::general_pose> pose(std::shared_ptr<fl_skeleton> skeleton,
						std::vector<bone> body_parts);

				/**
				 * Returns a vector pose which means calculating the pose from the vectors not from angles.
				 *
				 * @param skeleton The skeleton.
				 * @param body_parts The processed body parts.
				 * @return The pose.
				 */
				virtual std::shared_ptr<mae::general_pose> vector_pose(std::shared_ptr<fl_skeleton> skeleton,
														std::vector<bone> body_parts);

			private:
				bool debug_;
				std::unordered_map<int, cv::Vec3d> map_directions_;

				const double PM_ACCEPT_DIST = 22.5;

		};

	} // namespace fl
} // namespace mae

#endif // FLPOSEDETECTOR_HPP_
