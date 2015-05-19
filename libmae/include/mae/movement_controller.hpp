/*
 * MovementController.hpp
 *
 *  Created on: 15.05.2014
 *      Author: keks
 */

#ifndef MOVEMENTCONTROLLER_HPP_
#define MOVEMENTCONTROLLER_HPP_

//eclipse indexer fix
#include "indexer_fix.hpp"

//custom includes
#include "kp_movement_detector.hpp"
#include "i_pose_detector.hpp"
#include "i_sequence_generator.hpp"
#include "i_sequence_recognizer.hpp"
#include "bone.hpp"

#include "i_sequence_listener.hpp"
#include "i_pose_listener.hpp"
#include "i_recognition_listener.hpp"

//global includes
#include <vector>
#include <iostream>
#include <memory>
#include <cstdint>

namespace mae
{

	template<typename T, typename U>
	class movement_controller
	{
		public:

			/**
			 * Creates a new movement controller with controllers for the steps of the processing chain.
			 *
			 * @param imd The movement detector to detect sequences.
			 * @param isr The sequence recognizer to recognize sequences.
			 * @param body_parts The addressed body parts.
			 * @param pose_buffer_size The initial pose buffer size.
			 * @param framerate The framerate of the skeleton stream.
			 * @param debug True for debug output on the terminal.
			 */
			movement_controller(std::shared_ptr<i_movement_detector<T, U> > imd,
					std::shared_ptr<i_sequence_recognizer<U> > isr, std::vector<bone> body_parts, int pose_buffer_size =
							0, double framerate = 1.0 / 30.0, bool debug = false);

			/**
			 * Creates a new movement controller with controllers for the steps of the processing chain.
			 * The movement detector is built from the pose detector and the sequence generator. A key
			 * pose approach is used to do this.
			 *
			 * @param ipd The pose detector to detect poses from the stream.
			 * @param isg The sequence generator to generate sequences out of pose sequences.
			 * @param isr The sequence recognizer to recognize sequences.
			 * @param body_parts The addressed body parts.
			 * @param pose_buffer_size The initial pose buffer size.
			 * @param framerate The framerate of the skeleton stream.
			 * @param debug True for debug output on the terminal.
			 */
			movement_controller(std::shared_ptr<i_pose_detector<T> > ipd, std::shared_ptr<i_sequence_generator<U> > isg,
					std::shared_ptr<i_sequence_recognizer<U> > isr, std::vector<bone> body_parts, int pose_buffer_size =
							0, double framerate = 1.0 / 30.0, bool debug = false);
			virtual ~movement_controller();

			/**
			 * Processes the next frame.
			 *
			 * @param timestamp The timestamp for the skeleton.
			 * @param skeleton The skeleton.
			 */
			virtual void next_frame(uint64_t timestamp, std::shared_ptr<T> skeleton);

			/**
			 * Registers a sequence to the controller in order to be recognized from the stream.
			 *
			 * @param sequence The sequence.
			 */
			virtual void register_sequence(std::shared_ptr<U> sequence);

			/**
			 * Removes the registered sequence from the controller.
			 *
			 * @param sequence The sequence.
			 */
			virtual void deregister_sequence(std::shared_ptr<U> sequence);

			/**
			 * Removes all registered sequences from the controller.
			 */
			virtual void clear_registered_sequences();

			/**
			 * Disables or enables buffer size updates on newly registered sequences.
			 *
			 * @param updates True for automatic updates of the buffer size.
			 */
			virtual void set_no_buffer_size_update(bool updates);

			/**
			 * Sets the framerate to be applied.
			 *
			 * @param framerate The framerate
			 */
			virtual void set_framerate(double framerate);

			/**
			 * Returns the currently applied framerate.
			 *
			 * @return The framerate.
			 */
			virtual double get_framerate() const;

			/**
			 * Clears the buffer of currently present movements.
			 */
			virtual void clear_buffer();

			/**
			 * Returns the currently generated sequence from the skeleton stream.
			 *
			 * @return The sequence.
			 */
			virtual std::shared_ptr<U> get_current_sequence() const;

