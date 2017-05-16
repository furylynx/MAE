#ifndef MAE_FL_LABAN_LABAN_SEQUENCE_RECOGNIZER_H_
#define MAE_FL_LABAN_LABAN_SEQUENCE_RECOGNIZER_H_

//custom includes
#include "laban_sequence.hpp"
#include "decision_forest.hpp"

#include "../../i_sequence_recognizer.hpp"
#include "../../bone.hpp"

//global includes
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <list>


namespace mae
{
	namespace fl
	{
		namespace laban
		{
			class laban_sequence_recognizer: public i_sequence_recognizer<laban_sequence>
			{
				public:
					/**
					 * Creates a new recognizer for laban sequences.
					 *
					 * @param debug True for debug output on the terminal.
					 */
					laban_sequence_recognizer(bool debug = false);

					/**
					 * Creates a new recognizer for laban sequences.
					 *
					 * @param column_definitions The column definitions as used by the laban sequence generator.
					 * @param beats_per_measure The number of beats per measure as used by the laban sequence generator.
					 * @param beat_duration The beat duration as used by the laban sequence generator.
					 * @param time_unit The time unit as used by the laban sequence generator.
					 * @param debug True for debug output on the terminal.
					 */
					laban_sequence_recognizer(std::vector<std::shared_ptr<column_definition> > column_definitions,
							unsigned int beats_per_measure = laban_sequence::default_beats_per_measure(),
							unsigned int beat_duration = laban_sequence::default_beat_duration(),
							e_time_unit time_unit = laban_sequence::default_time_unit(), bool debug = false);

					virtual ~laban_sequence_recognizer();

					/**
					 * Sets the tolerance for the recognition. The tolerance is a value which represents the
					 * number of beats of the labanotation which are tolerated in deviation.
					 *
					 * @param tolerance The tolerance to be accepted.
					 */
					virtual void set_recognition_tolerance(double tolerance);

					/**
					 * Returns the underlying decision forest used to recognize sequences.
					 *
					 * @return The decision forest.
					 */
					virtual std::shared_ptr<decision_forest> get_decision_forest() const;

					/**
					 * Registers a sequence to the recognizer.
					 *
					 * @param sequence The sequence.
					 */
					virtual void register_sequence(std::shared_ptr<laban_sequence> sequence);

					/**
					 * Removes the sequence from the recognizer.
					 *
					 * @param sequence The sequence.
					 * @return True if the sequence was removed.
					 */
					virtual bool deregister_sequence(std::shared_ptr<laban_sequence> sequence);

					/**
					 * Removes the sequence at the index position of the list.
					 *
					 * @param list_index The index.
					 * @return True if the sequence was removed.
					 */
					virtual bool deregister_sequence(unsigned int list_index);

					/**
					 * Removes all registered sequences.
					 */
					virtual void clear_registered_sequences();

					/**
					 * Clears the buffer.
					 */
					virtual void clear_buffer();

					/**
					 * Returns all registered sequences.
					 *
					 * @return All sequences.
					 */
					virtual std::list<std::shared_ptr<laban_sequence> > get_registered_sequences() const;

					/**
					 * Returns the length of the sequence in milliseconds.
					 *
					 * @param sequence The sequence.
					 * @return The length of the sequence.
					 */
					virtual int get_sequence_length(std::shared_ptr<laban_sequence> sequence) const;

					/**
					 * Recognized subsequences in the sequence for the given body parts.
					 *
					 * @param framerate The framerate to be applied.
					 * @param sequence The sequences to be looked at.
					 * @param body_parts The body parts.
					 * @return All matches.
					 */
					virtual std::vector<std::shared_ptr<laban_sequence> > recognize_sequence(double framerate,
							std::shared_ptr<laban_sequence> sequence, std::vector<bone> body_parts);

					/**
					 * Returns the string representation for the underlying decision forest.
					 *
					 * @return The string.
					 */
					virtual std::string str() const;
				private:
					bool debug_;

					std::vector<std::shared_ptr<column_definition> > column_definitions_;
					std::vector<int> reserved_columns_;

					unsigned int beats_per_measure_;
					unsigned int beat_duration_;
					e_time_unit time_unit_;

					std::shared_ptr<decision_forest> decision_forest_;
			};
		} // namespace laban
	} // namespace fl
} // namespace mae
#endif // MAE_FL_LABAN_LABAN_SEQUENCE_RECOGNIZER_H_
