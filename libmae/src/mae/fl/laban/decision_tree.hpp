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

#include "decision_value.hpp"
#include "i_decision_maker.hpp"

//global includes
#include <memory>
#include <stdexcept>
#include <vector>
#include <string>

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			//T: decision item
			//U: treasure item
			template<typename T, typename U>
			class decision_tree
			{
				public:
					/**
					 * Creates a new decision tree for sequences.
					 *
					 * @param body_part The addressed body part.
					 * @param decision_maker The decision maker which is used to decide whether two sequences are equal.
					 */
					decision_tree(std::shared_ptr<i_decision_maker<T> > decision_maker);
					virtual ~decision_tree();

					/**
					 * Returns the root node if any. Returns null otherwise.
					 *
					 * @return The root element.
					 */
					virtual std::shared_ptr<decision_node<T, U> > get_root();

					/**
					 * Adds a sequences to the tree. This may introduce new nodes to the tree.
					 *
					 * @param sequence The sequence to be registered.
					 */
					virtual void add_sequence(std::shared_ptr<decision_value<T, U> > decision_value);

					virtual std::vector<std::shared_ptr<decision_value<T, U>> > get_all_values();

					/**
					 * Searches the tree for all sequences that match the motion on the given body part.
					 *
					 * @param whole_sequence The whole sequence which is meant to be looked up for matches with the registered sequences.
					 * @return All matches.
					 */
					virtual std::vector<std::shared_ptr<decision_value<T, U>> > find_submatches(
							std::vector<std::shared_ptr<T> > whole_sequence, int start_pos = 0);

					virtual std::vector<std::shared_ptr<decision_value<T, U>> > find_matches(std::vector<std::shared_ptr<T> > sequence,
							int start_pos = 0);

					virtual std::string str();


				private:
					std::shared_ptr<i_decision_maker<T> > decision_maker_;
					std::shared_ptr<decision_node<T, U> > root_;

			};

		} // namespace laban
	} // namespace fl
} // namespace mae

//------------------------------
// template implementation
//------------------------------

#include "decision_tree.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			template<typename T, typename U>
			decision_tree<T, U>::decision_tree(std::shared_ptr<i_decision_maker<T> > decision_maker)
			{
				decision_maker_ = decision_maker;

				if (decision_maker_ == nullptr)
				{
					throw std::invalid_argument("Decision maker must not be null.");
				}
			}

			template<typename T, typename U>
			decision_tree<T, U>::~decision_tree()
			{
			}

			template<typename T, typename U>
			std::shared_ptr<decision_node<T, U> > decision_tree<T, U>::get_root()
			{
				return root_;
			}

			template<typename T, typename U>
			void decision_tree<T, U>::add_sequence(std::shared_ptr<decision_value<T, U> > decision_value)
			{
				std::shared_ptr<T> back = decision_value->get_sequence().back();

				if (root_ == nullptr)
				{
					root_ = std::shared_ptr<decision_node<T, U> >(new decision_node<T, U>(decision_maker_, back));

					root_->add_sequence(decision_value, 0);
				}
				else
				{
					if (root_->is_matching(back))
					{
						root_->add_sequence(decision_value, 0);
					}
					else
					{
						throw std::invalid_argument(
								"Root does not match the first element. Therefore the sequence cannot be added.");
					}
				}
			}

			template<typename T, typename U>
			std::vector<std::shared_ptr<decision_value<T, U>> > decision_tree<T, U>::get_all_values()
			{
				return root_->get_all_values();
			}

			template<typename T, typename U>
			std::vector<std::shared_ptr<decision_value<T, U> > > decision_tree<T, U>::find_submatches(
					std::vector<std::shared_ptr<T> > whole_sequence, int start_pos)
			{
				if (root_ == nullptr || !root_->is_matching(whole_sequence.back()))
				{
					return std::vector<std::shared_ptr<decision_value<T, U> > >();
				}
				else
				{
					return root_->find_submatches(whole_sequence, start_pos);
				}
			}

			template<typename T, typename U>
			std::vector<std::shared_ptr<decision_value<T, U> > > decision_tree<T, U>::find_matches(
					std::vector<std::shared_ptr<T> > sequence, int start_pos)
			{
				if (root_ == nullptr || !root_->is_matching(sequence.back()))
				{
					return std::vector<std::shared_ptr<decision_value<T, U> > >();
				}
				else
				{
					return root_->find_matches(sequence, start_pos);
				}
			}

			template<typename T, typename U>
			std::string decision_tree<T, U>::str()
			{
				return root_->str();
			}

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // DECISION_TREE_HPP_
