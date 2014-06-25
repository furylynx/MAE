/*
 * FLLabanSequenceGenerator.cpp
 *
 *  Created on: 20.05.2014
 *      Author: keks
 */

//custom includes
#include "laban_sequence_generator.hpp"

namespace mae
{
	namespace fl
	{

		laban_sequence_generator::laban_sequence_generator()
		{
		}

		laban_sequence_generator::~laban_sequence_generator()
		{
		}

		std::shared_ptr<laban_sequence> laban_sequence_generator::generate_sequence(
				std::list<std::shared_ptr<general_enriched_pose> > keyPoses, std::vector<bone> bodyParts)
		{

			std::shared_ptr<mae::fl::laban_sequence> sequence;

			//todo do stuff in here

			return sequence;
		}

	} // namespace fl
} // namespace mae
