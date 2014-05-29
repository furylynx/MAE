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
#include "IPoseDetector.hpp"
#include "ISequenceGenerator.hpp"
#include "KPMovementDetector.hpp"

//global includes
#include <vector>
#include <memory>
#include <chrono>

namespace mae{
	namespace controller {

		template <typename T, typename U>
		class MovementController {
			public:

				MovementController(std::shared_ptr<IMovementDetector<T,U> > imd, std::vector<int> bodyParts);
				MovementController(std::shared_ptr<IPoseDetector<T> > ipd, std::shared_ptr<ISequenceGenerator<U> > isg, std::vector<int> bodyParts);
				virtual ~MovementController();

				//todo other methods in here
				virtual void nextFrame(long timestamp,std::shared_ptr<T> skeleton);

				//todo listener stuff

			private:
				std::shared_ptr<IMovementDetector<T,U> > imd;
				std::vector<int> bodyParts;

		};

	} //namespace controller
} // namespace mae


//include implementation of the template
#include "MovementController.tpp"


#endif // MOVEMENTCONTROLLER_HPP_
