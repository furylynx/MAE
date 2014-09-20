/*
 * FLMovementController.cpp
 *
 *  Created on: 29.05.2014
 *      Author: keks
 */

#include "fl_movement_controller.hpp"


namespace mae
{
	namespace fl
	{

		fl_movement_controller::fl_movement_controller(unsigned int pose_buffer_size, double framerate, bool debug)
				: movement_controller(std::shared_ptr<fl_pose_detector>(new fl_pose_detector(debug)),
						std::shared_ptr<laban::laban_sequence_generator>(new laban::laban_sequence_generator(debug)),
						isr_ = std::shared_ptr<laban::laban_sequence_recognizer>(new laban::laban_sequence_recognizer(debug)),
						bone::default_bones(), pose_buffer_size, framerate, debug)
		{
			this->skel_ctrl = std::shared_ptr<fl_skeleton_controller>(new fl_skeleton_controller(debug));
		}

		fl_movement_controller::fl_movement_controller(std::vector<bone> body_parts, std::vector<std::shared_ptr<laban::column_definition> > column_definitions, unsigned int pose_buffer_size, unsigned int beats_per_measure, unsigned int beat_duration, laban::e_time_unit time_unit, double framerate, bool debug)
				: movement_controller(std::shared_ptr<fl_pose_detector>(new fl_pose_detector(debug)),
						std::shared_ptr<laban::laban_sequence_generator>(new laban::laban_sequence_generator(column_definitions, beats_per_measure, beat_duration, time_unit, debug)),
						isr_ = std::shared_ptr<laban::laban_sequence_recognizer>(new laban::laban_sequence_recognizer(column_definitions, beats_per_measure, beat_duration, time_unit, debug)),
						body_parts, pose_buffer_size, framerate, debug)
		{
			this->skel_ctrl = std::shared_ptr<fl_skeleton_controller>(new fl_skeleton_controller(debug));
		}

		fl_movement_controller::~fl_movement_controller()
		{
		}

		void fl_movement_controller::next_frame(long timestamp, std::shared_ptr<general_skeleton> skeleton)
		{
			std::shared_ptr<fl_skeleton> fl_skel = skel_ctrl->specified_skeleton(skeleton);

			//call next_frame for base class
			movement_controller<fl_skeleton, laban::laban_sequence>::next_frame(timestamp, fl_skel);
		}

		void fl_movement_controller::set_recognition_tolerance(double tolerance)
		{
			isr_->set_recognition_tolerance(tolerance);
		}

	} // namespace fl
} // namespace mae
