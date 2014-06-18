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
#include "FLSkeleton.hpp"
#include "FLMath.hpp"
#include "FLJ.hpp"
#include "../controller/ISkeletonController.hpp"
#include "../model/GeneralJoint.hpp"
#include "../model/GeneralSkeleton.hpp"
#include "../model/MAEJ.hpp"

//global includes
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>
#include <memory>


namespace mae {
	namespace fl {

		class FLSkeletonController : mae::controller::ISkeletonController<mae::fl::FLSkeleton>
		{

			public:
				FLSkeletonController();
				virtual ~FLSkeletonController();

				virtual std::shared_ptr<mae::fl::FLSkeleton> specified_skeleton(std::shared_ptr<mae::model::GeneralSkeleton> skeleton);


				//only defined in FLSkeletonController
				virtual std::shared_ptr<FLSkeleton> calculate_angular_skeleton(std::shared_ptr<mae::model::GeneralSkeleton> skeleton, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t);

				static cv::Vec2d first_degree_md(std::shared_ptr<mae::model::GeneralSkeleton> skeleton, int adjacent_joint, int outer_joint, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t, cv::Vec3d md);
				static cv::Vec2d first_degree_r(std::shared_ptr<mae::model::GeneralSkeleton> skeleton, int adjacent_joint, int outer_joint, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t);

				static cv::Vec2d first_degree(std::shared_ptr<mae::model::GeneralSkeleton> skeleton, int adjacent_joint, int outer_joint, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t);
				static cv::Vec2d second_degree(std::shared_ptr<mae::model::GeneralSkeleton> skeleton, int adjacent_joint, int outer_joint, int extremity_joint, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t);

			private:
				std::vector<std::vector<int> > skel_extremities;
		};

	} // namespace fl
} // namespace mae

#endif /* FLSKELETONCONTROLLER_HPP_ */
