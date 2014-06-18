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
#include "../model/general_skeleton.hpp"
#include "../controller/movement_controller.hpp"
#include "../controller/i_pose_detector.hpp"
#include "fl_skeleton.hpp"
#include "laban_sequence.hpp"
#include "fl_pose_detector.hpp"
#include "laban_sequence_generator.hpp"
#include "fl_skeleton_controller.hpp"
#include "flj.hpp"

//global includes
#include <iostream>


namespace mae {
	namespace fl {

		class fl_movement_controller : movement_controller<fl_skeleton, laban_sequence>{
			public:
				fl_movement_controller();
				fl_movement_controller(std::vector<int> bodyParts);
				virtual ~fl_movement_controller();

				virtual void next_frame(long timestamp,std::shared_ptr<general_skeleton> skeleton);

			private:
				std::shared_ptr<fl_skeleton_controller> skel_ctrl;

		};

	} // namespace fl
} // namespace mae

#endif // FLMOVEMENTCONTROLLER_HPP_
