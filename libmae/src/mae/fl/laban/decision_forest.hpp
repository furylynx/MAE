/*
 * decision_forest.hpp
 *
 *  Created on: 12.08.2014
 *      Author: keks
 */

#ifndef DECISION_FOREST_HPP_
#define DECISION_FOREST_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
#include "decision_tree.hpp"

#include "laban_sequence.hpp"
#include "i_decision_maker.hpp"

//global includes
#include <memory>
#include <stdexcept>
#include <vector>
#include <unordered_map>

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
					 * @param body_parts The body parts that are taken into account.
					 * @param decision_maker The decision maker to compare movements.
					 */
					decision_forest(std::vector<int> body_parts, std::shared_ptr<i_decision_maker> decision_maker);
					virtual ~decision_forest();

					/**
					 * Adds a sequence to the forest. It will stored in different decision trees for each body part.
					 * Since body part IDs are used to identify the columns, the column definition for all sequences
					 * should be the same.
					 *
					 * @param sequence The sequence to be registered.
					 */
					void add_sequence(std::shared_ptr<laban_sequence> sequence);

					/**
					 * Searches the sequence for matches of subsequences (which are the registered ones).
					 *
					 * @param whole_sequence The whole sequence to be processed.
					 * @return All matching sequences.
					 */
					std::vector<std::shared_ptr<laban_sequence> > find_submatches(std::shared_ptr<laban_sequence> whole_sequence);

				private:
					std::vector<int> body_parts_;

					std::shared_ptr<i_decision_maker> decision_maker_;

					std::unordered_map<int, std::vector<std::shared_ptr<decision_tree> > > trees_;

			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // DECISION_FOREST_HPP_