			/**
			 * Returns the last processed pose.
			 *
			 * @return The last processed pose.
			 */
			virtual std::shared_ptr<general_pose> get_current_pose() const;

			/**
			 * Returns the currently recognized sequences.
			 *
			 * @return The sequences.
			 */
			virtual std::vector<std::shared_ptr<U> > get_current_recognition() const;

			/**
			 * Adds a pose listener to the movement controller. The pose listener is invoked whenever a
			 * pose was quantized (which is on every frame).
			 *
			 * @param pose_listener The listener
			 */
			virtual void add_listener(std::shared_ptr<i_pose_listener> pose_listener);

			/**
			 * Removes the pose listener from the controller.
			 *
			 * @param pose_listener The listener.
			 */
			virtual void remove_listener(std::shared_ptr<i_pose_listener> pose_listener);

			/**
			 * Adds a sequence listener to the movement controller. The sequence listener is invoked whenever a
			 * sequence was generated (which is on every frame).
			 *
			 * @param sequence_listener The listener
			 */
			virtual void add_listener(std::shared_ptr<i_sequence_listener<U> > sequence_listener);

			/**
			 * Removes the sequence listener from the controller.
			 *
			 * @param sequence_listener The listener
			 */
			virtual void remove_listener(std::shared_ptr<i_sequence_listener<U> > sequence_listener);

			/**
			 * Adds a recognition listener to the controller. The recognition listener is invoked whenever a
			 * sequence was recognized.
			 *
			 * @param recognition_listener The listener.
			 */
			virtual void add_listener(std::shared_ptr<i_recognition_listener<U> > recognition_listener);

			/**
			 * Removes the recognition listener from the controller.
			 *
			 * @param sequence_listener The listener
			 */
			virtual void remove_listener(std::shared_ptr<i_recognition_listener<U> > recognition_listener);

			/**
			 * Removes all listeners from the controller.
			 */
			virtual void clear_listeners();

			/**
			 * Notifies the sequence listeners on a newly generated sequence.
			 *
			 * @param timestamp The timestamp.
			 * @param sequence The sequence.
			 */
			virtual void notify_sequence_listeners(uint64_t timestamp, std::shared_ptr<U> sequence);

			/**
			 * Notifies the recognition listeners on recognized sequences.
			 *
			 * @param timestamp The timestamp.
			 * @param sequences The recognized sequences.
			 */
			virtual void notify_recognition_listeners(uint64_t timestamp, std::vector<std::shared_ptr<U> > sequences);

			/**
			 * Returns the movement detector which is registered to this controller.
			 *
			 * @return The movement detector.
			 */
			virtual std::shared_ptr<i_movement_detector<T, U> > get_movement_detector();

			/**
			 * Returns the sequence recognizer which is registered to this controller.
			 *
			 * @return The sequence recognizer.
			 */
			virtual std::shared_ptr<i_sequence_recognizer<U> > get_sequence_recognizer();

		private:
			bool debug_;
			double framerate_;
			int buffer_size_;
			bool no_buffer_size_update_;
			std::vector<bone> body_parts_;

			std::shared_ptr<U> current_sequence_;
			std::vector<std::shared_ptr<U> > current_recognition_;

			std::shared_ptr<i_movement_detector<T, U> > imd_;
			std::shared_ptr<i_sequence_recognizer<U> > isr_;

			//listeners
			std::list<std::shared_ptr<i_sequence_listener<U> > > sequence_listeners_;
			std::list<std::shared_ptr<i_recognition_listener<U> > > recognition_listeners_;

	};

} // namespace mae

//----------
//template implementation
//----------

namespace mae
{

	template<typename T, typename U>
	movement_controller<T, U>::movement_controller(std::shared_ptr<i_movement_detector<T, U> > imd,
			std::shared_ptr<i_sequence_recognizer<U> > isr, std::vector<bone> body_parts, int pose_buffer_size,
			double framerate, bool debug)
	{
		this->debug_ = debug;
		this->framerate_ = framerate;
		this->body_parts_ = body_parts;
		buffer_size_ = pose_buffer_size;
		no_buffer_size_update_ = false;

		this->imd_ = imd;
		this->isr_ = isr;

		if (buffer_size_ > 1 && imd_ != nullptr)
		{
			imd_->set_buffer(buffer_size_);
		}
	}

