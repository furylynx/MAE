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
#include "../model/pose_listener.hpp"
#include "../model/bone.hpp"

//global includes
#include <memory>
#include <vector>

namespace mae {

		template <typename T, typename U> class i_movement_detector {
			public:
				virtual ~i_movement_detector(){ }

				virtual std::shared_ptr<U> detect_movement(std::shared_ptr<T> skeleton, std::vector<bone> body_parts) = 0;
				virtual void set_buffer(int size) = 0;

				virtual void add_listener(std::shared_ptr<pose_listener> listener) = 0;
				virtual void remove_listener(std::shared_ptr<pose_listener> listener) = 0;
				virtual void clear_listeners() = 0;

				virtual void notify_listeners(long timestamp, std::shared_ptr<general_pose> pose) = 0;
		};

} // namespace mae

#endif // IMOVEMENTDETECTOR_HPP_
