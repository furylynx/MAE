/*
 * FLSkeletonController.hpp
 *
 *  Created on: 21.05.2014
 *      Author: keks
 */

#ifndef FLSKELETONCONTROLLER_HPP_
#define FLSKELETONCONTROLLER_HPP_

//custom includes
#include "FLSkeleton.hpp"
#include "../controller/ISkeletonController.hpp"
#include "../model/GeneralJoint.hpp"

//global includes
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>


namespace mae {
	namespace fl {

		class FLSkeletonController : mae::controller::ISkeletonController<mae::fl::FLSkeleton> {
			public:
				FLSkeletonController();
				virtual ~FLSkeletonController();

				virtual mae::fl::FLSkeleton calculateSpecifiedSkeleton(mae::model::GeneralSkeleton* skeleton);


				//only defined in FLSkeletonController
				virtual cv::Vec3d projectOrthogonal(cv::Vec3d point, cv::Vec3d position_vector, cv::Vec3d plane_u, cv::Vec3d plane_v);
				virtual cv::Vec2d calcFirstDegreeJoint(int adjacent_joint, int outer_joint, cv::Vec3d r, cv::Vec3d t, cv::Vec3d u);
		};

	} /* namespace fl */
} /* namespace mae */

#endif /* FLSKELETONCONTROLLER_HPP_ */
