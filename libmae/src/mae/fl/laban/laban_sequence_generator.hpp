#ifndef MAE_FL_LABAN_LABAN_SEQUENCE_GENERATOR_HPP_
#define MAE_FL_LABAN_LABAN_SEQUENCE_GENERATOR_HPP_

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
				 * @param beats_per_measure The number of beats per measure.
				 * @param beat_duration The duration of a single beat given in the time unit.
				 * @param time_unit The time unit to be used.
				 * @param debug True if debug output is wanted.
				 */
				laban_sequence_generator(std::vector<std::shared_ptr<column_definition> > column_definitions, unsigned int beats_per_measure = laban_sequence::default_beats_per_measure(), unsigned int beat_duration = laban_sequence::default_beat_duration(), e_time_unit time_unit = laban_sequence::default_time_unit(), bool debug = false);
				virtual ~laban_sequence_generator();

				/**
				 * Generates a Labanotation score from the enriched poses.
				 *
				 * @param keyPoses The enriched poses beginning with the lastly performed pose.
				 * @param body_parts The addressed body parts.
				 * @return A Labanotation sequence.
				 */
				virtual std::shared_ptr<laban_sequence> generate_sequence(double framerate,
						std::list<std::shared_ptr<general_enriched_pose> > key_poses, std::vector<bone> body_parts);

				/**
				 * Clears the buffer.
				 */
				virtual void clear_buffer();

			private:
				bool debug_;
				std::vector<std::shared_ptr<column_definition> > column_definitions_;

				unsigned int beats_per_measure_;
				unsigned int beat_duration_;
				e_time_unit time_unit_;



		};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_LABAN_SEQUENCE_GENERATOR_HPP_
