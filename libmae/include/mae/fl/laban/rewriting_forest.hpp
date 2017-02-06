/*
 * rewriting_rules.hpp
 *
 *  Created on: 13.08.2014
 *      Author: keks
 */

#ifndef REWRITING_FOREST_HPP_
#define REWRITING_FOREST_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
#include "decision_tree.hpp"

#include "i_decision_maker.hpp"
#include "i_movement.hpp"
#include "movement.hpp"
#include "e_time_unit.hpp"
#include "laban_sequence.hpp"
#include "rewriting_decision_maker.hpp"

//global includes
#include <memory>
#include <vector>
#include <stdexcept>
#include <unordered_map>
#include <string>
#include <sstream>
#include <unordered_map>

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			class rewriting_forest
			{
				public:
					/**
					 * Creates a new decision forest for rewriting rules.
					 *
					 * @param beats_per_measure The beats per measure as used by the laban sequence generator.
					 * @param beat_duration The beat duration as used by the laban sequence generator.
					 * @param time_unit The time unit as used by the laban sequence generator.
					 */
					rewriting_forest(unsigned int beats_per_measure = laban_sequence::default_beats_per_measure(), unsigned int beat_duration = laban_sequence::default_beat_duration(), e_time_unit time_unit = laban_sequence::default_time_unit(), double tolerance = 0.5);

					/**
					 * Creates a new decision forest for rewriting rules with initial rules set.
					 *
					 * @param rules The rules to be added to the forest.
					 * @param beats_per_measure The beats per measure as used by the laban sequence generator.
					 * @param beat_duration The beat duration as used by the laban sequence generator.
					 * @param time_unit The time unit as used by the laban sequence generator.
					 * @param tolerance The tolerance applied for finding continuous movements.
					 */
					rewriting_forest(std::vector<std::shared_ptr<decision_value<i_movement, std::vector<std::vector<std::shared_ptr<i_movement> > > > > > rules, unsigned int beats_per_measure = laban_sequence::default_beats_per_measure(), unsigned int beat_duration = laban_sequence::default_beat_duration(), e_time_unit time_unit = laban_sequence::default_time_unit(), double tolerance = 0.5);

					virtual ~rewriting_forest();

					/**
					 * Returns the tolerance value (in beats) for a connected sequence.
					 *
					 * @return The tolerance.
					 */
					virtual double get_tolerance();

					/**
					 * Sets the tolerance value (in beats) for a connected sequence.
					 *
					 * @param tolerance The tolerance.
					 */
					virtual void set_tolerance(double tolerance);

					/**
					 * Returns all equivalent sequences for the given sequence (this includes the unchanged sequence itself).
					 *
					 * @param sequence The sequence to be checked for replacements.
					 * @return All equivalent sequences.
					 */
					virtual std::vector<std::vector<std::shared_ptr<i_movement> > > replacements(std::vector<std::shared_ptr<i_movement> > sequence);

					/**
					 * Adds a rewriting rule to the forest.
					 *
					 * @param sequence The sequence.
					 * @param replacements The replacement for the sequence.
					 */
					virtual void add_rule(std::vector<std::shared_ptr<i_movement> > sequence, std::shared_ptr<std::vector<std::vector<std::shared_ptr<i_movement> > > > replacements);

					/**
					 * Adds a rewriting rule to the forest.
					 *
					 * @param rule The rule to be added.
					 */
					virtual void add_rule(std::shared_ptr<decision_value<i_movement, std::vector<std::vector<std::shared_ptr<i_movement> > > > > rule);

					/**
					 * Returns the string representation for the rewriting forest.
					 *
					 * @return The string representation.
					 */
					virtual std::string str();


				private:
					unsigned int beats_per_measure_;
					unsigned int beat_duration_;
					e_time_unit time_unit_;
					double tolerance_;

					std::shared_ptr<i_decision_maker<i_movement> > decision_maker_;
					std::vector<std::shared_ptr<decision_tree<i_movement, std::vector<std::vector<std::shared_ptr<i_movement> > > > > > trees_;

					/**
					 * Construct the new sequence with the given replacement.
					 *
					 * @param sequence The unchanged sequence.
					 * @param replacement The replacement for the sequence.
					 * @param start_pos The start position of the replacement.
					 * @param end_pos The end position of the replacement.
					 * @return The new, replaced sequence.
					 */
					std::vector<std::shared_ptr<i_movement> > construct_replaced(std::vector<std::shared_ptr<i_movement> > sequence, std::vector<std::shared_ptr<i_movement> > replacement, unsigned int start_pos, unsigned int end_pos);
			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // REWRITING_FOREST_HPP_
