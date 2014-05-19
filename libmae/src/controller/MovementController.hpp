/*
 * MovementController.hpp
 *
 *  Created on: 15.05.2014
 *      Author: keks
 */

#ifndef MOVEMENTCONTROLLER_HPP_
#define MOVEMENTCONTROLLER_HPP_

#include "IMovementDetector.hpp"

namespace mae{
	namespace controller {

		template <class T, class U>
		class MovementController {
			public:
				MovementController(mae::controller::IMovementDetector<T,U> imd, int bodyParts[], int bodyPartsSize);
				virtual ~MovementController();

				//todo other methods in here

		};

	} //namespace controller
} // namespace mae

#endif // MOVEMENTCONTROLLER_HPP_
