/*
 * decision_tree.hpp
 *
 *  Created on: 12.08.2014
 *      Author: keks
 */

#ifndef DECISION_TREE_HPP_
#define DECISION_TREE_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
#include "decision_node.hpp"

#include "laban_sequence.hpp"
#include "i_decision_maker.hpp"

//global includes
#include <memory>
#include <stdexcept>
#include <vector>

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			class decision_tree
			{
				public:
					/**
					 * Creates a new decision tree for sequences.
					 *
					 * @param body_part The addressed body part.
					 * @param decision_maker The decision maker which is used to decide whether two sequences are equal.
					 */
					decision_tree(int body_part, std::shared_ptr<i_decision_maker> decision_maker);
					virtual ~decision_tree();

					/**
					 * Returns the root node if any. Returns null otherwise.
					 *
					 * @return The root element.
					 */
					virtual std::shared_ptr<decision_node> get_root();

					/**
					 * Adds a sequences to the tree. This may introduce new nodes to the tree.
					 *
					 * @param sequence The sequence to be registered.
					 */
					virtual void add_sequence(std::shared_ptr<laban_sequence> sequence);

					/**
					 * Searches the tree for all sequences that match the motion on the given body part.
					 *
					 * @param whole_sequence The whole sequence which is meant to be looked up for matches with the registered sequences.
					 * @return All matches.
					 */
					virtual std::vector<std::shared_ptr<laban_sequence> >  find_submatches(std::shared_ptr<laban_sequence> whole_sequence);

				private:
					int body_part_;
					std::shared_ptr<i_decision_maker> decision_maker_;
					std::shared_ptr<decision_node> root_;

			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // DECISION_TREE_HPP_
