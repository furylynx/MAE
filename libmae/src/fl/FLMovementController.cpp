/*
 * FLMovementController.cpp
 *
 *  Created on: 29.05.2014
 *      Author: keks
 */

#include "FLMovementController.hpp"

namespace mae {
	namespace fl {

		FLMovementController::FLMovementController() : MovementController(std::shared_ptr<FLPoseDetector>(new FLPoseDetector()),std::shared_ptr<FLLabanSequenceGenerator>(new FLLabanSequenceGenerator()), get_flj_ids())
		{
			this->skel_ctrl = std::shared_ptr<FLSkeletonController>(new FLSkeletonController);
		}

		FLMovementController::FLMovementController(std::vector<int> bodyParts) : MovementController(std::shared_ptr<FLPoseDetector>(new FLPoseDetector()),std::shared_ptr<FLLabanSequenceGenerator>(new FLLabanSequenceGenerator()), bodyParts)
		{
			this->skel_ctrl = std::shared_ptr<FLSkeletonController>(new FLSkeletonController);
		}


		FLMovementController::~FLMovementController()
		{
		}


		void FLMovementController::nextFrame(long timestamp,std::shared_ptr<mae::model::GeneralSkeleton> skeleton){
			std::shared_ptr<FLSkeleton> fl_skel = skel_ctrl->calculateSpecifiedSkeleton(skeleton);
			mae::controller::MovementController<FLSkeleton, FLLabanSequence>::nextFrame(timestamp, fl_skel);
		}

	} // namespace fl
} // namespace mae
