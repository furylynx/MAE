/*
 * ISkeletonController.hpp
 *
 *  Created on: 21.05.2014
 *      Author: keks
 */

#ifndef ISKELETONCONTROLLER_HPP_
#define ISKELETONCONTROLLER_HPP_

//eclipse indexer fix
#include "indexer_fix.hpp"

//custom includes
#include "general_skeleton.hpp"

//global includes
#include <memory>

namespace mae {
		template <typename T>
		class i_skeleton_controller {
			public:
				virtual ~i_skeleton_controller(){ }

				virtual std::shared_ptr<T> specified_skeleton(std::shared_ptr<general_skeleton> skeleton) = 0;

		};

} // namespace mae

#endif // ISKELETONCONTROLLER_HPP_
