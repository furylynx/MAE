/*
 * decision_node.hpp
 *
 *  Created on: 12.08.2014
 *      Author: keks
 */

#ifndef DECISION_NODE_HPP_
#define DECISION_NODE_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
#include "laban_sequence.hpp"
#include "i_decision_maker.hpp"

//global includes
#include <memory>
#include <stdexcept>
#include <vector>
#include <string>
#include <sstream>

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			class decision_node
			{
				public:
					/**
					 * Creates a decision node which is a node of the decision tree for sequences.
					 *
					 * @param body_part The addressed body part (which also identifies the column of the sequences.
					 * @param decision_maker The decision maker which is used to decide whether sequence elements are equal.
					 * @param decision_item The item which is used to decide which sequence part this node matches.
					 */
					decision_node(int body_part, std::shared_ptr<i_decision_maker> decision_maker,
							std::shared_ptr<i_movement> decision_item);
					virtual ~decision_node();

					/**
					 * Adds a sequence to the node. Processes the children recursively. Adds children
					 * if decision elements are missing.
					 *
					 * @param sequence The sequence to be registered. Regards only the given body part.
					 * @param step The step which is used to identify a specific sequence element.
					 */
					virtual void add_sequence(std::shared_ptr<laban_sequence> sequence, int step);

					/**
					 * Finds matches of subsequences in the whole sequence. This means that the
					 * whole sequences is looked up for having some of the registered sequences
					 * in it.
					 *
					 * @param whole_sequence The whole sequence to be identified.
					 * @param step The step which is used to identify a specific sequence element.
					 * @return
					 */
					virtual std::vector<std::shared_ptr<laban_sequence> > find_submatches(
							std::shared_ptr<laban_sequence> whole_sequence, int step);

					/**
					 * Returns all children.
					 *
					 * @return The children.
					 */
					virtual std::vector<std::shared_ptr<decision_node> > get_children();

					/**
					 * Returns the attached sequences which are those that begin with the assigned movement.
					 * @return
					 */
					virtual std::vector<std::shared_ptr<laban_sequence> > get_sequences();

					/**
					 * Returns the item which is used to decide.
					 *
					 * @return The decision item.
					 */
					virtual std::shared_ptr<i_movement> get_decision_item();

					/**
					 * Returns true if this node is a leaf.
					 *
					 * @return True if leaf.
					 */
					virtual bool is_leaf();

					/**
					 * Returns the string representation for this node.
					 *
					 * @param indent The indent to be applied.
					 * @return The string.
					 */
					virtual std::string str(int indent);

				private:
					int body_part_;

					std::shared_ptr<i_decision_maker> decision_maker_;

					std::shared_ptr<i_movement> decision_item_;

					std::vector<std::shared_ptr<decision_node> > children_;
					std::vector<std::shared_ptr<laban_sequence> > sequences_;

			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // DECISION_NODE_HPP_
