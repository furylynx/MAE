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

		template <typename T, typename U> class i_movement_detector {
			public:
				virtual ~i_movement_detector(){ }

				virtual std::shared_ptr<U> detect_movement(std::shared_ptr<T> skeleton, std::vector<int> bodyParts) = 0;
				virtual void set_buffer(int size) = 0;
		};

} // namespace mae

#endif // IMOVEMENTDETECTOR_HPP_
