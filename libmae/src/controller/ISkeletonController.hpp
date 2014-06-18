/*
 * ISkeletonController.hpp
 *
 *  Created on: 21.05.2014
 *      Author: keks
 */

#ifndef ISKELETONCONTROLLER_HPP_
#define ISKELETONCONTROLLER_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "../model/general_skeleton.hpp"

//global includes
#include <memory>

namespace mae {
	namespace controller {

		template <typename T>
		class ISkeletonController {
			public:
				virtual ~ISkeletonController(){ }

				virtual std::shared_ptr<T> specified_skeleton(std::shared_ptr<general_skeleton> skeleton) = 0;

		};

	} // namespace controller
} // namespace mae

#endif // ISKELETONCONTROLLER_HPP_
