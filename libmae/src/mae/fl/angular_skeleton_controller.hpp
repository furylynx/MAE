#ifndef MAE_FL_ANGULAR_SKELETON_CONTROLLER_HPP_
#define MAE_FL_ANGULAR_SKELETON_CONTROLLER_HPP_

//custom includes
#include "angular_skeleton.hpp"
#include "fl_skeleton_controller.hpp"

#include "e_fl_joint.hpp"

#include "../general_skeleton.hpp"
#include "../i_skeleton_controller.hpp"
#include "../e_joint.hpp"

#include "../math/basis.hpp"

//global includes
#include <vector>
#include <cmath>
#include <memory>
#include <iostream>

namespace mae
{
	namespace fl
	{
		class angular_skeleton_controller : i_skeleton_controller<angular_skeleton>
		{
			public:
				angular_skeleton_controller(bool debug = false);
				virtual ~angular_skeleton_controller();

				/**
				 * Generates the specified skeleton from the general skeleton.
				 *
				 * @param skeleton The general skeleton.
				 * @param basis (optional) The basis as a system of reference (e.g. the torso basis).
				 * @return The specified skeleton.
				 */
				virtual std::shared_ptr<angular_skeleton> specified_skeleton(std::shared_ptr<general_skeleton> skeleton, std::shared_ptr<mae::math::basis> basis = nullptr);

				/**
				 * Generates the angular skeleton from the general one.
				 *
				 * @param skeleton The general skeleton.
				 * @param u The u direction of the basis.
				 * @param r The r direction of the basis.
				 * @param t The t direction of the basis.
				 * @return The specified skeleton.
				 */
				virtual std::shared_ptr<angular_skeleton> calculate_angular_skeleton(std::shared_ptr<general_skeleton> skeleton, std::shared_ptr<mae::math::vec3d> u, std::shared_ptr<mae::math::vec3d> r, std::shared_ptr<mae::math::vec3d> t);

				/**
				 * Calculates first degree joints using a main direction.
				 *
				 * @param skeleton
				 * @param adjacent_joint
				 * @param outer_joint
				 * @param u
				 * @param r
				 * @param t
				 * @param md
				 * @return
				 */
				static std::shared_ptr<angular_joint> first_degree_md(std::shared_ptr<general_skeleton> skeleton, int adjacent_joint, int outer_joint, std::shared_ptr<mae::math::vec3d> u, std::shared_ptr<mae::math::vec3d> r, std::shared_ptr<mae::math::vec3d> t, std::shared_ptr<mae::math::vec3d> md);

				/**
				 * Calculates the first degree joint using the plane to which r is the normal.
				 *
				 * @param skeleton
				 * @param adjacent_joint
				 * @param outer_joint
				 * @param u
				 * @param r
				 * @param t
				 * @return
				 */
				static std::shared_ptr<angular_joint> first_degree_r(std::shared_ptr<general_skeleton> skeleton, int adjacent_joint, int outer_joint, std::shared_ptr<mae::math::vec3d> u, std::shared_ptr<mae::math::vec3d> r, std::shared_ptr<mae::math::vec3d> t);

				/**
				 * Calculates the first degree joint which the general method.
				 *
				 * @param skeleton
				 * @param adjacent_joint
				 * @param outer_joint
				 * @param u
				 * @param r
				 * @param t
				 * @return
				 */
				static std::shared_ptr<angular_joint> first_degree(std::shared_ptr<general_skeleton> skeleton, int adjacent_joint, int outer_joint, std::shared_ptr<mae::math::vec3d> u, std::shared_ptr<mae::math::vec3d> r, std::shared_ptr<mae::math::vec3d> t);

				/**
				 * Calculates the second degree joint.
				 *
				 * @param skeleton
				 * @param adjacent_joint
				 * @param outer_joint
				 * @param extremity_joint
				 * @param u
				 * @param r
				 * @param t
				 * @return
				 */
				static std::shared_ptr<angular_joint> second_degree(std::shared_ptr<general_skeleton> skeleton, int adjacent_joint, int outer_joint, int extremity_joint, std::shared_ptr<mae::math::vec3d> u, std::shared_ptr<mae::math::vec3d> r, std::shared_ptr<mae::math::vec3d> t);

			private:
				bool debug_;
				std::vector<std::vector<int> > skel_extremities;

				std::shared_ptr<fl_skeleton_controller> fl_ctrl_;

		};

	} // namespace fl
} // namespace mae

#endif // MAE_FL_ANGULAR_SKELETON_CONTROLLER_HPP_
