/*
 * ISequenceGenerator.hpp
 *
 *  Created on: 19.05.2014
 *      Author: keks
 */

#ifndef ISEQUENCEGENERATOR_HPP_
#define ISEQUENCEGENERATOR_HPP_

//eclipse indexer fix
#include "indexer_fix.hpp"

//custom includes
#include "general_enriched_pose.hpp"
#include "bone.hpp"


//global includes
#include <vector>
#include <list>
#include <memory>


namespace mae {
		template <typename U>
		class i_sequence_generator {
			public:
				virtual ~i_sequence_generator(){}

				/**
				 * Generates a sequence from the enriched poses.
				 *
				 * @param keyPoses The enriched poses beginning with the lastly performed pose.
				 * @param body_parts The addressed body parts.
				 * @return The sequence.
				 */
				virtual std::shared_ptr<U> generate_sequence(double framerate, std::list<std::shared_ptr<general_enriched_pose> > keyPoses, std::vector<bone> bodyParts) = 0;
		};

} // namespace mae

#endif // ISEQUENCEGENERATOR_HPP_
