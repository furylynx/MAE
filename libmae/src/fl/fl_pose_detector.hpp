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
#include "fl_skeleton.hpp"
#include "math.hpp"
#include "laban_sequence.hpp"
#include "fld.hpp"
#include "flj.hpp"

//global includes
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

			private:
				std::vector<std::vector<int> > dir_circ;
				std::vector<int> flj_ext_bones;
				std::vector<int> flj_ext_whole;
		};

	} // namespace fl
} // namespace mae

#endif // FLPOSEDETECTOR_HPP_
