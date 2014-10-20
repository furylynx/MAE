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
				virtual std::vector<int> get_columns() const;

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
				 * Returns the SVG representation for this sequence.
				 *
				 * @param im_width The image width.
				 * @param im_height The image heigth.
				 * @return The SVG.
				 */
				virtual std::string svg(unsigned int im_width, unsigned int im_height) const;

				/**
				 * Prints the corresponding svg file for this sequence.
				 *
				 * @param path The file path.
				 * @param im_width The image width.
				 * @param im_height The image heigth.
				 */
				virtual void svg_file(std::string path, unsigned int im_width = 1920, unsigned int im_height = 1080) const;

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

				const std::string FILL_PATTERN = "    <pattern                                                                                                                 "
    "   id=\"fillpattern\"                                                                                                                                                     "
    "   patternTransform=\"translate(550.0,-750.0)\"                                                                                                                    "
    "   height=\"2195.3125\"                                                                                                                                                   "
    "   width=\"2028.4062\"                                                                                                                                                    "
    "   patternUnits=\"userSpaceOnUse\">                                                                                                                                       "
    "  <g                                                                                                                                                                      "
    "     transform=\"translate(639.625,561.71875)\"                                                                                                                           "
    "     id=\"g3513\">                                                                                                                                                        "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982\"                                                                                                                                                    "
    "       d=\"M -638.63881,99.015073 502.79399,-559.99145 z\"                                                                                                                "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-2\"                                                                                                                                                  "
    "       d=\"M -595.46872,173.78788 545.96409,-485.21867 z\"                                                                                                                "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-7\"                                                                                                                                                  "
    "       d=\"M -573.88366,211.1743 567.54915,-447.83224 z\"                                                                                                                 "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-29\"                                                                                                                                                 "
    "       d=\"M -530.71352,285.94718 610.71929,-373.05937 z\"                                                                                                                "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-6\"                                                                                                                                                  "
    "       d=\"M -487.54337,360.72005 653.88942,-298.28648 z\"                                                                                                                "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-4\"                                                                                                                                                  "
    "       d=\"M -422.78816,472.87938 718.64466,-186.12717 z\"                                                                                                                "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-8\"                                                                                                                                                  "
    "       d=\"M -336.44789,622.4251 804.98491,-36.58143 z\"                                                                                                                  "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-9\"                                                                                                                                                  "
    "       d=\"M -293.27779,697.19792 848.15503,38.191375 z\"                                                                                                                 "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-49\"                                                                                                                                                 "
    "       d=\"M -206.93752,846.74366 934.49529,187.73711 z\"                                                                                                                 "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-66\"                                                                                                                                                 "
    "       d=\"M -142.18234,958.90292 999.25048,299.89639 z\"                                                                                                                 "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-93\"                                                                                                                                                 "
    "       d=\"M -77.42713,1071.0623 1064.0057,412.0557 z\"                                                                                                                   "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-0\"                                                                                                                                                  "
    "       d=\"M -163.7674,921.51652 977.66543,262.50997 z\"                                                                                                                  "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-24\"                                                                                                                                                 "
    "       d=\"M -250.10764,771.97082 891.32517,112.96427 z\"                                                                                                                 "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-5\"                                                                                                                                                  "
    "       d=\"M -358.03299,585.03865 783.39984,-73.967904 z\"                                                                                                                "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-72\"                                                                                                                                                 "
    "       d=\"M -509.12846,323.33358 632.30435,-335.67295 z\"                                                                                                                "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-42\"                                                                                                                                                 "
    "       d=\"M -552.2986,248.56072 589.13421,-410.44582 z\"                                                                                                                 "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-1\"                                                                                                                                                  "
    "       d=\"M -617.05376,136.40148 524.37903,-522.60506 z\"                                                                                                                "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-95\"                                                                                                                                                 "
    "       d=\"M -34.256975,1145.8351 1107.1758,486.82858 z\"                                                                                                                 "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-80\"                                                                                                                                                 "
    "       d=\"M 30.498204,1257.9944 1171.931,598.98786 z\"                                                                                                                   "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-41\"                                                                                                                                                 "
    "       d=\"M 116.83846,1407.5401 1258.2713,748.53358 z\"                                                                                                                  "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-938\"                                                                                                                                                "
    "       d=\"M 160.0086,1482.313 1301.4414,823.30644 z\"                                                                                                                    "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-20\"                                                                                                                                                 "
    "       d=\"M 73.668341,1332.7672 1215.1011,673.76072 z\"                                                                                                                  "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-98\"                                                                                                                                                 "
    "       d=\"M 203.17873,1557.0859 1344.6115,898.07931 z\"                                                                                                                  "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-3\"                                                                                                                                                  "
    "       d=\"M 246.34887,1631.8587 1387.7817,972.85217 z\"                                                                                                                  "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-62\"                                                                                                                                                 "
    "       d=\"M 224.76379,1594.4722 1366.1966,935.46571 z\"                                                                                                                  "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-48\"                                                                                                                                                 "
    "       d=\"M 181.59366,1519.6993 1323.0265,860.69287 z\"                                                                                                                  "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-92\"                                                                                                                                                 "
    "       d=\"M 138.42354,1444.9266 1279.8563,785.92001 z\"                                                                                                                  "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-46\"                                                                                                                                                 "
    "       d=\"M 52.083264,1295.3808 1193.5161,636.37428 z\"                                                                                                                  "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-64\"                                                                                                                                                 "
    "       d=\"M 95.253401,1370.1538 1236.6862,711.14714 z\"                                                                                                                  "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-08\"                                                                                                                                                 "
    "       d=\"M 8.9131443,1220.608 1150.3459,561.60142 z\"                                                                                                                   "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-06\"                                                                                                                                                 "
    "       d=\"M -12.671933,1183.2215 1128.7609,524.215 z\"                                                                                                                   "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-28\"                                                                                                                                                 "
    "       d=\"M -55.84207,1108.4487 1085.5908,449.44212 z\"                                                                                                                  "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-86\"                                                                                                                                                 "
    "       d=\"M -99.012189,1033.6758 1042.4206,374.66927 z\"                                                                                                                 "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-32\"                                                                                                                                                 "
    "       d=\"M -120.59726,996.28936 1020.8355,337.28283 z\"                                                                                                                 "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-59\"                                                                                                                                                 "
    "       d=\"M -185.35245,884.1301 956.08037,225.12355 z\"                                                                                                                  "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-68\"                                                                                                                                                 "
    "       d=\"M -228.52258,809.35724 912.91023,150.35069 z\"                                                                                                                 "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-081\"                                                                                                                                                "
    "       d=\"M -271.69272,734.58436 869.74009,75.577814 z\"                                                                                                                 "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-78\"                                                                                                                                                 "
    "       d=\"M -314.86287,659.81147 826.56994,0.80491961 z\"                                                                                                                "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-50\"                                                                                                                                                 "
    "       d=\"M -379.61806,547.65219 761.81474,-111.35436 z\"                                                                                                                "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-45\"                                                                                                                                                 "
    "       d=\"M -401.20309,510.2658 740.22972,-148.74073 z\"                                                                                                                 "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-15\"                                                                                                                                                 "
    "       d=\"M -465.95831,398.10651 675.47452,-260.90004 z\"                                                                                                                "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "    <path                                                                                                                                                                 "
    "       id=\"path3982-63\"                                                                                                                                                 "
    "       d=\"M -444.37327,435.49287 697.05954,-223.51367 z\"                                                                                                                "
    "       style=\"fill:none;stroke:#000000;stroke-width:4;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />          "
    "  </g>                                                                                                                                                                    "
    "</pattern>";
		};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // LABAN_SEQUENCE_HPP_
