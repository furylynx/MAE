/*
 * FLLabanSequenceGenerator.hpp
 *
 *  Created on: 20.05.2014
 *      Author: keks
 */

#ifndef FLLABANSEQUENCEGENERATOR_HPP_
#define FLLABANSEQUENCEGENERATOR_HPP_

//eclipse indexer fix
#include "indexer_fix.hpp"

//custom includes
#include "FLLabanSequence.hpp"
#include "../model/GeneralEnrichedPose.hpp"
#include "../controller/ISequenceGenerator.hpp"

//global includes
#include <memory>
#include <vector>



namespace mae {
	namespace fl {

		class FLLabanSequenceGenerator : public mae::controller::ISequenceGenerator<FLLabanSequence>
		{
			public:

				FLLabanSequenceGenerator();
				virtual ~FLLabanSequenceGenerator();

				virtual std::shared_ptr<FLLabanSequence> generateSequence(std::queue<std::shared_ptr<mae::model::GeneralEnrichedPose> > keyPoses, std::vector<int> bodyParts);

		};

	} // namespace fl
} // namespace mae

#endif // FLLABANSEQUENCEGENERATOR_HPP_
