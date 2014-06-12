/*
 * KPMovementDetector.cpp
 *
 *  Created on: 29.05.2014
 *      Author: keks
 */

#include "KPMovementDetector.hpp"

namespace mae {
	namespace controller {

		template<typename T, typename U>
		KPMovementDetector<T, U>::KPMovementDetector(std::shared_ptr<IPoseDetector<T> > ipd, std::shared_ptr<ISequenceGenerator<U> > isg) {
			this->ipd = ipd;
			this->isg = isg;

			this->ikpd = std::shared_ptr<IKeyPoseDetector>(new GeneralKeyPoseDetector());

			this->pose_buffer_size = 20;

		}

		template<typename T, typename U>
		KPMovementDetector<T, U>::KPMovementDetector(std::shared_ptr<IPoseDetector<T> > ipd, std::shared_ptr<ISequenceGenerator<U> > isg, std::shared_ptr<IKeyPoseDetector> ikpd){
			this->ipd = ipd;
			this->isg = isg;
			this->ikpd = ikpd;

			this->pose_buffer_size = 20;
		}


		template<typename T, typename U>
		KPMovementDetector<T, U>::~KPMovementDetector() {
			//clear the queue
			std::queue<std::shared_ptr<mae::model::GeneralEnrichedPose> >().swap(queue);
		}


		template<typename T, typename U>
		std::shared_ptr<U> KPMovementDetector<T, U>::detectMovement(std::shared_ptr<T> skeleton, std::vector<int> bodyParts){
			std::shared_ptr<mae::model::GeneralPose> pose = ipd->pose(skeleton, bodyParts);

			std::shared_ptr<mae::model::GeneralEnrichedPose> enriched_pose = ikpd->estimateFrame(pose, queue, bodyParts);

			queue.push(enriched_pose);
			if (queue.size() > pose_buffer_size)
			{
				queue.pop();
			}

			std::shared_ptr<U> sequence = isg->generateSequence(queue, bodyParts);

			return sequence;
		}


		template<typename T, typename U>
		void KPMovementDetector<T, U>::setPoseBufferSize(int size){
			pose_buffer_size = size;
		}


	} // namespace controller
} // namespace mae
