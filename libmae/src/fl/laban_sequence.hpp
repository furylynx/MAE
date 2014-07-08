/*
 * FLLabanSequence.hpp
 *
 *  Created on: 19.05.2014
 *      Author: keks
 */

#ifndef FLLABANSEQUENCE_HPP_
#define FLLABANSEQUENCE_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "laban_column.hpp"
#include "laban_movement.hpp"

//global includes
#include <memory>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>


namespace mae {
	namespace fl {

		enum class time_unit {MINUTE, SECOND, MILLISECOND, SIZE};
		static const char* time_unit_str[(int) time_unit::SIZE] = { "minute", "second", "millisecond" };


		class laban_sequence {
			public:
				laban_sequence();
				virtual ~laban_sequence();

				/**
				 * Specifies the authors of the sequence. At least one author should be defined.
				 *
				 * @param authors
				 */
				void set_authors(std::vector<std::string> authors);

				/**
				 * Returns the listed authors.
				 *
				 * @return The authors.
				 */
				std::vector<std::string> get_authors();

				/**
				 * Sets the title of this sequence.
				 *
				 * @param title The title.
				 */
				void set_title(std::string title);

				/**
				 * Returns the title of the sequence.
				 *
				 * @return The title.
				 */
				std::string get_title();

				/**
				 * Specifies the description for this sequence.
				 *
				 * @param description The description.
				 */
				void set_description(std::string description);

				/**
				 * Returns the description of this sequence.
				 *
				 * @return The description.
				 */
				std::string get_description();

				/**
				 * Sets the amount of measures of the sequence (i.e. the length). A measure consists per definition of
				 * a positive amount of beats, which is the unit time of the Labanotation.
				 *
				 * @param measures The amount of measures.
				 */
				void set_measures(unsigned int measures);

				/**
				 * Returns the amount of measures of the sequence (i.e. the length). A measure consists per definition
				 * of a positive amount of beats, which is the unit time of the Labanotation.
				 *
				 * @return The amount of measures.
				 */
				unsigned int get_measures();

				/**
				 * Specifies the time unit used for the beat count.
				 *
				 * @param time_unit The time unit.
				 */
				void set_time_unit(time_unit time_unit);

				/**
				 * Returns the time unit used for the beat count.
				 * @return The time unit.
				 */
				time_unit get_time_unit();

				/**
				 * Specifies the duration of a beat. The time unit (ms, s, m) is defined by the time unit variable
				 * set in this sequence.
				 *
				 * @param beat_duration The duration of a beat.
				 */
				void set_beat_duration(unsigned int beat_duration);

				/**
				 * Returns the duration of a beat. The time unit (ms, s, m) is defined by the time unit variable
				 * set in this sequence.
				 *
				 * @return The beat duration.
				 */
				unsigned int get_beat_duration();

				/**
				 * Specifies the number of beats a measure contains (i.e. the length of a measure).
				 *
				 * @param beats The number of beats.
				 */
				void set_beats(unsigned int beats);

				/**
				 * Returns the number of beats a measure contains (i.e. the length of a measure).
				 *
				 * @return The number of beats.
				 */
				unsigned int get_beats();

				/**
				 * Specifies all column definitions. A column definition defines the content of a column (the pre sign).
				 *
				 * @param column_definitions The column definition.
				 */
				void set_column_definitions(std::vector<std::shared_ptr<laban_column> > column_definitions);

				/**
				 * Adds a new column definition to the definitions. A column definition defines the
				 * content of a column (the pre sign).
				 *
				 * @param definition The definition.
				 */
				void add_column_definition(std::shared_ptr<laban_column> definition);

				/**
				 * Returns the column definitions.
				 *
				 * @return The column definitions.
				 */
				std::vector<std::shared_ptr<laban_column> > get_column_definitions();

				/**
				 * Sets the movements by specifying the movements vector. The vector does not need to be sorted.
				 *
				 * @param movements The movements vector.
				 */
				void set_movements(std::vector<std::shared_ptr<laban_movement> > movements);

				/**
				 * Returns all registered movements. The vector is not ordered.
				 *
				 * @return The movements vector.
				 */
				std::vector<std::shared_ptr<laban_movement> > get_movements();

				/**
				 * Add a movement to the column specified by the movement. The movement will be sorted
				 * in the correct position by ascending time. Therefore the vector containing all movements
				 * of a column is sorted.
				 *
				 * @param column The addressed column.
				 * @param movement The movement.
				 */
				void add_movement(std::shared_ptr<laban_movement> movement);

				/**
				 * Returns a vector containing all listed movements for a column. The vector is sorted by ascending time.
				 *
				 * @param column The column (which is specifying a body part).
				 * @return The movements vector.
				 */
				std::vector<std::shared_ptr<laban_movement> > get_movements(int column);



				virtual std::string xml();


			private:
				std::string version_;
				std::vector<std::string> authors_;
				std::string title_;
				std::string description_;

				unsigned int measures_;
				time_unit time_unit_;
				unsigned int beat_duration_;
				unsigned int beats_;

				std::vector<std::shared_ptr<laban_column> > column_definitions_;
				std::unordered_map<int, std::vector<std::shared_ptr<laban_movement> > > movements_;
				std::vector<std::shared_ptr<laban_movement> > movements_vec_;
		};

	} // namespace fl
} // namespace mae

#endif // FLLABANSEQUENCE_HPP_
