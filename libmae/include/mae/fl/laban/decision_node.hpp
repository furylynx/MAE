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
#include "decision_value.hpp"
#include "i_decision_maker.hpp"

//global includes
#include <memory>
#include <stdexcept>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			//T: decision item
			//U: treasure item
			template<typename T, typename U>
			class decision_node
			{
				public:
					/**
					 * Creates a decision node which is a node of the decision tree for sequences.
					 *
					 * @param decision_maker The decision maker which is used to decide whether sequence elements are equal.
					 * @param decision_item The item which is used to decide which sequence part this node matches.
					 */
					decision_node(std::shared_ptr<i_decision_maker<T> > decision_maker,
							std::shared_ptr<T> decision_item);
					virtual ~decision_node();

					/**
					 * Adds a sequence to the node. Processes the children recursively. Adds children
					 * if decision elements are missing.
					 *
					 * @param sequence The sequence to be registered. Regards only the given body part.
					 * @param step The step which is used to identify a specific sequence element.
					 */
					virtual void add_sequence(std::shared_ptr<decision_value<T, U> > decision_value, int step,
							bool reverse_order = false);

					/**
					 * Removes all decision values that have the given value.
					 *
					 * @param value The value used to decide removals.
					 * @return True if any removal was done.
					 */
					virtual bool remove_where(std::shared_ptr<U> value);

					/**
					 * Removes the given decision value from all child nodes. Uses a smart pointer comparison for equality.
					 *
					 * @param dec_val The decision value.
					 * @return True if any removal was done.
					 */
					virtual bool remove_where(std::shared_ptr<decision_value<T, U> > dec_val);

					/**
					 * Returns all registered values of the node and its children.
					 *
					 * @return All values.
					 */
					virtual std::vector<std::shared_ptr<decision_value<T, U> > > get_all_values();

					/**
					 * Finds matches of subsequences in the whole sequence. This means that the
					 * whole sequences is looked up for having some of the registered sequences
					 * in it.
					 *
					 * @param whole_sequence The whole sequence to be identified.
					 * @param step The step which is used to identify a specific sequence element.
					 * @param end_pos The last step to be matched (no matter what the search order is, this
					 * 			values must be greater or equal the step value). -1 for last element of whole
					 * 			sequence.
					 * @param reverse_order The order in which the submatches are searched.
					 * @return The submatches.
					 */
					virtual std::vector<std::shared_ptr<decision_value<T, U> > > find_submatches(
							std::vector<std::shared_ptr<T> > whole_sequence, int step, int end_pos = -1,
							bool reverse_order = false);

					/**
					 * Finds exact matches starting at the step index. The order of the sequence
					 * must be of the same order as the added sequences.
					 *
					 * @param sequence The sequence to be matched.
					 * @param step The step index defining the start position for the match in this node.
					 * @param end_pos The last position to be matched. -1 for last element of whole sequence.
					 * @return The matches.
					 */
					virtual std::vector<std::shared_ptr<decision_value<T, U> > > find_matches(
							std::vector<std::shared_ptr<T> > sequence, int step, int end_pos = -1);

					/**
					 * Returns all children.
					 *
					 * @return The children.
					 */
					virtual std::vector<std::shared_ptr<decision_node<T, U> > > get_children();

					/**
					 * Returns all children that match the decision.
					 *
					 * @param decision_item The item to be matched.
					 * @param insertion True if matching children for insertion.
					 * @return The child that matches the item.
					 */
					virtual std::vector<std::shared_ptr<decision_node<T, U> > > get_matching_children(std::shared_ptr<T> decision_item,
							std::shared_ptr<T> decision_item_predecessor, bool insertion = true);

					/**
					 * Returns the attached sequences which are those that begin with the assigned movement.
					 * @return
					 */
					virtual std::vector<std::shared_ptr<decision_value<T, U> > > get_node_values();

					/**
					 * Returns the item which is used to decide.
					 *
					 * @return The decision item.
					 */
					virtual std::shared_ptr<T> get_decision_item();

					/**
					 * Returns true if this node's decision item is matching.
					 *
					 * @param decision_item The other item (to be matched with).
					 * @param decision_item_predecessor The other item's predecessor.
					 * @param decision_item_parent This item's parent's item.
					 * @param insertion True if matching children for insertion.
					 * @return True if matching.
					 */
					virtual bool is_matching(std::shared_ptr<T> decision_item,
							std::shared_ptr<T> decision_item_predecessor, std::shared_ptr<T> decision_item_parent, bool insertion = true);

					/**
					 * Returns true if this node is a leaf.
					 *
					 * @return True if leaf.
					 */
					virtual bool is_leaf();

					/**
					 * Returns true if this node is a leaf and no values are attached.
					 *
					 * @return True if empty leaf.
					 */
					virtual bool is_empty_leaf();

					/**
					 * Returns the string representation for this node.
					 *
					 * @param indent The indent to be applied.
					 * @return The string.
					 */
					virtual std::string str(int indent = 0);

				private:
					std::shared_ptr<i_decision_maker<T> > decision_maker_;

					std::shared_ptr<T> decision_item_;

					std::vector<std::shared_ptr<decision_node<T, U> > > children_;
					std::vector<std::shared_ptr<decision_value<T, U> > > values_;

			};

		} // namespace laban
	} // namespace fl
} // namespace mae

