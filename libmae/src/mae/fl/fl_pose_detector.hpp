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

#include "fl_skeleton.hpp"
#include "e_fl_direction.hpp"

#include "../math/math.hpp"

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
				 * @param hysteresis_val The value applied for the hysteris. 22.5 for no hysteresis.
				 * @param debug (optional) If true debug output on the console is done.
				 */
				fl_pose_detector(double hysteresis_val = fl_pose_detector::default_hysteresis_val(), bool debug = false);
				virtual ~fl_pose_detector();

				/**
				 * Sets the hysteresis threshold value.
				 *
				 * @param hysteresis_val The value.
				 */
				virtual void set_hysteresis_val(double hysteresis_val);

				/**
				 * Returns the hysteresis threshold value.
				 *
				 * @return The value.
				 */
				virtual double get_hysteresis_val() const;

				/**
				 * Processes the skeleton in order to return the pose for each body part.
				 *
				 * @param skeleton The skeleton.
				 * @param body_parts The processed body parts.
				 * @param previous_pose The previous pose that can be used for hysteresis.
				 * @return The pose.
				 */
				virtual std::shared_ptr<mae::general_pose> pose(std::shared_ptr<fl_skeleton> skeleton,
						std::vector<bone> body_parts, std::shared_ptr<general_pose> previous_pose);

				/**
				 * Returns a vector pose which means calculating the pose from the vectors not from angles.
				 *
				 * @param skeleton The skeleton.
				 * @param body_parts The processed body parts.
				 * @param previous_pose The previous pose that can be used for hysteresis.
				 * @return The pose.
				 */
				virtual std::shared_ptr<mae::general_pose> vector_pose(std::shared_ptr<fl_skeleton> skeleton,
														std::vector<bone> body_parts, std::shared_ptr<general_pose> previous_pose);

				/**
				 * Returns the default hysteresis threshold value.
				 *
				 * @return The default hysteresis threshold value.
				 */
				static double default_hysteresis_val();
			private:
				bool debug_;
				std::unordered_map<int, cv::Vec3d> map_directions_;
				double hysteresis_val_;

				const double PM_ACCEPT_DIST = 22.5;

		};

	} // namespace fl
} // namespace mae

#endif // FLPOSEDETECTOR_HPP_
