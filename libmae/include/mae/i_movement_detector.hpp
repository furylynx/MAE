/*
 * IMovementDetector.hpp
 *
 *  Created on: 15.05.2014
 *      Author: keks
 */

#ifndef IMOVEMENTDETECTOR_HPP_
#define IMOVEMENTDETECTOR_HPP_

//eclipse indexer fix
#include "indexer_fix.hpp"

//custom includes
#include "i_pose_listener.hpp"
#include "bone.hpp"

//global includes
#include <memory>
#include <vector>

namespace mae {

		template <typename T, typename U> class i_movement_detector {
			public:
				virtual ~i_movement_detector(){ }

				/**
				 * Detects movement in the streamed skeleton sequence for the given body parts. Therefore, a buffer is required
				 * and the whole movement sequence for the buffer is returned.
				 *
				 * @param timestamp The timestamp of the current frame as provided by the user. It is not save to rely on this value.
				 * @param framerate The framerate to be applied. The framerate does not change.
				 * @param skeleton The skeleton data.
				 * @param body_parts The addressed body parts.
				 * @return The detected movement sequence.
				 */
				virtual std::shared_ptr<U> detect_movement(uint64_t timestamp, double framerate, std::shared_ptr<T> skeleton, std::vector<bone> body_parts) = 0;

				/**
				 * Updates the buffer size used to store the skeleton data.
				 *
				 * @param size The buffer size.
				 */
				virtual void set_buffer(int size) = 0;

				/**
				 * Clears the buffer used to store the data.
				 */
				virtual void clear_buffer() = 0;

				/**
				 * Adds a pose listener to the detector. The listeners are invoked whenever a pose is fully detected (each frame).
				 *
				 * @param listener The listener to be added.
				 */
				virtual void add_listener(std::shared_ptr<i_pose_listener> listener) = 0;

				/**
				 * Removes the listener from the detector.
				 *
				 * @param listener The listener to be removed.
				 */
				virtual void remove_listener(std::shared_ptr<i_pose_listener> listener) = 0;

				/**
				 * Clears all listeners, which means removing them from the detector.
				 */
				virtual void clear_listeners() = 0;

				/**
				 * Notifies all listeners on the detection of a new pose.
				 *
				 * @param timestamp
				 * @param pose
				 */
				virtual void notify_listeners(uint64_t timestamp, std::shared_ptr<general_pose> pose) = 0;

				/**
				 * Returns the last processed pose.
				 *
				 * @return The last processed pose.
				 */
				virtual std::shared_ptr<general_pose> get_current_pose() const = 0;
		};

} // namespace mae

#endif // IMOVEMENTDETECTOR_HPP_
