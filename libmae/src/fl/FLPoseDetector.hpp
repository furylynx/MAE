/*
 * FLPoseDetector.hpp
 *
 *  Created on: 29.05.2014
 *      Author: keks
 */

#ifndef FLPOSEDETECTOR_HPP_
#define FLPOSEDETECTOR_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "../controller/IPoseDetector.hpp"
#include "FLSkeleton.hpp"
#include "FLMath.hpp"
#include "FLLabanSequence.hpp"
#include "FLD.hpp"
#include "FLJ.hpp"

//global includes
#include <memory>
#include <vector>
#include <iostream>

namespace mae
{
	namespace fl
	{

		class FLPoseDetector: public mae::controller::IPoseDetector<FLSkeleton>
		{
			public:
				FLPoseDetector();
				virtual ~FLPoseDetector();

				virtual std::shared_ptr<mae::model::GeneralPose> pose(std::shared_ptr<FLSkeleton> skeleton,
						std::vector<int> bodyParts);

				virtual std::shared_ptr<mae::model::GeneralPose> angle_pose(std::shared_ptr<FLSkeleton> skeleton,
										std::vector<int> bodyParts);

			private:
				std::vector<std::vector<int> > dir_circ;
				std::vector<int> flj_ext_bones;
				std::vector<int> flj_ext_whole;
		};

	} // namespace fl
} // namespace mae

#endif // FLPOSEDETECTOR_HPP_
