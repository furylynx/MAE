/*
 * ISequenceGenerator.hpp
 *
 *  Created on: 19.05.2014
 *      Author: keks
 */

#ifndef ISEQUENCEGENERATOR_HPP_
#define ISEQUENCEGENERATOR_HPP_

//custom includes
#include "../model/GeneralEnrichedPose.hpp"

//global includes
//...


namespace mae {
	namespace controller {

		template <class U>
		class ISequenceGenerator {
			public:
				virtual ~ISequenceGenerator();

				virtual U generateSequence(mae::model::GeneralEnrichedPose keyPoses[], int keyPosesSize, int bodyParts[], int bodyPartsSize) = 0;
		};

	} // namespace controller
} // namespace mae

#endif // ISEQUENCEGENERATOR_HPP_
