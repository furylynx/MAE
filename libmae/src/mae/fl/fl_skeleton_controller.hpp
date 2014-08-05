/*
 * FLSkeletonController.hpp
 *
 *  Created on: 21.05.2014
 *      Author: keks
 */

#ifndef FLSKELETONCONTROLLER_HPP_
#define FLSKELETONCONTROLLER_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "fl_skeleton.hpp"
#include "math.hpp"
#include "e_fl_joint.hpp"

#include "../i_skeleton_controller.hpp"
#include "../general_joint.hpp"
#include "../general_skeleton.hpp"
#include "../e_joint.hpp"

//global includes
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>
#include <memory>
#include <iostream>

namespace mae {
	namespace fl {

		class fl_skeleton_controller : mae::i_skeleton_controller<mae::fl::fl_skeleton>
		{

			public:
				/**
				 * Createa a new skeleton controller which generates a fl_skeleton from the general skeleton.
				 *
				 * @param debug (optional) If true debug output will be printed to the terminal.
				 */
				fl_skeleton_controller(bool debug = false);
				virtual ~fl_skeleton_controller();

				/**
				 * Generates the specified skeleton from the general skeleton.
				 *
				 * @param skeleton The general skeleton.
				 * @return The specified skeleton.
				 */
				virtual std::shared_ptr<fl_skeleton> specified_skeleton(std::shared_ptr<general_skeleton> skeleton);


				/**
				 * Generates the angular skeleton from the general one.
				 *
				 * @param skeleton The general skeleton.
				 * @param u The u direction of the basis.
				 * @param r The r direction of the basis.
				 * @param t The t direction of the basis.
				 * @return The specified skeleton.
				 */
				virtual std::shared_ptr<fl_skeleton> calculate_angular_skeleton(std::shared_ptr<general_skeleton> skeleton, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t);

				/**
				 * Calculates first degree joints using a main direction.
				 *
				 * @param skeleton
				 * @param adjacent_joint
				 * @param outer_joint
				 * @param u
				 * @param r
				 * @param t
				 * @param md
				 * @return
				 */
				static cv::Vec2d first_degree_md(std::shared_ptr<general_skeleton> skeleton, int adjacent_joint, int outer_joint, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t, cv::Vec3d md);

				/**
				 * Calculates the first degree joint using the plane to which r is the normal.
				 *
				 * @param skeleton
				 * @param adjacent_joint
				 * @param outer_joint
				 * @param u
				 * @param r
				 * @param t
				 * @return
				 */
				static cv::Vec2d first_degree_r(std::shared_ptr<general_skeleton> skeleton, int adjacent_joint, int outer_joint, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t);

				/**
				 * Calculates the first degree joint which the general method.
				 *
				 * @param skeleton
				 * @param adjacent_joint
				 * @param outer_joint
				 * @param u
				 * @param r
				 * @param t
				 * @return
				 */
				static cv::Vec2d first_degree(std::shared_ptr<general_skeleton> skeleton, int adjacent_joint, int outer_joint, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t);

				/**
				 * Calculates the second degree joint.
				 *
				 * @param skeleton
				 * @param adjacent_joint
				 * @param outer_joint
				 * @param extremity_joint
				 * @param u
				 * @param r
				 * @param t
				 * @return
				 */
				static cv::Vec2d second_degree(std::shared_ptr<general_skeleton> skeleton, int adjacent_joint, int outer_joint, int extremity_joint, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t);

			private:
				bool debug_;
				std::vector<std::vector<int> > skel_extremities;
		};

	} // namespace fl
} // namespace mae

#endif /* FLSKELETONCONTROLLER_HPP_ */
