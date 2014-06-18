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
		}

		FLLabanSequenceGenerator::~FLLabanSequenceGenerator() {
		}

		std::shared_ptr<FLLabanSequence> FLLabanSequenceGenerator::generateSequence(std::queue<std::shared_ptr<general_enriched_pose> > keyPoses, std::vector<int> bodyParts){

			std::shared_ptr<mae::fl::FLLabanSequence> sequence;

			//todo do stuff in here

			return sequence;
		}


	} // namespace fl
} // namespace mae
