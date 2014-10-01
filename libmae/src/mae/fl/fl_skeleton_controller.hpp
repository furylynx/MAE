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
#include "fl_skeleton.hpp"
#include "math.hpp"
#include "e_fl_joint.hpp"

#include "../i_skeleton_controller.hpp"
#include "../general_joint.hpp"
#include "../general_skeleton.hpp"
#include "../e_joint.hpp"

//global includes
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>
#include <memory>
#include <iostream>

namespace mae
{
	namespace fl
	{

		class fl_skeleton_controller: mae::i_skeleton_controller<mae::fl::fl_skeleton>
		{

			public:
				/**
				 * Create a new skeleton controller which generates a fl_skeleton from the general skeleton.
				 *
				 * @param debug (optional) If true debug output will be printed to the terminal.
				 */
				fl_skeleton_controller(bool debug = false);
				virtual ~fl_skeleton_controller();

				/**
				 * Generates the specified skeleton from the general skeleton.
				 *
				 * @param skeleton The general skeleton.
				 * @return The specified skeleton.
				 */
				virtual std::shared_ptr<fl_skeleton> specified_skeleton(std::shared_ptr<general_skeleton> skeleton);

				/**
				 * Creates the torso basis for the given general skeleton.
				 *
				 * @param skeleton The skeleton.
				 * @return The torso basis.
				 */
				virtual std::shared_ptr<basis> create_torso_basis(std::shared_ptr<general_skeleton> skeleton);

			private:
				bool debug_;
		};

	} // namespace fl
} // namespace mae

#endif /* FLSKELETONCONTROLLER_HPP_ */
