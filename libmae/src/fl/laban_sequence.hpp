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
#include <vector>
#include <unordered_map>


namespace mae {
	namespace fl {

		enum class time_unit {MINUTE, SECOND, MILLISECOND};



		class laban_sequence {
			public:
				laban_sequence();
				virtual ~laban_sequence();

				void set_version(std::string version);
				std::string get_version();

				void set_authors(std::vector<std::string> authors);
				std::vector<std::string> get_authors();

				void set_title(std::string title);
				std::string get_title();

				void set_description(std::string description);
				std::string get_description();

				void set_measures(unsigned int measures);
				unsigned int get_measures();

				void set_time_unit(time_unit time_unit);
				time_unit get_time_unit();

				void set_beat_duration(unsigned int beat_duration);
				unsigned int get_beat_duration();

				void set_beats(unsigned int beats);
				unsigned int get_beats();

				void set_column_definitions(std::vector<std::string> column_definitions);
				std::vector<std::string> get_column_definitions();

				void set_movements(std::vector<std::shared_ptr<laban_movement> > movements);
				std::vector<std::shared_ptr<laban_movement> > get_movements();

				void add_movement(int column, std::shared_ptr<laban_movement> movement);
				std::vector<std::shared_ptr<laban_movement> > get_movements(int column);
				//TODO more movement methods



			private:
				std::string version_;
				std::vector<std::string> authors_;
				std::string title_;
				std::string description_;

				unsigned int measures_;
				time_unit time_unit_;
				unsigned int beat_duration_;
				unsigned int beats_;

				std::vector<laban_column> column_definitions_;
				std::unordered_map<int, std::vector<std::shared_ptr<laban_movement> > > movements_;
				std::vector<std::shared_ptr<laban_movement>> movements_vec_;
		};

	} // namespace fl
} // namespace mae

#endif // FLLABANSEQUENCE_HPP_
