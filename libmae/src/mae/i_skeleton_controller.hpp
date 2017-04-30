/*
 * ISkeletonController.hpp
 *
 *  Created on: 21.05.2014
 *      Author: keks
 */

#ifndef ISKELETONCONTROLLER_HPP_
#define ISKELETONCONTROLLER_HPP_

//custom includes
#include "general_skeleton.hpp"

//global includes
#include <memory>

namespace mae {
		template <typename T>
		class i_skeleton_controller
		{
			public:
				virtual ~i_skeleton_controller(){ }

				/**
				 * Generates the specified skeleton from the general skeleton.
				 *
				 * @param skeleton The general skeleton.
				 * @param basis (optional) The basis as a system of reference (e.g. the torso basis or the palm basis).
				 * @return The specified skeleton.
				 */
				virtual std::shared_ptr<T> specified_skeleton(std::shared_ptr<general_skeleton> skeleton, std::shared_ptr<mae::math::basis> basis = nullptr) = 0;

		};

} // namespace mae

#endif // ISKELETONCONTROLLER_HPP_
