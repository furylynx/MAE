/*
 * decision_forest.hpp
 *
 *  Created on: 12.08.2014
 *      Author: keks
 */

#ifndef DECISION_FOREST_HPP_
#define DECISION_FOREST_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
#include "decision_tree.hpp"

#include "laban_sequence.hpp"
#include "i_decision_maker.hpp"
#include "decision_maker.hpp"

//global includes
#include <memory>
#include <stdexcept>
#include <vector>
#include <unordered_map>

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			class decision_forest
			{
				public:
					/**
					 * Creates a new decision forest for laban_sequences.
					 *
					 * @param column_definitions The columns that are taken into account (besides the default ones).
					 * @param reserved_columns The reserved columns used by the scores.
					 * @param beats_per_measure The number of beats per measure.
					 * @param beat_duration The duration of a single beat.
					 * @param time_unit The time unit used by the scores.
					 * @param dec_maker The decision maker to compare movements.
					 */
					decision_forest(std::vector<std::shared_ptr<column_definition> > column_definitions = std::vector<std::shared_ptr<column_definition> >(), std::vector<int> reserved_columns = laban_sequence::default_columns(), unsigned int beats_per_measure = laban_sequence::default_beats_per_measure(), unsigned int beat_duration = laban_sequence::default_beat_duration(), e_time_unit time_unit = laban_sequence::default_time_unit(), std::shared_ptr<i_decision_maker<i_movement> > dec_maker = nullptr);

					virtual ~decision_forest();

					/**
					 * Adds a sequence to the forest. It will stored in different decision trees for each body part.
					 * Since body part IDs are used to identify the columns, the column definition for all sequences
					 * should be the same.
					 *
					 * @param sequence The sequence to be registered.
					 */
					void add_sequence(std::shared_ptr<laban_sequence> sequence);

					/**
					 * Searches the sequence for matches of subsequences (which are the registered ones).
					 *
					 * @param whole_sequence The whole sequence to be processed.
					 * @return All matching sequences.
					 */
					std::vector<std::shared_ptr<laban_sequence> > find_submatches(std::shared_ptr<laban_sequence> whole_sequence);

				private:
					std::vector<std::shared_ptr<column_definition> > column_definitions_;
					std::vector<int> column_ids_;
					unsigned int beats_per_measure_;
					unsigned int beat_duration_;
					e_time_unit time_unit_;

					std::shared_ptr<i_decision_maker<i_movement> > decision_maker_;

					std::unordered_map<int, std::vector<std::shared_ptr<decision_tree<i_movement, laban_sequence> > > > trees_;

			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // DECISION_FOREST_HPP_
