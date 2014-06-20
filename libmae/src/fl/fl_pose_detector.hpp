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
#include "../controller/i_pose_detector.hpp"
#include "../model/bone.hpp"
#include "fl_skeleton.hpp"
#include "math.hpp"
#include "laban_sequence.hpp"
#include "fld.hpp"
#include "flj.hpp"

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
				fl_pose_detector();
				virtual ~fl_pose_detector();

				virtual std::shared_ptr<mae::general_pose> pose(std::shared_ptr<fl_skeleton> skeleton,
						std::vector<int> body_parts);

				virtual std::shared_ptr<mae::general_pose> angle_pose(std::shared_ptr<fl_skeleton> skeleton,
										std::vector<int> body_parts);

				virtual std::shared_ptr<mae::general_pose> vector_pose(std::shared_ptr<fl_skeleton> skeleton,
														std::vector<bone> body_parts);

			private:
				std::unordered_map<int, cv::Vec3d> map_directions_;

				const double PM_ACCEPT_DIST = 22.5;

		};

	} // namespace fl
} // namespace mae

#endif // FLPOSEDETECTOR_HPP_
