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
#include "flj.hpp"

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


namespace mae {
	namespace fl {

		class fl_skeleton_controller : mae::i_skeleton_controller<mae::fl::fl_skeleton>
		{

			public:
				fl_skeleton_controller();
				virtual ~fl_skeleton_controller();

				virtual std::shared_ptr<mae::fl::fl_skeleton> specified_skeleton(std::shared_ptr<general_skeleton> skeleton);


				//only defined in FLSkeletonController
				virtual std::shared_ptr<fl_skeleton> calculate_angular_skeleton(std::shared_ptr<general_skeleton> skeleton, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t);

				static cv::Vec2d first_degree_md(std::shared_ptr<general_skeleton> skeleton, int adjacent_joint, int outer_joint, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t, cv::Vec3d md);
				static cv::Vec2d first_degree_r(std::shared_ptr<general_skeleton> skeleton, int adjacent_joint, int outer_joint, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t);

				static cv::Vec2d first_degree(std::shared_ptr<general_skeleton> skeleton, int adjacent_joint, int outer_joint, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t);
				static cv::Vec2d second_degree(std::shared_ptr<general_skeleton> skeleton, int adjacent_joint, int outer_joint, int extremity_joint, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t);

			private:
				std::vector<std::vector<int> > skel_extremities;
		};

	} // namespace fl
} // namespace mae

#endif /* FLSKELETONCONTROLLER_HPP_ */
