/*
 * FLPoseDetector.hpp
 *
 *  Created on: 29.05.2014
 *      Author: keks
 */

#ifndef FLPOSEDETECTOR_HPP_
#define FLPOSEDETECTOR_HPP_

//custom includes
#include "../controller/IPoseDetector.hpp"
#include "FLSkeleton.hpp"
#include "FLMath.hpp"


//global includes
#include <iostream>

namespace mae {
	namespace fl {

		class FLPoseDetector : public mae::controller::IPoseDetector<FLSkeleton>
		{
			public:
				FLPoseDetector();
				virtual ~FLPoseDetector();

				virtual std::shared_ptr<mae::model::GeneralPose> detectPose(std::shared_ptr<FLSkeleton> skeleton, std::vector<int> bodyParts);
		};

	} // namespace fl
} // namespace mae

#endif // FLPOSEDETECTOR_HPP_
