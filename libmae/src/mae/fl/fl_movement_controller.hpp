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

		class fl_movement_controller : public movement_controller<fl_skeleton, laban::laban_sequence>
		{
			public:
				/**
				 * Creates a new controller for movements analysis based on Labanotation and fl_skeletons.
				 * The used body parts are assumed to be the default ones used by the NITE skeleton. Since
				 * no column definition is given the default columns are the only ones that can be used.
				 *
				 * @param pose_buffer_size The buffer size for the movement detector (number of frames to process). Values <= 1 means calculating the buffer size from the registered sequences.
				 * @param framerate The framerate for the stream.
				 * @param debug True for debug console print.
				 */
				fl_movement_controller(unsigned int pose_buffer_size = 0, double framerate = 1.0/30.0, bool debug = false);

				/**
				 * Creates a new controller for movements analysis based on Labanotation and fl_skeletons
				 * which handles the given body parts and uses the defined columns for the Labanotation
				 * sequence.
				 *
				 * @param body_parts The body parts which shall be handled.
				 * @param column_definitions The columns which shall be defined besides those that are defined by default.
				 * @param pose_buffer_size The buffer size for the movement detector (number of frames to process).
				 * 		Values <= 1 means calculating the buffer size from the registered sequences.
				 * @param beats_per_measure The number of beats per measure.
				 * @param beat_duration The duration of a single beat.
				 * @param time_unit The time unit to be applied.
				 * @param framerate The framerate for the stream.
				 * @param debug True for debug console print.
				 */
				fl_movement_controller(std::vector<bone> body_parts, std::vector<std::shared_ptr<laban::column_definition> > column_definitions, unsigned int pose_buffer_size = 0, unsigned int beats_per_measure = laban::laban_sequence::default_beats_per_measure(), unsigned int beat_duration = laban::laban_sequence::default_beat_duration(), laban::e_time_unit time_unit = laban::laban_sequence::default_time_unit(), double framerate = 1.0/30.0, bool debug = false);

				/**
				 * Creates a new controller for movements analysis based on Labanotation and fl_skeletons
				 * which handles the given body parts and uses the defined columns for the Labanotation
				 * sequence.
				 *
				 * @param body_parts The body parts which shall be handled.
				 * @param column_definitions The columns which shall be defined besides those that are defined by default.
				 * @param sequence_generator
				 * @param pose_buffer_size The buffer size for the movement detector (number of frames to process).
				 * 		Values <= 1 means calculating the buffer size from the registered sequences.
				 * @param beats_per_measure The number of beats per measure.
				 * @param beat_duration The duration of a single beat.
				 * @param time_unit The time unit to be applied.
				 * @param framerate The framerate for the stream.
				 * @param debug True for debug console print.
				 */
				fl_movement_controller(std::vector<bone> body_parts, std::vector<std::shared_ptr<laban::column_definition> > column_definitions, std::shared_ptr<mae::fl::laban::laban_sequence_generator> sequence_generator, unsigned int pose_buffer_size = 0, unsigned int beats_per_measure = laban::laban_sequence::default_beats_per_measure(), unsigned int beat_duration = laban::laban_sequence::default_beat_duration(), laban::e_time_unit time_unit = laban::laban_sequence::default_time_unit(), double framerate = 1.0/30.0, bool debug = false);


				virtual ~fl_movement_controller();

				/**
				 * Invokes the processing for a new frame. The skeleton provides the information which
				 * is the basis for any further calculations.
				 *
				 * @param timestamp The timestamp on which the skeleton occured.
				 * @param skeleton The skeleton data for the frame.
				 */
				virtual void next_frame(long timestamp, std::shared_ptr<general_skeleton> skeleton);

				/**
				 * Sets the tolerance for the recognition. The tolerance is a value which represents the
				 * number of beats of the labanotation which are tolerated in deviation.
				 *
				 * @param tolerance The tolerance to be accepted.
				 */
				virtual void set_recognition_tolerance(double tolerance);

				/**
				 * Returns the laban sequence recognizer.
				 *
				 * @return The recognizer.
				 */
				virtual std::shared_ptr<mae::fl::laban::laban_sequence_recognizer> get_laban_sequence_recognizer() const;

				/**
				 * Returns the laban sequence generator.
				 *
				 * @return The generator.
				 */
				virtual std::shared_ptr<mae::fl::laban::laban_sequence_generator> get_laban_sequence_generator() const;

				/**
				 * Returns the fl pose detector.
				 *
				 * @return The detector.
				 */
				virtual std::shared_ptr<fl_pose_detector> get_fl_pose_detector() const;

			private:
				std::shared_ptr<fl_skeleton_controller> skel_ctrl_;

				std::shared_ptr<mae::fl::laban::laban_sequence_recognizer> lsr_;
				std::shared_ptr<mae::fl::laban::laban_sequence_generator> lsg_;
				std::shared_ptr<fl_pose_detector> flpd_;


				bool debug_;


				virtual void initialize();

		};

	} // namespace fl
} // namespace mae

#endif // FLMOVEMENTCONTROLLER_HPP_
