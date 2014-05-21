/*
 * ISkeletonController.hpp
 *
 *  Created on: 21.05.2014
 *      Author: keks
 */

#ifndef ISKELETONCONTROLLER_HPP_
#define ISKELETONCONTROLLER_HPP_

#include "../model/GeneralSkeleton.hpp"

namespace mae {
	namespace controller {

		template <class T>
		class ISkeletonController {
			public:
				virtual ~ISkeletonController();

				virtual T calculateSpecifiedSkeleton(mae::model::GeneralSkeleton* skeleton) = 0;

		};

	} // namespace controller
} // namespace mae

#endif // ISKELETONCONTROLLER_HPP_
