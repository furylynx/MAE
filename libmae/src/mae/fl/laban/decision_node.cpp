/*
 * decision_node.cpp
 *
 *  Created on: 12.08.2014
 *      Author: keks
 */

#include "decision_node.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			decision_node::decision_node(int body_part, std::shared_ptr<i_decision_maker> decision_maker,
					std::shared_ptr<i_movement> decision_item)
			{
				body_part_ = body_part;
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

			decision_node::~decision_node()
			{
			}

			void decision_node::add_sequence(std::shared_ptr<laban_sequence> sequence, int step)
			{
				std::vector<std::shared_ptr<movement> > part_seq = sequence->get_column_movements(body_part_);

				if (step == part_seq.size() - 1)
				{
					//last element in sequence
					//we can safely add the sequence, since the check for same movements is done in the parent node
					sequences_.push_back(sequence);
				}
				else
				{
					for (unsigned int i = 0; i < children_.size(); i++)
					{
						if (decision_maker_->decide(children_.at(i)->get_decision_item(),
								part_seq.at(part_seq.size() - 1 - (step + 1))))
						{
							children_.at(i)->add_sequence(sequence, step + 1);
							return;
						}
					}

					//no child had a match, therefore a new child has to be added
					children_.push_back(
							std::shared_ptr<decision_node>(
									new decision_node(body_part_, decision_maker_,
											part_seq.at(part_seq.size() - 1 - (step + 1)))));
					children_.back()->add_sequence(sequence, step + 1);
				}

			}

			std::vector<std::shared_ptr<laban_sequence> > decision_node::find_submatches(
					std::shared_ptr<laban_sequence> whole_sequence, int step)
			{
				std::vector<std::shared_ptr<laban_sequence> > result;

				std::vector<std::shared_ptr<movement> > part_seq = whole_sequence->get_column_movements(body_part_);

				if (step == part_seq.size())
				{
					return result;
				}

				if (!is_leaf())
				{
					for (unsigned int i = 0; i < children_.size(); i++)
					{
						if (decision_maker_->decide(children_.at(i)->get_decision_item(), part_seq.at(step)))
						{
							//TODO handle substitutes
							result = children_.at(i)->find_submatches(whole_sequence, step + 1);
							break;
						}
					}
				}

				//TODO dont just insert, but check the whole sequence for no further occurences before the end
				//of the to be returned sequences

				result.insert(result.end(), sequences_.begin(), sequences_.end());

				return result;
			}

			std::shared_ptr<i_movement> decision_node::get_decision_item()
			{
				return decision_item_;
			}

			std::vector<std::shared_ptr<decision_node> > decision_node::get_children()
			{
				return children_;
			}

			std::vector<std::shared_ptr<laban_sequence> > decision_node::get_sequences()
			{
				return sequences_;
			}

			bool decision_node::is_leaf()
			{
				return children_.size() == 0;
			}

			std::string decision_node::str(int indent)
			{
				std::stringstream sstr;

				for (unsigned int i = 0; i < indent; i++)
				{
					sstr << "\t";
				}

				sstr << "decision node : ";

				if (sequences_.size() > 0)
				{
					sstr << " sequences : ";

					for (unsigned int i = 0; i < sequences_.size(); i++)
					{
						sstr << sequences_.at(i)->get_title() << " | ";
					}
				}

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
