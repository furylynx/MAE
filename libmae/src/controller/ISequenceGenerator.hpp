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
#include <vector>
#include <queue>
#include <memory>


namespace mae {
	namespace controller {

		template <typename U>
		class ISequenceGenerator {
			public:
				virtual ~ISequenceGenerator(){}

				virtual std::shared_ptr<U> generateSequence(std::queue<std::shared_ptr<mae::model::GeneralEnrichedPose> > keyPoses, std::vector<int> bodyParts) = 0;
		};

	} // namespace controller
} // namespace mae

#endif // ISEQUENCEGENERATOR_HPP_
