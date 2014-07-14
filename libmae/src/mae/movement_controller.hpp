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

#include "pose_listener.hpp"
#include "bone.hpp"

//global includes
#include <vector>
#include <iostream>
#include <memory>
#include <chrono>

namespace mae{

		template <typename T, typename U>
		class movement_controller {
			public:

				movement_controller(std::shared_ptr<i_movement_detector<T,U> > imd, std::vector<bone> body_parts, bool debug = false);
				movement_controller(std::shared_ptr<i_pose_detector<T> > ipd, std::shared_ptr<i_sequence_generator<U> > isg, std::vector<bone> body_parts, bool debug = false);
				virtual ~movement_controller();

				//todo other methods in here
				virtual void next_frame(long timestamp, std::shared_ptr<T> skeleton);

				//todo more listener stuff
				virtual void add_listener(std::shared_ptr<pose_listener> pose_listener);
				virtual void remove_listener(std::shared_ptr<pose_listener> pose_listener);
				virtual void clear_listeners();

			private:
				bool debug_;
				std::shared_ptr<i_movement_detector<T,U> > imd;
				std::vector<bone> body_parts;



		};

} // namespace mae





//----------
//template implementation
//----------

namespace mae{

		template <typename T, typename U>
		movement_controller<T, U>::movement_controller(std::shared_ptr<i_movement_detector<T,U> > imd, std::vector<bone> body_parts, bool debug)
		{
			this->debug_ = debug;
			this->imd = imd;
			this->body_parts = body_parts;
		}

		template <typename T, typename U>
		movement_controller<T, U>::movement_controller(std::shared_ptr<i_pose_detector<T> > ipd, std::shared_ptr<i_sequence_generator<U> > isg, std::vector<bone> body_parts, bool debug)
		{
			this->debug_ = debug;
			std::shared_ptr<kp_movement_detector<T,U> > imd_n(new kp_movement_detector<T,U>(ipd, isg, debug));
			this->imd = imd_n;
			this->body_parts = body_parts;
		}

		template <typename T, typename U>
		movement_controller<T, U>::~movement_controller() {
		}

		template <typename T, typename U>
		void movement_controller<T, U>::next_frame(long timestamp,std::shared_ptr<T> skeleton)
		{
			if (debug_)
			{
				std::cout << "movement_controller: next frame" << std::endl;
			}

			if (imd)
			{
				std::shared_ptr<U> sequence = imd->detect_movement(timestamp, skeleton, body_parts);
			}
			else
			{
				throw std::invalid_argument("No movement detector defined in the movement controller.");
			}

			//TODO do stuff with the sequence
		}

		template <typename T, typename U>
		void movement_controller<T, U>::add_listener(std::shared_ptr<pose_listener> pose_listener)
		{
			imd->add_listener(pose_listener);
		}

		template <typename T, typename U>
		void movement_controller<T, U>::remove_listener(std::shared_ptr<pose_listener> pose_listener)
		{
			imd->remove_listener(pose_listener);
		}

		template <typename T, typename U>
		void movement_controller<T, U>::clear_listeners()
		{
			imd->clear_listeners();
		}

} // namespace mae


#endif // MOVEMENTCONTROLLER_HPP_
