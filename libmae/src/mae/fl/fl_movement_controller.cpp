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
				: movement_controller(
						std::shared_ptr<fl_pose_detector>(
								new fl_pose_detector(fl_pose_detector::default_hysteresis_val(), debug)),
						std::shared_ptr<laban::laban_sequence_generator>(new laban::laban_sequence_generator(debug)),
						std::shared_ptr<laban::laban_sequence_recognizer>(new laban::laban_sequence_recognizer(debug)),
						bone::default_bones(), pose_buffer_size, framerate, debug)
		{
			debug_ = debug;

			initialize();
		}

		fl_movement_controller::fl_movement_controller(std::vector<bone> body_parts,
				std::vector<std::shared_ptr<laban::column_definition> > column_definitions,
				unsigned int pose_buffer_size, unsigned int beats_per_measure, unsigned int beat_duration,
				laban::e_time_unit time_unit, double framerate, bool debug)
				: movement_controller(
						std::shared_ptr<fl_pose_detector>(
								new fl_pose_detector(fl_pose_detector::default_hysteresis_val(), debug)),
						std::shared_ptr<laban::laban_sequence_generator>(
								new laban::laban_sequence_generator(column_definitions, beats_per_measure,
										beat_duration, time_unit, debug)),
						std::shared_ptr<laban::laban_sequence_recognizer>(
								new laban::laban_sequence_recognizer(column_definitions, beats_per_measure,
										beat_duration, time_unit, debug)), body_parts, pose_buffer_size, framerate,
						debug)
		{
			debug_ = debug;

			initialize();
		}

		fl_movement_controller::fl_movement_controller(std::vector<bone> body_parts, std::vector<std::shared_ptr<laban::column_definition> > column_definitions, std::shared_ptr<mae::fl::laban::laban_sequence_generator> sequence_generator, unsigned int pose_buffer_size, unsigned int beats_per_measure, unsigned int beat_duration, laban::e_time_unit time_unit, double framerate, bool debug)
		: movement_controller(
								std::shared_ptr<fl_pose_detector>(
										new fl_pose_detector(fl_pose_detector::default_hysteresis_val(), debug)),
								sequence_generator,
								std::shared_ptr<laban::laban_sequence_recognizer>(
										new laban::laban_sequence_recognizer(column_definitions, beats_per_measure,
												beat_duration, time_unit, debug)), body_parts, pose_buffer_size, framerate,
								debug)
		{
			debug_ = debug;

			initialize();
		}


		fl_movement_controller::~fl_movement_controller()
		{
		}

		void fl_movement_controller::initialize()
		{
			if (debug_)
			{
				std::cout << "fl movement controller created." << std::endl;
			}

			skel_ctrl_ = std::shared_ptr<fl_skeleton_controller>(new fl_skeleton_controller(debug_));

			lsr_ = std::dynamic_pointer_cast<mae::fl::laban::laban_sequence_recognizer>(get_sequence_recognizer());
			std::shared_ptr<mae::kp_movement_detector<fl_skeleton, laban::laban_sequence> > kp_det = std::dynamic_pointer_cast<mae::kp_movement_detector<fl_skeleton, laban::laban_sequence> >(get_movement_detector());
			lsg_ = std::dynamic_pointer_cast<laban::laban_sequence_generator>(kp_det->get_sequence_generator());
			flpd_ = std::dynamic_pointer_cast<fl_pose_detector>(kp_det->get_pose_detector());
		}

		void fl_movement_controller::next_frame(long timestamp, std::shared_ptr<general_skeleton> skeleton)
		{
			if (debug_)
			{
				std::cout << "fl movement controller: next frame" << std::endl;
			}

			std::shared_ptr<fl_skeleton> fl_skel = skel_ctrl_->specified_skeleton(skeleton);

			//call next_frame for base class
			movement_controller<fl_skeleton, laban::laban_sequence>::next_frame(timestamp, fl_skel);
		}

		void fl_movement_controller::set_recognition_tolerance(double tolerance)
		{
			if (lsr_ != nullptr)
			{
				lsr_->set_recognition_tolerance(tolerance);
			}
		}

		std::shared_ptr<laban::laban_sequence_recognizer> fl_movement_controller::get_laban_sequence_recognizer() const
		{
			return lsr_;
		}

		std::shared_ptr<mae::fl::laban::laban_sequence_generator> fl_movement_controller::get_laban_sequence_generator() const
		{
			return lsg_;
		}

		std::shared_ptr<fl_pose_detector> fl_movement_controller::get_fl_pose_detector() const
		{
			return flpd_;
		}

	} // namespace fl
} // namespace mae
