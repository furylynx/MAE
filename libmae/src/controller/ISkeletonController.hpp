/*
 * ISkeletonController.hpp
 *
 *  Created on: 21.05.2014
 *      Author: keks
 */

#ifndef ISKELETONCONTROLLER_HPP_
#define ISKELETONCONTROLLER_HPP_

//custom includes
#include "../model/GeneralSkeleton.hpp"

//global includes
#include <memory>

namespace mae {
	namespace controller {

		template <typename T>
		class ISkeletonController {
			public:
				virtual ~ISkeletonController(){ }

				virtual std::shared_ptr<T> calculateSpecifiedSkeleton(std::shared_ptr<mae::model::GeneralSkeleton> skeleton) = 0;

		};

	} // namespace controller
} // namespace mae

#endif // ISKELETONCONTROLLER_HPP_
