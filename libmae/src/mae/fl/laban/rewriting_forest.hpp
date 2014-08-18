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
					rewriting_forest(unsigned int beats_per_measure = laban_sequence::default_beats_per_measure(), unsigned int beat_duration = laban_sequence::default_beat_duration(), e_time_unit time_unit = laban_sequence::default_time_unit());
					virtual ~rewriting_forest();

					virtual std::vector<std::vector<std::shared_ptr<i_movement> > > replacements(std::vector<std::shared_ptr<i_movement> > sequence);

					virtual void add_rule(std::vector<std::shared_ptr<i_movement> > sequence, std::vector<std::vector<std::shared_ptr<i_movement> > > replacements);


					virtual void read_rules_str(std::string xml);
					virtual void read_rules_file(std::string file);

					virtual std::string str();
					virtual void write_file(std::string file);

				private:
					unsigned int beats_per_measure_;
					unsigned int beat_duration_;
					e_time_unit time_unit_;

					std::shared_ptr<i_decision_maker<i_movement> > decision_maker_;
					std::vector<std::shared_ptr<decision_tree<i_movement, std::vector<std::vector<std::shared_ptr<i_movement> > > > > > trees_;

					std::vector<std::shared_ptr<i_movement> > construct_replaced(std::vector<std::shared_ptr<i_movement> > sequence, std::vector<std::shared_ptr<i_movement> > replacement, int start_pos, unsigned int end_pos);
			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // REWRITING_FOREST_HPP_
