/*
 * FLLabanSequenceGenerator.hpp
 *
 *  Created on: 20.05.2014
 *      Author: keks
 */

#ifndef FLLABANSEQUENCEGENERATOR_HPP_
#define FLLABANSEQUENCEGENERATOR_HPP_

//custom includes
#include "FLLabanSequence.hpp"
#include "../controller/ISequenceGenerator.hpp"

//global includes
//...



namespace mae {
	namespace fl {

		class FLLabanSequenceGenerator: public mae::controller::ISequenceGenerator<mae::fl::FLLabanSequence> {
			public:
				FLLabanSequenceGenerator();
				virtual ~FLLabanSequenceGenerator();

				virtual FLLabanSequence generateSequence(mae::model::GeneralEnrichedPose keyPoses[], int keyPosesSize, int bodyParts[], int bodyPartsSize);
		};

	} // namespace fl
} // namespace mae

#endif // FLLABANSEQUENCEGENERATOR_HPP_
