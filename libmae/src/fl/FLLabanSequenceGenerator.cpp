/*
 * FLLabanSequenceGenerator.cpp
 *
 *  Created on: 20.05.2014
 *      Author: keks
 */

//custom includes
#include "FLLabanSequenceGenerator.hpp"


namespace mae {
	namespace fl {

		FLLabanSequenceGenerator::FLLabanSequenceGenerator() {
			// TODO Auto-generated constructor stub

		}

		FLLabanSequenceGenerator::~FLLabanSequenceGenerator() {
			// TODO Auto-generated destructor stub
		}

		std::shared_ptr<mae::fl::FLLabanSequence> FLLabanSequenceGenerator::generateSequence(std::vector<std::shared_ptr<mae::model::GeneralEnrichedPose> > keyPoses[], std::vector<int> bodyParts){

			std::shared_ptr<mae::fl::FLLabanSequence> sequence = std::shared_ptr<mae::fl::FLLabanSequence>(new mae::fl::FLLabanSequence());

			//todo do stuff in here

			return sequence;
		}


	} // namespace fl
} // namespace mae
