#ifndef MAE_FL_LABAN_DECISION_TREE_HPP_
#define MAE_FL_LABAN_DECISION_TREE_HPP_

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
					 * Returns true if the sequence is empty (meaning the not root is assigned
					 * or the whole tree contains no elements).
					 *
					 * @return True if empty.
					 */
					virtual bool is_empty();

					/**
					 * Adds a sequences to the tree. This may introduce new nodes to the tree.
					 *
					 * @param sequence The sequence to be registered.
					 * @param reverse_order True if sequence shall be inserted in reverse order.
					 */
					virtual void add_sequence(std::shared_ptr<decision_value<T, U> > dec_val, bool reverse_order = false);

					/**
					 * Returns all registered values of the tree.
					 *
					 * @return The values.
					 */
					virtual std::vector<std::shared_ptr<decision_value<T, U> > > get_all_values();

					/**
					 * Removes all decision values where the value element is the given one. Equality is checked
					 * by the pointer.
					 *
					 * @param value The value.
					 * @return True if any removal was done.
					 */
					virtual bool remove_where(std::shared_ptr<U> value);

					/**
					 * Removes all entries for the decision value in the tree.
					 *
					 * @param dec_val The decision item.
					 * @return True if any removal was done.
					 */
					virtual bool remove_where(std::shared_ptr<decision_value<T,U> > dec_val);

					/**
					 * Searches the tree for all subsequences that match the decisions. The decision maker is checked for
					 * enough distance between a subsequence and the next element.
					 *
					 * @param whole_sequence The whole sequence which is meant to be looked up for matches with the registered sequences.
					 * @param start_pos The start position.
					 * @param end_pos The last position to be matched. -1 for last element of whole sequence.
					 * @param reverse_order The order in which the submatches are searched.
					 * @return All matches.
					 */
					virtual std::vector<std::shared_ptr<decision_value<T, U> > > find_submatches(
							std::vector<std::shared_ptr<T> > whole_sequence, int start_pos = 0, int end_pos = -1, bool reverse_order = false);

					/**
					 * Finds exact matches of the given sequence starting at the given position. The order of the
					 * sequence must be of the same order as the added sequences.
					 *
					 * @param sequence The sequence.
					 * @param start_pos The start position.
					 * @param end_pos The last position to be matched. -1 for last element of whole sequence.
					 * @return All matches.
					 */
					virtual std::vector<std::shared_ptr<decision_value<T, U> > > find_matches(std::vector<std::shared_ptr<T> > sequence,
							int start_pos = 0, int end_pos = -1);

					/**
					 * Returns true if the root element matches the given item.
					 *
					 * @param item The item to be compared using the decision maker.
					 * @return True if matching.
					 */
					virtual bool is_root_matching(std::shared_ptr<T> item) const;

					/**
					 * Returns true if the root element matches the given item for a insertion.
					 *
					 * @param item The item to be compared using the decision maker.
					 * @return True if matching.
					 */
					virtual bool is_root_insertion_matching(std::shared_ptr<T> item) const;

					/**
					 * Returns the string representation for this tree.
					 * @return The string.
					 */
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
			bool decision_tree<T, U>::is_empty()
			{
				if (root_ == nullptr || get_all_values().size() == 0)
				{
					return true;
				}

				return false;
			}

			template<typename T, typename U>
			void decision_tree<T, U>::add_sequence(std::shared_ptr<decision_value<T, U> > dec_val, bool reverse_order)
			{
				std::shared_ptr<T> first_item;

				if (reverse_order)
				{
					first_item = dec_val->get_sequence().back();
				}
				else
				{
					first_item = dec_val->get_sequence().front();
				}

				if (root_ == nullptr)
				{
					root_ = std::shared_ptr<decision_node<T, U> >(new decision_node<T, U>(decision_maker_, first_item));

					root_->add_sequence(dec_val, 0, reverse_order);
				}
				else
				{
					if (root_->is_matching(first_item, nullptr, nullptr))
					{
						root_->add_sequence(dec_val, 0, reverse_order);
					}
					else
					{
						throw std::invalid_argument(
								"Root does not match the first element. Therefore the sequence cannot be added.");
					}
				}
			}

			template<typename T, typename U>
			std::vector<std::shared_ptr<decision_value<T, U> > > decision_tree<T, U>::get_all_values()
			{
				return root_->get_all_values();
			}

			template<typename T, typename U>
			bool decision_tree<T, U>::remove_where(std::shared_ptr<U> value)
			{
				bool result = root_->remove_where(value);

				if (root_->is_empty_leaf())
				{
					root_ = nullptr;
				}

				return result;
			}

			template<typename T, typename U>
			bool decision_tree<T, U>::remove_where(std::shared_ptr<decision_value<T,U> > dec_val)
			{
				bool result = root_->remove_where(dec_val);

				if (root_->is_empty_leaf())
				{
					root_ = nullptr;
				}

				return result;
			}

			template<typename T, typename U>
			std::vector<std::shared_ptr<decision_value<T, U> > > decision_tree<T, U>::find_submatches(
					std::vector<std::shared_ptr<T> > whole_sequence, int start_pos, int end_pos, bool reverse_order)
			{
				if (root_ == nullptr || whole_sequence.size() == 0)
				{
					return std::vector<std::shared_ptr<decision_value<T, U> > >();
				}
				else
				{
					if ((!reverse_order && !(root_->is_matching(whole_sequence.at(start_pos), nullptr, nullptr, false))) || (reverse_order && !(root_->is_matching(whole_sequence.at(whole_sequence.size() - 1 - start_pos), nullptr, nullptr, false))))
					{
						//root does not match the sequence, return empty vector
						return std::vector<std::shared_ptr<decision_value<T, U> > >();
					}
					else
					{
						return root_->find_submatches(whole_sequence, start_pos, end_pos, reverse_order);
					}
				}
			}

			template<typename T, typename U>
			std::vector<std::shared_ptr<decision_value<T, U> > > decision_tree<T, U>::find_matches(
					std::vector<std::shared_ptr<T> > sequence, int start_pos, int end_pos)
			{
				if (root_ == nullptr || !root_->is_matching(sequence.back(), nullptr, nullptr))
				{
					return std::vector<std::shared_ptr<decision_value<T, U> > >();
				}
				else
				{
					return root_->find_matches(sequence, start_pos, end_pos);
				}
			}

			template<typename T, typename U>
			bool decision_tree<T, U>::is_root_matching(std::shared_ptr<T> item) const {
				return decision_maker_->decide_match(item, nullptr, root_->get_decision_item(), nullptr);
			}

			template<typename T, typename U>
			bool decision_tree<T, U>::is_root_insertion_matching(std::shared_ptr<T> item) const {
				return decision_maker_->decide_insertion(item, nullptr, root_->get_decision_item(), nullptr);
			}



			template<typename T, typename U>
			std::string decision_tree<T, U>::str()
			{
				std::stringstream sstr;

				sstr << "--TREE--" << std::endl;

				sstr << root_->str();

				sstr << "--/TREE/--" << std::endl;

				return sstr.str();
			}

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_DECISION_TREE_HPP_
