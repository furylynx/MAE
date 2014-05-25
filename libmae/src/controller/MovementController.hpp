/*
 * MovementController.hpp
 *
 *  Created on: 15.05.2014
 *      Author: keks
 */

#ifndef MOVEMENTCONTROLLER_HPP_
#define MOVEMENTCONTROLLER_HPP_

//custom includes
#include "IMovementDetector.hpp"

//global includes
#include <vector>
#include <memory>

namespace mae{
	namespace controller {

		template <typename T, typename U>
		class MovementController {
			public:
				MovementController(std::shared_ptr<mae::controller::IMovementDetector<T,U> > imd, std::vector<int> bodyParts);
				virtual ~MovementController();

				//todo other methods in here

		};

	} //namespace controller
} // namespace mae

#endif // MOVEMENTCONTROLLER_HPP_
