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
#include <fstream>
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
				virtual std::string get_version() const;

				/**
				 * Specifies the authors of the sequence. At least one author should be defined.
				 *
				 * @param authors
				 */
				virtual void set_authors(std::vector<std::string> authors);

				/**
				 * Adds an author.
				 *
				 * @param author The author
				 */
				virtual void add_author(std::string author);

				/**
				 * Returns the listed authors.
				 *
				 * @return The authors.
				 */
				virtual std::vector<std::string> get_authors() const;

				/**
				 * Sets the title of this sequence.
				 *
				 * @param title The title.
				 */
				virtual void set_title(std::string title);

				/**
				 * Returns the title of the sequence.
				 *
				 * @return The title.
				 */
				virtual std::string get_title() const;

				/**
				 * Specifies the description for this sequence.
				 *
				 * @param description The description.
				 */
				virtual void set_description(std::string description);

				/**
				 * Returns the description of this sequence.
				 *
				 * @return The description.
				 */
				virtual std::string get_description() const;

				/**
				 * Sets the amount of measures of the sequence (i.e. the length). A measure consists per definition of
				 * a positive amount of beats, which is the unit time of the Labanotation.
				 *
				 * @param measures The amount of measures.
				 */
				virtual void set_measures(unsigned int measures);

				/**
				 * Returns the amount of measures of the sequence (i.e. the length). A measure consists per definition
				 * of a positive amount of beats, which is the unit time of the Labanotation.
				 *
				 * @return The amount of measures.
				 */
				virtual unsigned int get_measures() const;

				/**
				 * Specifies the time unit used for the beat count.
				 *
				 * @param time_unit The time unit.
				 */
				virtual void set_time_unit(e_time_unit time_unit);

				/**
				 * Returns the time unit used for the beat count.
				 * @return The time unit.
				 */
				virtual e_time_unit get_time_unit() const;

				/**
				 * Specifies the duration of a beat. The time unit (ms, s, m) is defined by the time unit variable
				 * set in this sequence.
				 *
				 * @param beat_duration The duration of a beat.
				 */
				virtual void set_beat_duration(unsigned int beat_duration);

				/**
				 * Returns the duration of a beat. The time unit (ms, s, m) is defined by the time unit variable
				 * set in this sequence.
				 *
				 * @return The beat duration.
				 */
				virtual unsigned int get_beat_duration() const;

				/**
				 * Specifies the number of beats a measure contains (i.e. the length of a measure).
				 *
				 * @param beats The number of beats.
				 */
				virtual void set_beats(unsigned int beats);

				/**
				 * Returns the number of beats a measure contains (i.e. the length of a measure).
				 *
				 * @return The number of beats.
				 */
				virtual unsigned int get_beats() const;

				/**
				 * Specifies all column definitions. A column definition defines the content of a column (the pre sign).
				 *
				 * @param column_definitions The column definition.
				 */
				virtual void set_column_definitions(std::vector<std::shared_ptr<column_definition> > col_defs);

				/**
				 * Adds a new column definition to the definitions. A column definition defines the
				 * content of a column (the pre sign).
				 *
				 * @param definition The definition.
				 */
				virtual void add_column_definition(std::shared_ptr<column_definition> col_def);

				/**
				 * Returns the column definitions.
				 *
				 * @return The column definitions.
				 */
				virtual std::vector<std::shared_ptr<column_definition> > get_column_definitions() const;

				/**
				 * Returns the column definition for the column with the given index.
				 *
				 * @param column_index The column index.
				 * @return The definition.
				 */
				virtual std::shared_ptr<column_definition> get_column_definition(int column_index);

				/**
				 * Clears all column definitions.
				 */
				virtual void clear_column_definitions();

				/**
				 * Returns all columns Id_s that are present in the sequence. This includes the default columns.
				 *
				 * @return The column Id_s.
				 */
				virtual std::vector<int> get_columns();

				/**
				 * Sets the movements by specifying the movements vector.
				 *
				 * @param movements The movements vector.
				 */
				virtual void set_movements(std::vector<std::shared_ptr<i_movement> > movements);

				/**
				 * Returns all registered movements. The vector is not ordered.
				 *
				 * @return The movements vector.
				 */
				virtual std::vector<std::shared_ptr<i_movement> > get_movements() const;

				/**
				 * Add an i_movement to the sequence.
				 *
				 * If the i_movement is a movement it will be sorted in the correct position by ascending time.
				 * Therefore the vector containing all movements of a column is sorted.
				 *
				 * @param movement The movement.
				 */
				virtual void add_movement(std::shared_ptr<i_movement> i_mov);

				/**
				 * Returns a vector containing all listed movements for a column. The vector is sorted by ascending time.
				 *
				 * @param column The column (which is specifying a body part).
				 * @return The movements vector.
				 */
				virtual std::vector<std::shared_ptr<i_movement> > get_column_movements(int column) const;

				/**
				 * Returns the element with the last position among all movements on all columns (despite those without a column (=0)).
				 *
				 * @return The last element.
				 */
				virtual std::shared_ptr<i_movement> get_last_movement() const;

				/**
				 * Clears all movements from this sequence.
				 */
				virtual void clear_movements();

				/**
				 * Returns the xml representation for the sequence.
				 *
				 * @return The xml string.
				 */
				virtual std::string xml(bool no_header = false, unsigned int  indent = 0, std::string namesp = "laban") const;

				/**
				 * Returns the XML namespace header declaration.
				 *
				 * @param namesp The namespace to be applied.
				 * @return The namespace header.
				 */
				virtual std::string xml_namespace_header(std::string namesp = "laban") const;

				/**
				 * Returns the schema location for the XML namespace header.
				 *
				 * @return The schema location string.
				 */
				virtual std::string xml_schema_location() const;

				/**
				 * Returns the XML namespace URI.
				 *
				 * @return The string.
				 */
				virtual std::string xml_namespace_uri() const;

				/**
				 * Prints the sequence to an XML file.
				 *
				 * @param path The file to be printed to.
				 */
				virtual void xml_file(std::string path) const;

				/**
				 * Returns the string representation for the sequence.
				 *
				 * @return The string.
				 */
				virtual std::string str() const;


				friend std::ostream& operator<<(std::ostream& os, const laban_sequence& obj)
				{
					os << obj.str();
					return os;
				}

				friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<laban_sequence>& obj)
				{
					os << obj->str();
					return os;
				}


				/**
				 * Returns the default duration of a single beat.
				 *
				 * @return The default duration.
				 */
				static unsigned int default_beat_duration();

				/**
				 * Returns the default number of beats per measure.
				 *
				 * @return The default beats per measure.
				 */
				static unsigned int default_beats_per_measure();

				/**
				 * Returns the default time unit.
				 *
				 * @return The default unit.
				 */
				static e_time_unit default_time_unit();

				/**
				 * Returns the default columns which are columns that don't need to be specified
				 * by column definitions.
				 *
				 * @return The default columns.
				 */
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

				std::shared_ptr<i_movement> last_movement_;
		};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // LABAN_SEQUENCE_HPP_
