/*
 * MovementController.cpp
 *
 *  Created on: 15.05.2014
 *      Author: keks
 */

#include "MovementController.hpp"

namespace mae{
	namespace controller {


		template <typename T, typename U>
		MovementController<T, U>::MovementController(std::shared_ptr<IMovementDetector<T,U> > imd, std::vector<int> bodyParts)
		{
			this->imd = imd;
			this->bodyParts = bodyParts;
		}


		template <typename T, typename U>
		MovementController<T, U>::MovementController(std::shared_ptr<IPoseDetector<T> > ipd, std::shared_ptr<ISequenceGenerator<U> > isg, std::vector<int> bodyParts)
		{
			std::shared_ptr<KPMovementDetector<T,U> > imd_n(new KPMovementDetector<T,U>(ipd, isg));
			this->imd = imd_n;
			this->bodyParts = bodyParts;
		}


		template <typename T, typename U>
		MovementController<T, U>::~MovementController() {
			// TODO dtor
		}
		
		template <typename T, typename U>
		void MovementController<T, U>::nextFrame(long timestamp,std::shared_ptr<T> skeleton){
			
			//TODO check for null pointers??
			if (imd != nullptr)
			{
				std::shared_ptr<U> sequence = imd->detectMovement(skeleton, bodyParts);
			}
			else
			{
				std::cerr << "imd nullpointer" << std::endl;
			}

			//TODO do stuff with the sequence
		}

	} //namespace controller
} // namespace mae
