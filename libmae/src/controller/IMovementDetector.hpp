/*
 * IMovementDetector.hpp
 *
 *  Created on: 15.05.2014
 *      Author: keks
 */

#ifndef IMOVEMENTDETECTOR_HPP_
#define IMOVEMENTDETECTOR_HPP_

//custom includes
//...

//global includes
#include <memory>

namespace mae {
	namespace controller {

		template <class T, class U> class IMovementDetector {
			public:
				virtual ~IMovementDetector();

				virtual std::shared_ptr<U> detectMovement(std::shared_ptr<T> skeleton) = 0;
				virtual void setPoseBufferSize(int size) = 0;
		};

	} // namespace controller
} // namespace mae

#endif // IMOVEMENTDETECTOR_HPP_
