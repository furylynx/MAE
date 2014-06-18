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
		template <typename U>
		class i_sequence_generator {
			public:
				virtual ~i_sequence_generator(){}

				virtual std::shared_ptr<U> generate_sequence(std::queue<std::shared_ptr<general_enriched_pose> > keyPoses, std::vector<int> bodyParts) = 0;
		};

} // namespace mae

#endif // ISEQUENCEGENERATOR_HPP_
