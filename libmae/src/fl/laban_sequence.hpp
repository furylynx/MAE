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
				std::unordered_map<int, std::shared_ptr<laban_movement> > movements_;
				std::vector<std::shared_ptr<laban_movement>> movements_vec_;
		};

	} // namespace fl
} // namespace mae

#endif // FLLABANSEQUENCE_HPP_
