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
					std::shared_ptr<i_sequence_generator<U> > isg, std::shared_ptr<i_kp_detector> ikpd, bool debug =
							false);
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
			virtual std::shared_ptr<U> detect_movement(uint64_t timestamp, double framerate, std::shared_ptr<T> skeleton,
					std::vector<bone> body_parts);

			/**
			 * Updates the buffer size.
			 *
			 * @param size The size.
			 */
			virtual void set_buffer(int size);

			/**
			 * Clears the buffer used to store the data.
			 */
			virtual void clear_buffer();

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
			virtual void notify_listeners(uint64_t timestamp, std::shared_ptr<general_pose> pose);

			/**
			 * Returns the last processed pose.
			 *
			 * @return The last processed pose.
			 */
			virtual std::shared_ptr<general_pose> get_current_pose() const;

			/**
			 * Returns the pose detector.
			 *
			 * @return The detector.
			 */
			virtual std::shared_ptr<i_pose_detector<T> > get_pose_detector() const;

			/**
			 * Returns the sequence generator.
			 *
			 * @return The generator.
			 */
			virtual std::shared_ptr<i_sequence_generator<U> > get_sequence_generator() const;

			/**
			 * Returns the key pose detector.
			 *
			 * @return The detector.
			 */
			virtual std::shared_ptr<i_kp_detector> get_kp_detector() const;

		private:
			bool debug_;
			std::shared_ptr<i_pose_detector<T> > ipd_;
			std::shared_ptr<i_sequence_generator<U> > isg_;
			std::shared_ptr<i_kp_detector> ikpd_;

			std::list<std::shared_ptr<i_pose_listener> > listeners_;
			int pose_buffer_size_;
			std::list<std::shared_ptr<general_enriched_pose> > poses_;
			std::shared_ptr<general_pose> previous_pose_;

	};
} // namespace mae

//template implementation
namespace mae
{

	template<typename T, typename U>
	kp_movement_detector<T, U>::kp_movement_detector(std::shared_ptr<i_pose_detector<T> > ipd,
			std::shared_ptr<i_sequence_generator<U> > isg, bool debug)
	{
		debug_ = debug;
		ipd_ = ipd;
		isg_ = isg;
		ikpd_ = std::shared_ptr<i_kp_detector>(new kp_detector(debug));

		pose_buffer_size_ = 400;
		previous_pose_ = nullptr;

	}

	template<typename T, typename U>
	kp_movement_detector<T, U>::kp_movement_detector(std::shared_ptr<i_pose_detector<T> > ipd,
			std::shared_ptr<i_sequence_generator<U> > isg, std::shared_ptr<i_kp_detector> ikpd, bool debug)
	{
		debug_ = debug;
		ipd_ = ipd;
		isg_ = isg;
		ikpd_ = ikpd;

		pose_buffer_size_ = 400;
		previous_pose_ = nullptr;
	}

	template<typename T, typename U>
	kp_movement_detector<T, U>::~kp_movement_detector()
	{
		//clear the queue
		poses_.clear();
	}

	template<typename T, typename U>
	std::shared_ptr<U> kp_movement_detector<T, U>::detect_movement(uint64_t timestamp, double framerate,
			std::shared_ptr<T> skeleton, std::vector<bone> body_parts)
	{
		if (debug_)
		{
			std::cout << "kp_movement_detector: detect movement" << std::endl;
		}

		std::shared_ptr<U> sequence;

		if (ipd_)
		{
			std::shared_ptr<general_pose> pose = ipd_->pose(framerate, skeleton, body_parts, previous_pose_);

			//update previous pose
			previous_pose_ = pose;

			//notify pose listeners
			notify_listeners(timestamp, pose);

			if (ikpd_)
			{
				std::shared_ptr<general_enriched_pose> enriched_pose = ikpd_->estimate_frame(framerate, pose, poses_, body_parts);

				poses_.push_front(enriched_pose);
				if (poses_.size() > pose_buffer_size_)
				{
					poses_.pop_back();
				}

				if (isg_)
				{
					sequence = isg_->generate_sequence(framerate, poses_, body_parts);
				}
			}
		}

		return sequence;
	}

	template<typename T, typename U>
	void kp_movement_detector<T, U>::set_buffer(int size)
	{
		pose_buffer_size_ = size;
	}

	template<typename T, typename U>
	void kp_movement_detector<T, U>::clear_buffer()
	{
		poses_.clear();
		previous_pose_ = nullptr;
	}

	template<typename T, typename U>
	void kp_movement_detector<T, U>::add_listener(std::shared_ptr<i_pose_listener> listener)
	{
		listeners_.push_back(listener);
	}

	template<typename T, typename U>
	void kp_movement_detector<T, U>::remove_listener(std::shared_ptr<i_pose_listener> listener)
	{
		for (std::list<std::shared_ptr<i_pose_listener> >::iterator it = listeners_.begin(); it != listeners_.end();
				it++)
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
	void kp_movement_detector<T, U>::notify_listeners(uint64_t timestamp, std::shared_ptr<general_pose> pose)
	{
		if (debug_ && listeners_.size() > 0)
		{
			std::cout << "kp_movement_detector: notify (pose) listeners" << std::endl;
		}

		for (std::list<std::shared_ptr<i_pose_listener> >::iterator it = listeners_.begin(); it != listeners_.end();
				it++)
		{
			if (*it != nullptr)
			{
				(*it)->on_pose(timestamp, pose);
			}
		}
	}

	template<typename T, typename U>
	std::shared_ptr<general_pose> kp_movement_detector<T, U>::get_current_pose() const
	{
		return previous_pose_;
	}

	template<typename T, typename U>
	std::shared_ptr<i_pose_detector<T> > kp_movement_detector<T, U>::get_pose_detector() const
	{
		return ipd_;
	}

	template<typename T, typename U>
	std::shared_ptr<i_sequence_generator<U> > kp_movement_detector<T, U>::get_sequence_generator() const
	{
		return isg_;
	}

	template<typename T, typename U>
	std::shared_ptr<i_kp_detector> kp_movement_detector<T, U>::get_kp_detector() const
	{
		return ikpd_;
	}

} // namespace mae

#endif // KPMOVEMENTDETECTOR_HPP_
