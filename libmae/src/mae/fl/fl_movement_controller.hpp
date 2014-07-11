/*
 * FLMovementController.hpp
 *
 *  Created on: 29.05.2014
 *      Author: keks
 */

#ifndef FLMOVEMENTCONTROLLER_HPP_
#define FLMOVEMENTCONTROLLER_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "fl_skeleton.hpp"
#include "fl_pose_detector.hpp"
#include "fl_skeleton_controller.hpp"

#include "laban/laban_sequence.hpp"
#include "laban/laban_sequence_generator.hpp"

#include "../bone.hpp"
#include "../general_skeleton.hpp"
#include "../movement_controller.hpp"
#include "../i_pose_detector.hpp"

//global includes
#include <iostream>

namespace mae {
	namespace fl {

		class fl_movement_controller : public movement_controller<fl_skeleton, laban::laban_sequence>{
			public:
				fl_movement_controller();
				fl_movement_controller(std::vector<bone> bodyParts);
				virtual ~fl_movement_controller();

				virtual void next_frame(long timestamp, std::shared_ptr<general_skeleton> skeleton);

			private:
				std::shared_ptr<fl_skeleton_controller> skel_ctrl;

		};

	} // namespace fl
} // namespace mae

#endif // FLMOVEMENTCONTROLLER_HPP_
