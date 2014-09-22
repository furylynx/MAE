/*
 * KPMovementDetector.hpp
 *
 *  Created on: 29.05.2014
 *      Author: keks
 */

#ifndef KPMOVEMENTDETECTOR_HPP_
#define KPMOVEMENTDETECTOR_HPP_

//eclipse indexer fix
#include "indexer_fix.hpp"

//custom includes
#include "i_movement_detector.hpp"
#include "i_pose_detector.hpp"
#include "i_sequence_generator.hpp"
#include "kp_detector.hpp"

#include "bone.hpp"
#include "i_pose_listener.hpp"

//global includes
#include <memory>
#include <queue>
#include <iostream>

namespace mae
{

	template<typename T, typename U>
	class kp_movement_detector: public i_movement_detector<T, U>
	{
		public:
			/**
			 * Creates a new key pose movement detector. The detection relies on the key pose detector
			 * (kp_detector) of this package. The key pose movement detector invokes the pose and key
			 * pose detectors as well as the sequence generator given to this detector.
			 *
			 * @param ipd The pose detector to be used.
			 * @param isg The sequence generator to be used.
			 * @param debug True if debug information is intended to be provided on the terminal.
			 */
			kp_movement_detector(std::shared_ptr<i_pose_detector<T> > ipd,
					std::shared_ptr<i_sequence_generator<U> > isg, bool debug = false);

			/**
			 * Creates a new key pose movement detector. The detection relies on the key pose detector
			 * which is passed to this detector. The key pose movement detector invokes the pose and key
			 * pose detectors as well as the sequence generator given to this detector.
			 *
			 * @param ipd The pose detector to be used.
			 * @param isg The sequence generator to be used.
			 * @param ikpd The key pose detector to be used.
			 * @param debug True if debug information is intended to be provided on the terminal.
			 */
			kp_movement_detector(std::shared_ptr<i_pose_detector<T> > ipd,
					std::shared_ptr<i_sequence_generator<U> > isg, std::shared_ptr<i_kp_detector> ikpd, bool debug = false);
			virtual ~kp_movement_detector();

			/**
			 * Detects movement in the streamed skeleton sequence for the given body parts. Therefore, a buffer is used
			 * and the whole movement sequence for the buffer is returned. Invokes the pose and key pose detectors as well as the
			 * sequence generator given to this detector.
			 *
			 * @param timestamp The timestamp of the current frame as provided by the user. It is not save to rely on this value.
			 * @param framerate The framerate to be applied. The framerate does not change.
			 * @param skeleton The skeleton data.
			 * @param body_parts The addressed body parts.
			 * @return The detected movement sequence.
			 */
			virtual std::shared_ptr<U> detect_movement(long timestamp, double framerate, std::shared_ptr<T> skeleton, std::vector<bone> body_parts);

			/**
			 * Updates the buffer size.
			 *
			 * @param size The size.
			 */
			virtual void set_buffer(int size);

			/**
			 * Adds a pose listener to the detector. The listeners are invoked whenever a pose is fully detected (each frame).
			 *
			 * @param listener The listener to be added.
			 */
			virtual void add_listener(std::shared_ptr<i_pose_listener> listener);

			/**
			 * Removes the listener from the detector.
			 *
			 * @param listener The listener to be removed.
			 */
			virtual void remove_listener(std::shared_ptr<i_pose_listener> listener);

			/**
			 * Clears all listeners, which means removing them from the detector.
			 */
			virtual void clear_listeners();

			/**
			 * Notifies all listeners on the detection of a new pose.
			 *
			 * @param timestamp
			 * @param pose
			 */
			virtual void notify_listeners(long timestamp, std::shared_ptr<general_pose> pose);

		private:
			bool debug_;
			std::shared_ptr<i_pose_detector<T> > ipd;
			std::shared_ptr<i_sequence_generator<U> > isg;
			std::shared_ptr<i_kp_detector> ikpd;

			std::list<std::shared_ptr<i_pose_listener> > listeners_;
			int pose_buffer_size;
			std::list<std::shared_ptr<general_enriched_pose> > poses;

	};
} // namespace mae

//template implementation
namespace mae
{

	template<typename T, typename U>
	kp_movement_detector<T, U>::kp_movement_detector(std::shared_ptr<i_pose_detector<T> > ipd,
			std::shared_ptr<i_sequence_generator<U> > isg, bool debug)
	{
		this->debug_ = debug;
		this->ipd = ipd;
		this->isg = isg;
		this->ikpd = std::shared_ptr<i_kp_detector>(new kp_detector(debug));

		this->pose_buffer_size = 400;

	}

	template<typename T, typename U>
	kp_movement_detector<T, U>::kp_movement_detector(std::shared_ptr<i_pose_detector<T> > ipd,
			std::shared_ptr<i_sequence_generator<U> > isg, std::shared_ptr<i_kp_detector> ikpd, bool debug)
	{
		this->debug_ = debug;
		this->ipd = ipd;
		this->isg = isg;
		this->ikpd = ikpd;

		this->pose_buffer_size = 400;
	}

	template<typename T, typename U>
	kp_movement_detector<T, U>::~kp_movement_detector()
	{
		//clear the queue
		poses.clear();
	}

	template<typename T, typename U>
	std::shared_ptr<U> kp_movement_detector<T, U>::detect_movement(long timestamp, double framerate, std::shared_ptr<T> skeleton,
			std::vector<bone> body_parts)
	{
		if (debug_)
		{
			std::cout << "kp_movement_detector: detect movement" << std::endl;
		}

		std::shared_ptr<U> sequence;

		if (ipd)
		{
			std::shared_ptr<general_pose> pose = ipd->pose(skeleton, body_parts);

			notify_listeners(timestamp, pose);

			if (ikpd)
			{
				std::shared_ptr<general_enriched_pose> enriched_pose = ikpd->estimate_frame(pose, poses, body_parts);

				poses.push_front(enriched_pose);
				if (poses.size() > pose_buffer_size)
				{
					poses.pop_back();
				}

				if (isg)
				{
					sequence = isg->generate_sequence(framerate, poses, body_parts);
				}
			}
		}

		return sequence;
	}

	template<typename T, typename U>
	void kp_movement_detector<T, U>::set_buffer(int size)
	{
		pose_buffer_size = size;
	}

	template<typename T, typename U>
	void kp_movement_detector<T, U>::add_listener(std::shared_ptr<i_pose_listener> listener)
	{
		listeners_.push_back(listener);
	}

	template<typename T, typename U>
	void kp_movement_detector<T, U>::remove_listener(std::shared_ptr<i_pose_listener> listener)
	{
		for (std::list<std::shared_ptr<i_pose_listener> >::iterator it = listeners_.begin(); it != listeners_.end(); it++)
		{
			if (listener == *it)
			{
				listeners_.erase(it);
				break;
			}
		}
	}

	template<typename T, typename U>
	void kp_movement_detector<T, U>::clear_listeners()
	{
		listeners_.clear();
	}

	template<typename T, typename U>
	void kp_movement_detector<T, U>::notify_listeners(long timestamp, std::shared_ptr<general_pose> pose)
	{
		if (debug_ && listeners_.size() > 0)
		{
			std::cout << "kp_movement_detector: notify (pose) listeners" << std::endl;
		}

		for (std::list<std::shared_ptr<i_pose_listener> >::iterator it = listeners_.begin(); it != listeners_.end(); it++)
		{
			(*it)->on_pose(timestamp, pose);
		}
	}

} // namespace mae

#endif // KPMOVEMENTDETECTOR_HPP_
