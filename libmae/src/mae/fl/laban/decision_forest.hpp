/*
 * decision_forest.hpp
 *
 * Created on: 12.08.2014
 * Author: keks
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
#include "rewriting_forest.hpp"

#include "../../bone.hpp"

//global includes
#include <memory>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <list>


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
					 * @param rw The rewriting forest. If not set not rewriting rules are applied.
					 * @param cooldown True for applying a cooldown on the recognized sequences.
					 */
					decision_forest(
							std::vector<std::shared_ptr<column_definition> > column_definitions = std::vector<
									std::shared_ptr<column_definition> >(), std::vector<int> reserved_columns =
									laban_sequence::default_columns(), unsigned int beats_per_measure =
									laban_sequence::default_beats_per_measure(), unsigned int beat_duration =
									laban_sequence::default_beat_duration(), e_time_unit time_unit =
									laban_sequence::default_time_unit(),
							std::shared_ptr<i_decision_maker<i_movement> > dec_maker = nullptr,
							std::shared_ptr<rewriting_forest> rw = nullptr,
							bool cooldown = true
							);
					virtual ~decision_forest();

					/**
					 * Sets the tolerance for the recognition. The tolerance is a value which represents the
					 * number of beats of the labanotation which are tolerated in deviation.
					 *
					 * @param tolerance The tolerance to be accepted.
					 */
					virtual void set_recognition_tolerance(double tolerance);

					/**
					 * Turns the cooldown mechanism on or off.
					 *
					 * @param cooldown True to apply cooldown.
					 */
					virtual void set_cooldown(bool cooldown);

					/**
					 * Returns true if the cooldown mechanism is turned on. False otherwise.
					 *
					 * @return True when cooldown is applied.
					 */
					virtual bool get_cooldown() const;

					/**
					 * Returns the length of the sequence in milliseconds.
					 *
					 * @param sequence The sequence.
					 * @return The length of the sequence.
					 */
					virtual int get_sequence_length(std::shared_ptr<laban_sequence> sequence) const;

					/**
					 * Adds a sequence to the forest. It will stored in different decision trees for each body part.
					 * Since body part IDs are used to identify the columns, the column definition for all sequences
					 * should be the same.
					 *
					 * @param sequence The sequence to be registered.
					 */
					virtual void add_sequence(std::shared_ptr<laban_sequence> sequence);

					/**
					 * Removes the sequence from the forest. Processes all involved trees.
					 *
					 * @param sequence The sequence to be removed.
					 * @return True if successful.
					 */
					virtual bool remove_sequence(std::shared_ptr<laban_sequence> sequence);

					/**
					 * Removes the sequence with the given index in the sequence list (received by get_sequences()).
					 *
					 * @param list_index The index of the sequence in the list.
					 * @return True if successful.
					 */
					virtual bool remove_sequence(unsigned int list_index);

					/**
					 * Removes all sequences from the forest. This removes all associated trees either.
					 */
					virtual void clear();

					/**
					 * Adds a rewriting rule to the forest.
					 *
					 * @param sequence The sequence.
					 * @param replacements The replacement for the sequence.
					 */
					virtual void add_rewriting_rule(std::vector<std::shared_ptr<i_movement> > sequence, std::shared_ptr<std::vector<std::vector<std::shared_ptr<i_movement> > > > replacements);

					/**
					 * Adds a rewriting rule to the forest.
					 *
					 * @param rule The rule to be added.
					 */
					virtual void add_rewriting_rule(std::shared_ptr<decision_value<i_movement, std::vector<std::vector<std::shared_ptr<i_movement> > > > > rule);

					/**
					 * Recreates the sequence with adjusted beat duration, beats per measure and time unit. Additionally
					 * the column definitions are adjusted.
					 *
					 * @param sequence The sequence to be recreated.
					 * @return The new, adjusted sequence.
					 */
					std::shared_ptr<laban_sequence> recreate_sequence(std::shared_ptr<laban_sequence> sequence);

					/**
					 * Returns all registered sequences.
					 *
					 * @return All sequences.
					 */
					virtual std::list<std::shared_ptr<laban_sequence> > get_sequences() const;

					/**
					 * Searches the sequence for matches of subsequences (which are the registered ones).
					 *
					 * @param whole_sequence The whole sequence to be processed.
					 * @param body_parts All the body parts that are meant to be taken into account.
					 * @return All matching sequences.
					 */
					virtual std::vector<std::shared_ptr<laban_sequence> > find_submatches(double framerate,
							std::shared_ptr<laban_sequence> whole_sequence, std::vector<bone> body_parts);

					/**
					 * Returns the string representation for the decision forest.
					 *
					 * @return The string.
					 */
					virtual std::string str() const;

				private:
					std::vector<std::shared_ptr<column_definition> > column_definitions_;
					std::vector<int> column_ids_;

					unsigned int beats_per_measure_;
					unsigned int beat_duration_;
					e_time_unit time_unit_;

					bool cooldown_;
					std::unordered_map<std::shared_ptr<laban_sequence>, unsigned int> cooldown_times_;

					std::shared_ptr<i_decision_maker<i_movement> > decision_maker_;
					std::shared_ptr<rewriting_forest> rewriting_forest_;

					std::unordered_map<int, std::vector<std::shared_ptr<decision_tree<i_movement, laban_sequence> > > > trees_;
					std::list<std::shared_ptr<laban_sequence> > sequences_;

					/**
					 * Removes the sequence from the trees but not from the list (expects this to be done already).
					 * @return True if successful.
					 */
					bool remove_sequence_p(std::shared_ptr<laban_sequence> sequence);



			};
		} // namespace laban
	} // namespace fl
} // namespace mae
#endif // DECISION_FOREST_HPP_
