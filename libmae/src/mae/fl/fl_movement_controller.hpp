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
#include "laban/laban_sequence_recognizer.hpp"

#include "../bone.hpp"
#include "../general_skeleton.hpp"
#include "../movement_controller.hpp"
#include "../i_pose_detector.hpp"

//global includes
#include <iostream>
#include <vector>
#include <memory>


namespace mae {
	namespace fl {

		class fl_movement_controller : public movement_controller<fl_skeleton, laban::laban_sequence>{
			public:
				/**
				 * Creates a new controller for movements analysis based on Labanotation and fl_skeletons.
				 * The used body parts are assumed to be the default ones used by the NITE skeleton. Since
				 * no column definition is given the default columns are the only ones that can be used.
				 *
				 * @param pose_buffer_size The buffer size for the movement detector (number of frames to process). Values <= 1 means calculating the buffer size from the registered sequences.
				 * @param debug True for debug console print.
				 */
				fl_movement_controller(unsigned int pose_buffer_size = 0, bool debug = false);

				/**
				 * Creates a new controller for movements analysis based on Labanotation and fl_skeletons
				 * which handles the given body parts and uses the defined columns for the Labanotation
				 * sequence.
				 *
				 * @param body_parts The body parts which shall be handled.
				 * @param column_definitions The columns which shall be defined besides those that are defined by default.
				 * @param pose_buffer_size The buffer size for the movement detector (number of frames to process).
				 * 		Values <= 1 means calculating the buffer size from the registered sequences.
				 * @param debug True for debug console print.
				 */
				fl_movement_controller(std::vector<bone> body_parts, std::vector<std::shared_ptr<laban::column_definition> > column_definitions, unsigned int pose_buffer_size = 0, bool debug = false);
				virtual ~fl_movement_controller();

				/**
				 * Invokes the processing for a new frame. The skeleton provides the information which
				 * is the basis for any further calculations.
				 *
				 * @param timestamp The timestamp on which the skeleton occured.
				 * @param skeleton The skeleton data for the frame.
				 */
				virtual void next_frame(long timestamp, std::shared_ptr<general_skeleton> skeleton);

			private:
				std::shared_ptr<fl_skeleton_controller> skel_ctrl;

		};

	} // namespace fl
} // namespace mae

#endif // FLMOVEMENTCONTROLLER_HPP_
