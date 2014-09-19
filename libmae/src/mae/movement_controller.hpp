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
#include <chrono>

namespace mae{

		template <typename T, typename U>
		class movement_controller {
			public:

				movement_controller(std::shared_ptr<i_movement_detector<T,U> > imd, std::shared_ptr<i_sequence_recognizer<U> > isr,  std::vector<bone> body_parts, int pose_buffer_size = 0, double framerate = 1.0/30.0, bool debug = false);
				movement_controller(std::shared_ptr<i_pose_detector<T> > ipd, std::shared_ptr<i_sequence_generator<U> > isg, std::shared_ptr<i_sequence_recognizer<U> > isr, std::vector<bone> body_parts, int pose_buffer_size = 0, double framerate = 1.0/30.0, bool debug = false);
				virtual ~movement_controller();

				/**
				 * Processes the next frame.
				 *
				 * @param timestamp The timestamp for the skeleton.
				 * @param skeleton The skeleton.
				 */
				virtual void next_frame(long timestamp, std::shared_ptr<T> skeleton);

				virtual void register_sequence(std::shared_ptr<U> sequence);
				virtual void deregister_sequence(std::shared_ptr<U> sequence);
				virtual void clear_registered_sequences();

				//buffer size
				virtual void  set_no_buffer_size_update(bool updates);

				//listeners
				virtual void add_listener(std::shared_ptr<i_pose_listener> pose_listener);
				virtual void remove_listener(std::shared_ptr<i_pose_listener> pose_listener);

				virtual void add_listener(std::shared_ptr<i_sequence_listener<U> > sequence_listener);
				virtual void remove_listener(std::shared_ptr<i_sequence_listener<U> >  sequence_listener);

				virtual void add_listener(std::shared_ptr<i_recognition_listener<U> > recognition_listener);
				virtual void remove_listener(std::shared_ptr<i_recognition_listener<U> >  recognition_listener);

				virtual void clear_listeners();

				virtual void notify_sequence_listeners(long timestamp, std::shared_ptr<U> sequence);

				virtual void notify_recognition_listeners(long timestamp, std::vector<std::shared_ptr<U> > sequences);

				//todo event listener stuff

			protected:
				virtual std::shared_ptr<i_movement_detector<T,U> > get_movement_detector();

			private:
				bool debug_;
				double framerate_;
				int buffer_size_;
				bool no_buffer_size_update_;
				std::vector<bone> body_parts_;

				std::shared_ptr<i_movement_detector<T,U> > imd_;
				std::shared_ptr<i_sequence_recognizer<U> > isr_;

				//listeners
				std::list<std::shared_ptr<i_sequence_listener<U> > > sequence_listeners_;
				std::list<std::shared_ptr<i_recognition_listener<U> > > recognition_listeners_;

		};

} // namespace mae





//----------
//template implementation
//----------

namespace mae{

		template <typename T, typename U>
		movement_controller<T, U>::movement_controller(std::shared_ptr<i_movement_detector<T,U> > imd, std::shared_ptr<i_sequence_recognizer<U> > isr, std::vector<bone> body_parts, int pose_buffer_size, double framerate, bool debug)
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

		template <typename T, typename U>
		movement_controller<T, U>::movement_controller(std::shared_ptr<i_pose_detector<T> > ipd, std::shared_ptr<i_sequence_generator<U> > isg, std::shared_ptr<i_sequence_recognizer<U> > isr, std::vector<bone> body_parts, int pose_buffer_size, double framerate, bool debug)
		{
			this->debug_ = debug;
			this->framerate_ = framerate;
			this->body_parts_ = body_parts;
			buffer_size_ = pose_buffer_size;
			no_buffer_size_update_ = false;

			std::shared_ptr<kp_movement_detector<T,U> > imd_n(new kp_movement_detector<T,U>(ipd, isg, debug));
			this->imd_ = imd_n;
			this->isr_ = isr;

			if (buffer_size_ > 1 && imd_ != nullptr)
			{
				imd_->set_buffer(buffer_size_);
			}

		}

		template <typename T, typename U>
		movement_controller<T, U>::~movement_controller()
		{
		}