	template<typename T, typename U>
	movement_controller<T, U>::movement_controller(std::shared_ptr<i_pose_detector<T> > ipd,
			std::shared_ptr<i_sequence_generator<U> > isg, std::shared_ptr<i_sequence_recognizer<U> > isr,
			std::vector<bone> body_parts, int pose_buffer_size, double framerate, bool debug)
	{
		if (debug)
		{
			std::cout << "creating movement controller." << std::endl;
		}

		debug_ = debug;
		framerate_ = framerate;
		body_parts_ = body_parts;
		buffer_size_ = pose_buffer_size;
		no_buffer_size_update_ = false;

		std::shared_ptr<kp_movement_detector<T, U> > imd_n(new kp_movement_detector<T, U>(ipd, isg, debug));
		this->imd_ = imd_n;
		this->isr_ = isr;

		if (buffer_size_ > 1 && imd_ != nullptr)
		{
			imd_->set_buffer(buffer_size_);
		}

	}

	template<typename T, typename U>
	movement_controller<T, U>::~movement_controller()
	{
	}

	template<typename T, typename U>
	void movement_controller<T, U>::next_frame(uint64_t timestamp, std::shared_ptr<T> skeleton)
	{
		if (debug_)
		{
			std::cout << "movement_controller: next frame" << std::endl;
		}

		if (imd_)
		{
			std::shared_ptr<U> sequence = imd_->detect_movement(timestamp, framerate_, skeleton, body_parts_);
			current_sequence_ = sequence;
			notify_sequence_listeners(timestamp, sequence);

			if (isr_ != nullptr)
			{
				current_recognition_ = isr_->recognize_sequence(framerate_, sequence, body_parts_);

				if (current_recognition_.size() > 0)
				{
					notify_recognition_listeners(timestamp, current_recognition_);
				}
			}
			else
			{
				throw std::invalid_argument("No sequence recognizer defined in the movement controller.");
			}
		}
		else
		{
			throw std::invalid_argument("No movement detector defined in the movement controller.");
		}
	}

	template<typename T, typename U>
	std::shared_ptr<i_movement_detector<T, U> > movement_controller<T, U>::get_movement_detector()
	{
		return imd_;
	}

	template<typename T, typename U>
	std::shared_ptr<i_sequence_recognizer<U> > movement_controller<T, U>::get_sequence_recognizer()
	{
		return isr_;
	}

	template<typename T, typename U>
	void movement_controller<T, U>::register_sequence(std::shared_ptr<U> sequence)
	{
		if (isr_ != nullptr)
		{
			isr_->register_sequence(sequence);

			//update buffer size if sequence length is longer than current buffer size
			int tmp_buffer_size = std::ceil(isr_->get_sequence_length(sequence) / (framerate_ * 1000.0));

			if (imd_ != nullptr && buffer_size_ < tmp_buffer_size && !no_buffer_size_update_)
			{
				buffer_size_ = tmp_buffer_size;
				imd_->set_buffer(buffer_size_);
			}
		}
		else
		{
			throw std::invalid_argument("No sequence recognizer defined in the movement controller.");
		}
	}

	template<typename T, typename U>
	void movement_controller<T, U>::deregister_sequence(std::shared_ptr<U> sequence)
	{
		if (isr_ != nullptr)
		{
			isr_->deregister_sequence(sequence);
		}
		else
		{
			throw std::invalid_argument("No sequence recognizer defined in the movement controller.");
		}
	}

	template<typename T, typename U>
	void movement_controller<T, U>::clear_registered_sequences()
	{
		if (isr_ != nullptr)
		{
			isr_->clear_registered_sequences();
		}
		else
		{
			throw std::invalid_argument("No sequence recognizer defined in the movement controller.");
		}
	}

	template<typename T, typename U>
	void movement_controller<T, U>::set_no_buffer_size_update(bool updates)
	{
		no_buffer_size_update_ = updates;
	}

