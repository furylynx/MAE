/*
 * laban_sequence_generator.hpp
 *
 *  Created on: 20.05.2014
 *      Author: keks
 */

#ifndef LABAN_SEQUENCE_GENERATOR_HPP_
#define LABAN_SEQUENCE_GENERATOR_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
#include "laban_sequence.hpp"

#include "mv/i_symbol.hpp"
#include "mv/direction_symbol.hpp"
#include "mv/e_level.hpp"
#include "mv/e_direction.hpp"

#include "../e_fl_direction.hpp"

#include "../../general_enriched_pose.hpp"
#include "../../bone.hpp"
#include "../../i_sequence_generator.hpp"

//global includes
#include <memory>
#include <vector>
#include <list>
#include <unordered_map>
#include <complex>
#include <iostream>


namespace mae
{
	namespace fl
	{
		namespace laban
		{

		class laban_sequence_generator: public i_sequence_generator<laban_sequence>
		{
			public:
				/**
				 * Creates a new sequence generator.
				 *
				 * @param debug True if debug output is wanted.
				 */
				laban_sequence_generator(bool debug = false);

				/**
				 * Creates a new sequence generator with additional columns to the default ones.
				 *
				 * @param column_definitions Column definitions for additional columns.
				 * @param debug True if debug output is wanted.
				 */
				laban_sequence_generator(std::vector<std::shared_ptr<column_definition> > column_definitions, bool debug = false);
				virtual ~laban_sequence_generator();

				/**
				 * Generates a Labanotation score from the enriched poses.
				 *
				 * @param keyPoses The enriched poses beginning with the lastly performed pose.
				 * @param body_parts The addressed body parts.
				 * @return A Labanotation sequence.
				 */
				virtual std::shared_ptr<laban_sequence> generate_sequence(
						std::list<std::shared_ptr<general_enriched_pose> > key_poses, std::vector<bone> body_parts);

			private:
				bool debug_;
				std::vector<std::shared_ptr<column_definition> > column_definitions_;


		};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // LABAN_SEQUENCE_GENERATOR_HPP_
