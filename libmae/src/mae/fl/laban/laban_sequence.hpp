/*
 * FLLabanSequence.hpp
 *
 *  Created on: 19.05.2014
 *      Author: keks
 */

#ifndef LABAN_SEQUENCE_HPP_
#define LABAN_SEQUENCE_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
#include "column_definition.hpp"
#include "i_movement.hpp"
#include "movement.hpp"
#include "e_time_unit.hpp"

//global includes
#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>
#include <ios>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <iostream>


namespace mae {
	namespace fl {
		namespace laban {

		class laban_sequence {
			public:
				/**
				 * Creates a new sequence with default values for title and author and no
				 * definitions for measures, beats and beat duration.
				 *
				 * The timing attributes must be set when having movements in the score.
				 *
				 */
				laban_sequence();

				/**
				 * Creates a new sequence.
				 *
				 * @param title The title of the sequence.
				 * @param author The first author of the sequence.
				 * @param measures The total number of measures this score contains.
				 * @param time_unit The time unit in which the beat duration is given.
				 * @param beat_duration The beat duration (in given time unit).
				 * @param beats The number of beats a measure consists of.
				 */
				laban_sequence(std::string title, std::string author, unsigned int measures, e_time_unit time_unit, unsigned int beat_duration, unsigned int beats);
				virtual ~laban_sequence();

				/**
				 * Returns the version of the sequence schema.
				 *
				 * @return
				 */
				std::string get_version();

				/**
				 * Specifies the authors of the sequence. At least one author should be defined.
				 *
				 * @param authors
				 */
				void set_authors(std::vector<std::string> authors);

				/**
				 * Adds an author.
				 *
				 * @param author The author
				 */
				void add_author(std::string author);

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
				void set_time_unit(e_time_unit time_unit);

				/**
				 * Returns the time unit used for the beat count.
				 * @return The time unit.
				 */
				e_time_unit get_time_unit();

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
				void set_column_definitions(std::vector<std::shared_ptr<column_definition> > col_defs);

				/**
				 * Adds a new column definition to the definitions. A column definition defines the
				 * content of a column (the pre sign).
				 *
				 * @param definition The definition.
				 */
				void add_column_definition(std::shared_ptr<column_definition> col_def);

				/**
				 * Returns the column definitions.
				 *
				 * @return The column definitions.
				 */
				std::vector<std::shared_ptr<column_definition> > get_column_definitions();

				/**
				 * Returns the column definition for the column with the given index.
				 *
				 * @param column_index The column index.
				 * @return The definition.
				 */
				std::shared_ptr<column_definition> get_column_definition(int column_index);

				/**
				 * Sets the movements by specifying the movements vector.
				 *
				 * @param movements The movements vector.
				 */
				void set_movements(std::vector<std::shared_ptr<i_movement> > movements);

				/**
				 * Returns all registered movements. The vector is not ordered.
				 *
				 * @return The movements vector.
				 */
				std::vector<std::shared_ptr<i_movement> > get_movements();

				/**
				 * Add an i_movement to the sequence.
				 *
				 * If the i_movement is a movement it will be sorted in the correct position by ascending time.
				 * Therefore the vector containing all movements of a column is sorted.
				 *
				 * @param movement The movement.
				 */
				void add_movement(std::shared_ptr<i_movement> i_mov);

				/**
				 * Returns a vector containing all listed movements for a column. The vector is sorted by ascending time.
				 *
				 * @param column The column (which is specifying a body part).
				 * @return The movements vector.
				 */
				std::vector<std::shared_ptr<i_movement> > get_column_movements(int column);


				/**
				 * Returns the xml representation for the sequence.
				 *
				 * @return The xml string.
				 */
				virtual std::string xml();


				//TODO doxygen
				static unsigned int default_beat_duration();
				static unsigned int default_beats_per_measure();
				static e_time_unit default_time_unit();
				static std::vector<int> default_columns();

			private:
				std::string version_;
				std::vector<std::string> authors_;
				std::string title_;
				std::string description_;

				unsigned int measures_;
				e_time_unit time_unit_;
				unsigned int beat_duration_;
				unsigned int beats_;

				std::unordered_map<int, std::shared_ptr<column_definition> > column_definitions_map_;
				std::vector<std::shared_ptr<column_definition> > column_definitions_vec_;

				std::unordered_map<int, std::vector<std::shared_ptr<i_movement> > > movements_map_;
				std::vector<std::shared_ptr<i_movement> > movements_vec_;

				std::vector<std::shared_ptr<i_movement> > i_movements_vec_;
		};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // LABAN_SEQUENCE_HPP_
