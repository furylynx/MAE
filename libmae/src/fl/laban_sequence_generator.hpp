/*
 * FLLabanSequenceGenerator.hpp
 *
 *  Created on: 20.05.2014
 *      Author: keks
 */

#ifndef FLLABANSEQUENCEGENERATOR_HPP_
#define FLLABANSEQUENCEGENERATOR_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "laban_sequence.hpp"
#include "../model/general_enriched_pose.hpp"
#include "../controller/i_sequence_generator.hpp"

//global includes
#include <memory>
#include <vector>

namespace mae
{
	namespace fl
	{

		class laban_sequence_generator: public i_sequence_generator<laban_sequence>
		{
			public:

				laban_sequence_generator();
				virtual ~laban_sequence_generator();

				virtual std::shared_ptr<laban_sequence> generate_sequence(
						std::queue<std::shared_ptr<general_enriched_pose> > keyPoses, std::vector<int> bodyParts);

		};

	} // namespace fl
} // namespace mae

#endif // FLLABANSEQUENCEGENERATOR_HPP_
