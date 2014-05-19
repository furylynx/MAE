/*
 * GeneralEnrichedPose.hpp
 *
 *  Created on: 19.05.2014
 *      Author: keks
 */

#ifndef GENERALENRICHEDPOSE_HPP_
#define GENERALENRICHEDPOSE_HPP_

#include "GeneralPose.hpp"

namespace mae {
	namespace model {

		class GeneralEnrichedPose: public GeneralPose
		{
			public:
				virtual ~GeneralEnrichedPose();

				virtual bool isKeyPose(int bodyPart);
				virtual bool isInMotion(int bodyPart);
		};

	} // namespace model
} //namespace mae

#endif // GENERALENRICHEDPOSE_HPP_
