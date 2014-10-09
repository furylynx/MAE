/*
 * angular_skeleton_controller.hpp
 *
 *  Created on: 29.09.2014
 *      Author: keks
 */

#ifndef ANGULAR_SKELETON_CONTROLLER_HPP_
#define ANGULAR_SKELETON_CONTROLLER_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "angular_skeleton.hpp"
#include "fl_skeleton_controller.hpp"

#include "e_fl_joint.hpp"

#include "../general_skeleton.hpp"
#include "../i_skeleton_controller.hpp"
#include "../e_joint.hpp"
#include "../math/math.hpp"

#include "../math/basis.hpp"

//global includes
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>
#include <memory>
#include <iostream>

namespace mae
{
	namespace fl
	{
		class angular_skeleton_controller : i_skeleton_controller<angular_skeleton>
		{
			public:
				angular_skeleton_controller(bool debug = false);
				virtual ~angular_skeleton_controller();

				/**
				 * Generates the specified skeleton from the general skeleton.
				 *
				 * @param skeleton The general skeleton.
				 * @return The specified skeleton.
				 */
				virtual std::shared_ptr<angular_skeleton> specified_skeleton(std::shared_ptr<general_skeleton> skeleton);

				/**
				 * Generates the angular skeleton from the general one.
				 *
				 * @param skeleton The general skeleton.
				 * @param u The u direction of the basis.
				 * @param r The r direction of the basis.
				 * @param t The t direction of the basis.
				 * @return The specified skeleton.
				 */
				virtual std::shared_ptr<angular_skeleton> calculate_angular_skeleton(std::shared_ptr<general_skeleton> skeleton, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t);

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

				std::shared_ptr<fl_skeleton_controller> fl_ctrl_;

		};

	} // namespace fl
} // namespace mae

#endif // ANGULAR_SKELETON_CONTROLLER_HPP_
