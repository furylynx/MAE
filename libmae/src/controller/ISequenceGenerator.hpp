/*
 * ISequenceGenerator.hpp
 *
 *  Created on: 19.05.2014
 *      Author: keks
 */

#ifndef ISEQUENCEGENERATOR_HPP_
#define ISEQUENCEGENERATOR_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "../model/general_enriched_pose.hpp"

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

				virtual std::shared_ptr<U> generateSequence(std::queue<std::shared_ptr<general_enriched_pose> > keyPoses, std::vector<int> bodyParts) = 0;
		};

	} // namespace controller
} // namespace mae

#endif // ISEQUENCEGENERATOR_HPP_
