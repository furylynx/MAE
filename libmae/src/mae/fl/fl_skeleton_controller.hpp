#ifndef MAE_FL_FLSKELETONCONTROLLER_HPP_
#define MAE_FL_FLSKELETONCONTROLLER_HPP_

//custom includes
#include "fl_skeleton.hpp"
#include "e_fl_joint.hpp"

#include "../i_skeleton_controller.hpp"
#include "../general_joint.hpp"
#include "../general_skeleton.hpp"
#include "../e_joint.hpp"

#include "../math/math.hpp"

//global includes
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
				 * Generates the specified skeleton from the general skeleton using the given torso basis.
				 *
				 * @param skeleton The skeleton to be translated.
				 * @param basis (optional) The basis meant to be used as a system of reference (e.g. the torso basis or the palm basis). Uses nullptr as default.
				 * @return The specified skeleton.
				 */
				virtual std::shared_ptr<fl_skeleton> specified_skeleton(std::shared_ptr<general_skeleton> skeleton, std::shared_ptr<mae::math::basis> basis = nullptr);

				/**
				 * Creates the basis (formerly torso basis) for the given general skeleton as a system of reference (e.g. the torso basis or the palm basis). Uses the hierarchy to determine base joints.
				 *
				 * @param skeleton The skeleton.
				 * @return The torso basis.
				 */
				[[deprecated("Replaced by create_basis()")]]
				virtual std::shared_ptr<mae::math::basis> create_torso_basis(std::shared_ptr<general_skeleton> skeleton);


				/**
				 * Creates the basis for the given general skeleton as a system of reference (e.g. the torso basis or the palm basis). Uses the hierarchy to determine base joints.
				 *
				 * @param skeleton The skeleton.
				 * @return The torso basis.
				 */
				virtual std::shared_ptr<mae::math::basis> create_basis(std::shared_ptr<general_skeleton> skeleton);

		private:
			bool debug_;
		};

	} // namespace fl
} // namespace mae

#endif /* MAE_FL_FLSKELETONCONTROLLER_HPP_ */