//------------------------------
// template implementation
//------------------------------

#include "decision_node.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			template<typename T, typename U>
			decision_node<T, U>::decision_node(std::shared_ptr<i_decision_maker<T> > decision_maker,
					std::shared_ptr<T> decision_item)
			{
				decision_maker_ = decision_maker;
				decision_item_ = decision_item;

				if (decision_maker == nullptr)
				{
					throw std::invalid_argument("Decision maker must not be null.");
				}

				if (decision_item == nullptr)
				{
					throw std::invalid_argument("Decision item must not be null.");
				}
			}

			template<typename T, typename U>
			decision_node<T, U>::~decision_node()
			{
			}

			template<typename T, typename U>
			void decision_node<T, U>::add_sequence(std::shared_ptr<decision_value<T, U> > decision_value, int step,
					bool reverse_order)
			{
				std::vector<std::shared_ptr<T> > sequence = decision_value->get_sequence();

				if (step == sequence.size() - 1)
				{
					//last element in sequence
					//we can safely add the sequence, since the check for same movements is done in the parent node
					values_.push_back(decision_value);
				}
				else
				{
					//next index for normal or reverse order
					unsigned int current_index = step;
					unsigned int next_index = step + 1;
					if (reverse_order)
					{
						current_index = sequence.size() - 1 - step;
						next_index = sequence.size() - 1 - (step + 1);
					}

					std::vector<std::shared_ptr<decision_node<T, U> > > matching_children = get_matching_children(sequence.at(next_index),
							sequence.at(current_index), true);

					if (matching_children.size() > 0)
					{
						//use the first possible match to insert
						matching_children.at(0)->add_sequence(decision_value, step + 1, reverse_order);
					}
					else
					{
						//no child had a match, therefore a new child has to be added
						children_.push_back(
								std::shared_ptr<decision_node<T, U> >(
										new decision_node(decision_maker_, sequence.at(next_index))));
						children_.back()->add_sequence(decision_value, step + 1, reverse_order);
					}
				}
			}

			template<typename T, typename U>
			bool decision_node<T, U>::remove_where(std::shared_ptr<U> value)
			{
				bool result = false;

				for (unsigned int i = children_.size() - 1; i >= 0; i++)
				{
					bool child_rem = children_.at(i)->remove_where(value);

					if (child_rem)
					{
						if (children_.at(i)->is_empty_leaf())
						{
							children_.erase(children_.begin() + i);
						}

						result = true;
					}
				}

				//remove own sequences
				std::vector<int> to_remove;

				for (unsigned int i = values_.size() - 1; i >= 0; i++)
				{
					if (values_.at(i)->get_value() == value)
					{
						result = true;
						values_.erase(values_.begin() + i);
					}
				}

				return result;
			}

			template<typename T, typename U>
			bool decision_node<T, U>::remove_where(std::shared_ptr<decision_value<T, U> > dec_val)
			{
				bool result = false;

				for (unsigned int i = children_.size() - 1; i >= 0; i++)
				{
					bool child_rem = children_.at(i)->remove_where(dec_val);

					if (child_rem)
					{
						if (children_.at(i)->is_empty_leaf())
						{
							children_.erase(children_.begin() + i);
						}

						result = true;
					}
				}

				//remove own sequences
				std::vector<int> to_remove;

				for (unsigned int i = values_.size() - 1; i >= 0; i++)
				{
					if (values_.at(i) == dec_val)
					{
						result = true;
						values_.erase(values_.begin() + i);
					}
				}

				return result;
			}

			template<typename T, typename U>
			std::vector<std::shared_ptr<decision_value<T, U> > > decision_node<T, U>::get_all_values()
			{
				std::vector<std::shared_ptr<decision_value<T, U> > > result = values_;

				for (unsigned int i = 0; i < children_.size(); i++)
				{
					std::vector<std::shared_ptr<decision_value<T, U> > > tmp = children_.at(i)->get_all_values();
					result.insert(result.end(), tmp.begin(), tmp.end());
				}

				return result;
			}

			template<typename T, typename U>
			std::vector<std::shared_ptr<decision_value<T, U> > > decision_node<T, U>::find_submatches(
					std::vector<std::shared_ptr<T> > whole_sequence, int step, int end_pos, bool reverse_order)
			{
				if (end_pos < 0)
				{
					//set end_pos if not specified
					end_pos = whole_sequence.size() - 1;
				}

				//all treasures that are given by submatches for the whole sequence
				std::vector<std::shared_ptr<decision_value<T, U> > > result;

				unsigned int current_index = step;
				unsigned int next_index = step + 1;

				if (reverse_order)
				{
					//change indices for reverse order
					current_index = whole_sequence.size() - 1 - step;
					next_index = whole_sequence.size() - 1 - (step + 1);
				}

				if (!is_leaf() && step != end_pos)
				{
					//recursively search all matching children for sequences
					std::vector<std::shared_ptr<decision_node<T, U> > > matching_children = get_matching_children(
							whole_sequence.at(next_index), whole_sequence.at(current_index), false);

					for (unsigned int i= 0; i < matching_children.size(); i++)
					{
						//recurse; step is just incremented (it is not equal to the sequence element's index - this is next_index)
						std::vector<std::shared_ptr<decision_value<T, U> > > child_result = matching_children.at(i)->find_submatches(whole_sequence, step + 1, end_pos, reverse_order);
						result.insert(result.end(), child_result.begin(), child_result.end());
					}
				}

				//just insert all values for this node (since node had a match)
				for (unsigned int i = 0; i < values_.size(); i++)
				{
					result.push_back(values_.at(i));
				}

				return result;
			}

			template<typename T, typename U>
			std::vector<std::shared_ptr<decision_value<T, U> > > decision_node<T, U>::find_matches(
					std::vector<std::shared_ptr<T> > sequence, int step, int end_pos)
			{
				if (end_pos < 0)
				{
					end_pos = sequence.size() - 1;
				}

				if (step == sequence.size() - 1)
				{
					return values_;
				}
				else
				{
					//all treasures that are given by matches for the sequence
					std::vector<std::shared_ptr<decision_value<T, U> > > result;

					if (!is_leaf())
					{
						if (step != end_pos)
						{
							//recursively search all matching children for sequences - since insertion matching is equal to the exact matching
							std::vector<std::shared_ptr<decision_node<T, U> > > matching_children = get_matching_children(
									sequence.at(step + 1), sequence.at(step), true);

							for (unsigned int i= 0; i < matching_children.size(); i++)
							{
								std::vector<std::shared_ptr<decision_value<T, U> > > child_result = matching_children.at(i)->find_matches(sequence, step + 1, end_pos);
								result.insert(result.end(), child_result.begin(), child_result.end());
							}
						}
					}

					//return empty vector
					return result;
				}
			}

			template<typename T, typename U>
			std::shared_ptr<T> decision_node<T, U>::get_decision_item()
			{
				return decision_item_;
			}

			template<typename T, typename U>
			std::vector<std::shared_ptr<decision_node<T, U> > > decision_node<T, U>::get_children()
			{
				return children_;
			}

			template<typename T, typename U>
			std::vector<std::shared_ptr<decision_node<T, U> > > decision_node<T, U>::get_matching_children(
					std::shared_ptr<T> decision_item, std::shared_ptr<T> decision_item_predecessor, bool insertion)
			{
				std::vector<std::shared_ptr<decision_node<T, U> > > result;

				for (unsigned int i = 0; i < children_.size(); i++)
				{
					if (children_.at(i)->is_matching(decision_item, decision_item_predecessor, decision_item_, insertion))
					{
						result.push_back( children_.at(i) );
					}
				}

				return result;
			}

			template<typename T, typename U>
			std::vector<std::shared_ptr<decision_value<T, U> > > decision_node<T, U>::get_node_values()
			{
				return values_;
			}

			template<typename T, typename U>
			bool decision_node<T, U>::is_matching(std::shared_ptr<T> decision_item,
					std::shared_ptr<T> decision_item_predecessor, std::shared_ptr<T> decision_item_parent, bool insertion)
			{
				if (insertion)
				{
					return decision_maker_->decide_insertion(decision_item, decision_item_predecessor, decision_item_, decision_item_parent);
				}
				else
				{
					return decision_maker_->decide_match(decision_item, decision_item_predecessor, decision_item_, decision_item_parent);
				}
			}

			template<typename T, typename U>
			bool decision_node<T, U>::is_leaf()
			{
				return (children_.size() == 0);
			}

			template<typename T, typename U>
			bool decision_node<T, U>::is_empty_leaf()
			{
				return is_leaf() && values_.size() == 0;
			}

			template<typename T, typename U>
			std::string decision_node<T, U>::str(int indent)
			{
				std::stringstream sstr;

				for (unsigned int i = 0; i < indent; i++)
				{
					sstr << "\t";
				}

				sstr << "decision node : " << decision_item_ << std::endl;

				for (unsigned int j = 0; j < values_.size(); j++)
				{
					for (unsigned int i = 0; i < indent; i++)
					{
						sstr << "\t";
					}

					sstr << ">> sequence: " << values_.at(j)->get_value() << std::endl;
				}

				for (unsigned int i = 0; i < children_.size(); i++)
				{
					sstr << children_.at(i)->str(indent + 1);
				}

				return sstr.str();
			}

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // DECISION_NODE_HPP_
