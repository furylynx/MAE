/*
 * KPMovementDetector.hpp
 *
 *  Created on: 29.05.2014
 *      Author: keks
 */

#ifndef KPMOVEMENTDETECTOR_HPP_
#define KPMOVEMENTDETECTOR_HPP_

//custom includes
#include "IMovementDetector.hpp"
#include "IPoseDetector.hpp"
#include "ISequenceGenerator.hpp"
#include "IKeyPoseDetector.hpp"

#include "../model/GeneralEnrichedPose.hpp"

//todo
#include "GeneralKeyPoseDetector.hpp"

//global includes
#include <memory>
#include <queue>
#include <iostream>



namespace mae {
	namespace controller {

		template <typename T, typename U>
		class KPMovementDetector : public IMovementDetector<T,U>
		{
			public:
				KPMovementDetector(std::shared_ptr<IPoseDetector<T> > ipd, std::shared_ptr<ISequenceGenerator<U> > isg);
				KPMovementDetector(std::shared_ptr<IPoseDetector<T> > ipd, std::shared_ptr<ISequenceGenerator<U> > isg, std::shared_ptr<IKeyPoseDetector> ikpd);
				virtual ~KPMovementDetector();

				virtual std::shared_ptr<U> detectMovement(std::shared_ptr<T> skeleton, std::vector<int> bodyParts);
				virtual void setPoseBufferSize(int size);

			private:
				std::shared_ptr<IPoseDetector<T> > ipd;
				std::shared_ptr<ISequenceGenerator<U> > isg;
				std::shared_ptr<IKeyPoseDetector> ikpd;

				int pose_buffer_size;
				std::queue<std::shared_ptr<mae::model::GeneralEnrichedPose> > queue;

		};

	} // namespace controller
} // namespace mae

#include "KPMovementDetector.tpp"

#endif // KPMOVEMENTDETECTOR_HPP_
