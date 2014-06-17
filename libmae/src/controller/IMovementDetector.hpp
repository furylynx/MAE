/*
 * IMovementDetector.hpp
 *
 *  Created on: 15.05.2014
 *      Author: keks
 */

#ifndef IMOVEMENTDETECTOR_HPP_
#define IMOVEMENTDETECTOR_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
//...

//global includes
#include <memory>
#include <vector>

namespace mae {
	namespace controller {

		template <typename T, typename U> class IMovementDetector {
			public:
				virtual ~IMovementDetector(){ }

				virtual std::shared_ptr<U> detectMovement(std::shared_ptr<T> skeleton, std::vector<int> bodyParts) = 0;
				virtual void setPoseBufferSize(int size) = 0;
		};

	} // namespace controller
} // namespace mae

#endif // IMOVEMENTDETECTOR_HPP_