	template<typename T, typename U>
	void movement_controller<T, U>::clear_buffer()
	{
		current_sequence_ = nullptr;

		if (imd_ != nullptr)
		{
			imd_->clear_buffer();
		}

		if (isr_ != nullptr)
		{
			isr_->clear_buffer();
		}
	}

	template<typename T, typename U>
	std::shared_ptr<U> movement_controller<T, U>::get_current_sequence() const
	{
		return current_sequence_;
	}

	template<typename T, typename U>
	std::shared_ptr<general_pose> movement_controller<T, U>::get_current_pose() const
	{
		if (imd_ != nullptr)
		{
			return imd_->get_current_pose();
		}
		else
		{
			return nullptr;
		}
	}

	template<typename T, typename U>
	std::vector<std::shared_ptr<U> > movement_controller<T, U>::get_current_recognition() const
	{
		return current_recognition_;
	}

	template<typename T, typename U>
	void movement_controller<T, U>::set_framerate(double framerate)
	{
		framerate_ = framerate;
	}

	template<typename T, typename U>
	double movement_controller<T, U>::get_framerate() const
	{
		return framerate_;
	}

	template<typename T, typename U>
	void movement_controller<T, U>::add_listener(std::shared_ptr<i_pose_listener> pose_listener)
	{
		imd_->add_listener(pose_listener);
	}

	template<typename T, typename U>
	void movement_controller<T, U>::remove_listener(std::shared_ptr<i_pose_listener> pose_listener)
	{
		imd_->remove_listener(pose_listener);
	}

	template<typename T, typename U>
	void movement_controller<T, U>::add_listener(std::shared_ptr<i_sequence_listener<U> > sequence_listener)
	{
		sequence_listeners_.push_back(sequence_listener);
	}

	template<typename T, typename U>
	void movement_controller<T, U>::remove_listener(std::shared_ptr<i_sequence_listener<U> > sequence_listener)
	{
		for (typename std::list<std::shared_ptr<i_sequence_listener<U>>>::iterator it = sequence_listeners_.begin(); it != sequence_listeners_.end(); it++)
		{
			if (sequence_listener == *it)
			{
				sequence_listeners_.erase(it);
				break;
			}
		}
	}

	template<typename T, typename U>
	void movement_controller<T, U>::add_listener(std::shared_ptr<i_recognition_listener<U> > recognition_listener)
	{
		recognition_listeners_.push_back(recognition_listener);
	}

	template<typename T, typename U>
	void movement_controller<T, U>::remove_listener(std::shared_ptr<i_recognition_listener<U> > recognition_listener)
	{
		for (typename std::list<std::shared_ptr<i_recognition_listener<U>>>::iterator it = recognition_listeners_.begin(); it != recognition_listeners_.end(); it++)
		{
			if (recognition_listener == *it)
			{
				recognition_listeners_.erase(it);
				break;
			}
		}
	}

	template<typename T, typename U>
	void movement_controller<T, U>::clear_listeners()
	{
		sequence_listeners_.clear();

		imd_->clear_listeners();
	}

	template<typename T, typename U>
	void movement_controller<T, U>::notify_sequence_listeners(uint64_t timestamp, std::shared_ptr<U> sequence)
	{
		if (debug_ && sequence_listeners_.size() > 0)
		{
			std::cout << "movement_controller: notify (sequence) listeners" << std::endl;
		}

		for (typename std::list<std::shared_ptr<i_sequence_listener<U> > >::iterator it = sequence_listeners_.begin();
				it != sequence_listeners_.end(); it++)
		{
			(*it)->on_sequence(timestamp, sequence);
		}
	}

	template<typename T, typename U>
	void movement_controller<T, U>::notify_recognition_listeners(uint64_t timestamp,
			std::vector<std::shared_ptr<U> > sequences)
	{
		if (debug_ && recognition_listeners_.size() > 0)
		{
			std::cout << "movement_controller: notify (recognition) listeners" << std::endl;
		}

		for (typename std::list<std::shared_ptr<i_recognition_listener<U> > >::iterator it =
				recognition_listeners_.begin(); it != recognition_listeners_.end(); it++)
		{
			(*it)->on_recognition(timestamp, sequences);
		}
	}

} // namespace mae

#endif // MOVEMENTCONTROLLER_HPP_
