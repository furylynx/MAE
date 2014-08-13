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

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			//T: decision item
			//U: treasure item
			template <typename T, typename U>
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
					virtual void add_sequence(std::shared_ptr<decision_value<T,U> > decision_value, int step);

					virtual std::vector<std::shared_ptr<decision_value<T, U> > > get_all_values();

					/**
					 * Finds matches of subsequences in the whole sequence. This means that the
					 * whole sequences is looked up for having some of the registered sequences
					 * in it.
					 *
					 * @param whole_sequence The whole sequence to be identified.
					 * @param step The step which is used to identify a specific sequence element.
					 * @return
					 */
					virtual std::vector<std::shared_ptr<decision_value<T, U> > >  find_submatches(std::vector<std::shared_ptr<T> > whole_sequence, int step);

					virtual std::vector<std::shared_ptr<decision_value<T, U> > >  find_matches(std::vector<std::shared_ptr<T> > sequence, int step);


					/**
					 * Returns all children.
					 *
					 * @return The children.
					 */
					virtual std::vector<std::shared_ptr<decision_node<T, U> > > get_children();

					virtual std::shared_ptr<decision_node<T, U> > get_matching_child(std::shared_ptr<T> decision_item);

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

					virtual bool is_matching(std::shared_ptr<T> decision_item);

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
					virtual std::string str(int indent = 0);

				private:
					std::shared_ptr<i_decision_maker<T> > decision_maker_;

					std::shared_ptr<T> decision_item_;

					std::vector<std::shared_ptr<decision_node<T,U> > > children_;
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

			template <typename T, typename U>
			decision_node<T,U>::decision_node(std::shared_ptr<i_decision_maker<T> > decision_maker,
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

			template <typename T, typename U>
			decision_node<T,U>::~decision_node()
			{
			}

			template <typename T, typename U>
			void decision_node<T,U>::add_sequence(std::shared_ptr<decision_value<T,U> > decision_value, int step)
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
					std::shared_ptr<decision_node<T, U> > matching_child = get_matching_child(sequence.at(sequence.size()  - 1 - (step + 1)));
					if (matching_child != nullptr)
					{
						matching_child->add_sequence(decision_value, step + 1);
					}
					else
					{
						//no child had a match, therefore a new child has to be added
						children_.push_back(
								std::shared_ptr<decision_node<T,U> >(
										new decision_node(decision_maker_,
												sequence.at(sequence.size() - 1 - (step + 1)))));
						children_.back()->add_sequence(decision_value, step + 1);
					}
				}

			}

			template <typename T, typename U>
			std::vector<std::shared_ptr<decision_value<T, U> > > decision_node<T,U>::get_all_values()
			{
				std::vector<std::shared_ptr<decision_value<T, U> > > result = values_;

				for (unsigned int i = 0; i < children_.size(); i++)
				{
					std::vector<std::shared_ptr<decision_value<T, U> > > tmp = children_.at(i)->get_all_values();
					result.insert(result.end(), tmp.begin(), tmp.end());
				}

				return result;
			}

			template <typename T, typename U>
			std::vector<std::shared_ptr<decision_value<T, U> > > decision_node<T,U>::find_submatches(
					std::vector<std::shared_ptr<T> > whole_sequence, int step)
			{
				//all treasures that are given by submatches for the whole sequence
				std::vector<std::shared_ptr<decision_value<T, U> > > result;

				if (!is_leaf())
				{
					if (step != whole_sequence.size() -1)
					{
						std::shared_ptr<decision_node<T, U> > matching_child = get_matching_child(whole_sequence.at(whole_sequence.size() - 1 - (step + 1)));

						if (matching_child != nullptr)
						{
							result = matching_child->find_submatches(whole_sequence, step + 1);
						}
					}
				}

				//TODO dont just insert, but check the whole sequence for no further occurences before the end
				//of the to be returned sequences. The end is given by the position (measure, beat) of the last
				//processed element (the decision element of the leaf node)

				result.insert(result.end(), values_.begin(), values_.end());

				return result;
			}

			template <typename T, typename U>
			std::vector<std::shared_ptr<decision_value<T, U> > >  decision_node<T,U>::find_matches(std::vector<std::shared_ptr<T> > sequence, int step)
			{
				if (step == sequence.size() - 1)
				{
					return values_;
				}
				else{
					//all treasures that are given by submatches for the whole sequence
					std::vector<std::shared_ptr<U> > result;

					if (!is_leaf())
					{
						if (step != sequence.size() -1)
						{
							std::shared_ptr<decision_node<T, U> > matching_child = get_matching_child(sequence.at(sequence.size() - 1 - (step + 1)));

							if (matching_child != nullptr)
							{
								return matching_child->find_matches(sequence, step + 1);
							}
						}
					}

					//return empty vector
					return std::vector<std::shared_ptr<decision_value<T, U> > >();
				}
			}


			template <typename T, typename U>
			std::shared_ptr<T> decision_node<T,U>::get_decision_item()
			{
				return decision_item_;
			}

			template <typename T, typename U>
			std::vector<std::shared_ptr<decision_node<T,U> > > decision_node<T,U>::get_children()
			{
				return children_;
			}

			template <typename T, typename U>
			std::shared_ptr<decision_node<T, U> > decision_node<T,U>::get_matching_child(std::shared_ptr<T> decision_item)
			{
				for (unsigned int i = 0; i < children_.size(); i++)
				{
					if (children_.at(i)->is_matching(decision_item))
					{
						return children_.at(i);
					}
				}

				return nullptr;
			}

			template <typename T, typename U>
			std::vector<std::shared_ptr<decision_value<T, U> > > decision_node<T,U>::get_node_values()
			{
				return values_;
			}

			template <typename T, typename U>
			bool decision_node<T,U>::is_matching(std::shared_ptr<T> decision_item)
			{
				return decision_maker_->decide(decision_item_, decision_item);
			}

			template <typename T, typename U>
			bool decision_node<T,U>::is_leaf()
			{
				return children_.size() == 0;
			}

			template <typename T, typename U>
			std::string decision_node<T,U>::str(int indent)
			{
				std::stringstream sstr;

				for (unsigned int i = 0; i < indent; i++)
				{
					sstr << "\t";
				}

				sstr << "decision node : ";

//				if (sequences_.size() > 0)
//				{
//					sstr << " sequences : ";
//
//					for (unsigned int i = 0; i < sequences_.size(); i++)
//					{
//						sstr << sequences_.at(i)->get_title() << " | ";
//					}
//				}

				//TODO add decision item -> str method in i_movement...

				sstr << std::endl;

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