		template <typename T, typename U>
		void movement_controller<T, U>::next_frame(long timestamp,std::shared_ptr<T> skeleton)
		{
			if (debug_)
			{
				std::cout << "movement_controller: next frame" << std::endl;
			}

			if (imd_)
			{
				std::shared_ptr<U> sequence = imd_->detect_movement(timestamp, framerate_, skeleton, body_parts_);
				notify_sequence_listeners(timestamp, sequence);

				if (isr_ != nullptr)
				{
					std::vector<std::shared_ptr<U> > recognized = isr_->recognize_sequence(sequence, body_parts_);

					if (recognized.size() > 0)
					{
						notify_recognition_listeners(timestamp, recognized);
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

		template <typename T, typename U>
		std::shared_ptr<i_movement_detector<T,U> >  movement_controller<T, U>::get_movement_detector()
		{
			return imd_;
		}

		template <typename T, typename U>
		void movement_controller<T, U>::register_sequence(std::shared_ptr<U> sequence)
		{
			if (isr_ != nullptr)
			{
				isr_->register_sequence(sequence);

				//update buffer size if sequence length is longer than current buffer size
				int tmp_buffer_size = std::ceil(isr_->get_sequence_length(sequence)/(framerate_ * 1000.0));

				if (imd_ != nullptr && buffer_size_ < tmp_buffer_size && !no_buffer_size_update_)
				{
					std::cout << "actually setting the new buffer size: " << tmp_buffer_size << std::endl;

					buffer_size_ = tmp_buffer_size;
					imd_->set_buffer(buffer_size_);
				}
			}
			else
			{
				throw std::invalid_argument("No sequence recognizer defined in the movement controller.");
			}
		}

		template <typename T, typename U>
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

		template <typename T, typename U>
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

		template <typename T, typename U>
		void movement_controller<T, U>::set_no_buffer_size_update(bool updates)
		{
			no_buffer_size_update_ = updates;
		}

		template <typename T, typename U>
		void movement_controller<T, U>::add_listener(std::shared_ptr<i_pose_listener> pose_listener)
		{
			imd_->add_listener(pose_listener);
		}

		template <typename T, typename U>
		void movement_controller<T, U>::remove_listener(std::shared_ptr<i_pose_listener> pose_listener)
		{
			imd_->remove_listener(pose_listener);
		}

		template <typename T, typename U>
		void movement_controller<T, U>::add_listener(std::shared_ptr<i_sequence_listener<U> > sequence_listener)
		{
			sequence_listeners_.push_back(sequence_listener);
		}

		template <typename T, typename U>
		void movement_controller<T, U>::remove_listener(std::shared_ptr<i_sequence_listener<U> >  sequence_listener)
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

		template <typename T, typename U>
		void movement_controller<T, U>::add_listener(std::shared_ptr<i_recognition_listener<U> > recognition_listener)
		{
			recognition_listeners_.push_back(recognition_listener);
		}

		template <typename T, typename U>
		void movement_controller<T, U>::remove_listener(std::shared_ptr<i_recognition_listener<U> >  recognition_listener)
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

		template <typename T, typename U>
		void movement_controller<T, U>::clear_listeners()
		{
			sequence_listeners_.clear();

			imd_->clear_listeners();
		}

		template <typename T, typename U>
		void movement_controller<T, U>::notify_sequence_listeners(long timestamp, std::shared_ptr<U> sequence)
		{
			if (debug_ && sequence_listeners_.size() > 0)
			{
				std::cout << "movement_controller: notify (sequence) listeners" << std::endl;
			}

			for (typename std::list<std::shared_ptr<i_sequence_listener<U> > >::iterator it = sequence_listeners_.begin(); it != sequence_listeners_.end(); it++)
			{
				(*it)->on_sequence(timestamp, sequence);
			}
		}

		template <typename T, typename U>
		void movement_controller<T, U>::notify_recognition_listeners(long timestamp, std::vector<std::shared_ptr<U> > sequences)
		{
			if (debug_ && recognition_listeners_.size() > 0)
			{
				std::cout << "movement_controller: notify (recognition) listeners" << std::endl;
			}

			for (typename std::list<std::shared_ptr<i_recognition_listener<U> > >::iterator it = recognition_listeners_.begin(); it != recognition_listeners_.end(); it++)
			{
				(*it)->on_recognition(timestamp, sequences);
			}
		}

} // namespace mae


#endif // MOVEMENTCONTROLLER_HPP_
