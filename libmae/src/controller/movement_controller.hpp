/*
 * MovementController.hpp
 *
 *  Created on: 15.05.2014
 *      Author: keks
 */

#ifndef MOVEMENTCONTROLLER_HPP_
#define MOVEMENTCONTROLLER_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "kp_movement_detector.hpp"
#include "i_pose_detector.hpp"
#include "i_sequence_generator.hpp"

//global includes
#include <vector>
#include <memory>
#include <chrono>

namespace mae{

		template <typename T, typename U>
		class movement_controller {
			public:

				movement_controller(std::shared_ptr<i_movement_detector<T,U> > imd, std::vector<int> body_parts);
				movement_controller(std::shared_ptr<i_pose_detector<T> > ipd, std::shared_ptr<i_sequence_generator<U> > isg, std::vector<int> body_parts);
				virtual ~movement_controller();

				//todo other methods in here
				virtual void next_frame(long timestamp,std::shared_ptr<T> skeleton);

				//todo listener stuff

			private:
				std::shared_ptr<i_movement_detector<T,U> > imd;
				std::vector<int> body_parts;

		};

} // namespace mae





//----------
//template implementation
//----------

namespace mae{

		template <typename T, typename U>
		movement_controller<T, U>::movement_controller(std::shared_ptr<i_movement_detector<T,U> > imd, std::vector<int> body_parts)
		{
			this->imd = imd;
			this->body_parts = body_parts;
		}


		template <typename T, typename U>
		movement_controller<T, U>::movement_controller(std::shared_ptr<i_pose_detector<T> > ipd, std::shared_ptr<i_sequence_generator<U> > isg, std::vector<int> body_parts)
		{
			std::shared_ptr<kp_movement_detector<T,U> > imd_n(new kp_movement_detector<T,U>(ipd, isg));
			this->imd = imd_n;
			this->body_parts = body_parts;
		}


		template <typename T, typename U>
		movement_controller<T, U>::~movement_controller() {
			// TODO dtor
		}

		template <typename T, typename U>
		void movement_controller<T, U>::next_frame(long timestamp,std::shared_ptr<T> skeleton){

			//TODO check for null pointers??
			if (imd != nullptr)
			{
				std::shared_ptr<U> sequence = imd->detect_movement(skeleton, body_parts);
			}
			else
			{
				std::cerr << "imd nullpointer" << std::endl;
			}

			//TODO do stuff with the sequence
		}

} // namespace mae


#endif // MOVEMENTCONTROLLER_HPP_
