/*
 * FLMovementController.hpp
 *
 *  Created on: 29.05.2014
 *      Author: keks
 */

#ifndef FLMOVEMENTCONTROLLER_HPP_
#define FLMOVEMENTCONTROLLER_HPP_

//custom includes
#include "../model/GeneralSkeleton.hpp"
#include "../controller/MovementController.hpp"
#include "../controller/IPoseDetector.hpp"
#include "FLSkeleton.hpp"
#include "FLLabanSequence.hpp"
#include "FLPoseDetector.hpp"
#include "FLLabanSequenceGenerator.hpp"
#include "FLSkeletonController.hpp"
#include "FLJ.hpp"

//global includes
#include <iostream>


namespace mae {
	namespace fl {

		class FLMovementController : mae::controller::MovementController<mae::fl::FLSkeleton, mae::fl::FLLabanSequence>{
			public:
				FLMovementController();
				FLMovementController(std::vector<int> bodyParts);
				virtual ~FLMovementController();

				virtual void nextFrame(long timestamp,std::shared_ptr<mae::model::GeneralSkeleton> skeleton);

			private:
				std::shared_ptr<FLSkeletonController> skel_ctrl;

		};

	} // namespace fl
} // namespace mae

#endif // FLMOVEMENTCONTROLLER_HPP_
