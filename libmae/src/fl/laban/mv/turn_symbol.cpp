/*
 * turn_symbol.cpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#include "turn_symbol.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				turn_symbol::turn_symbol(e_turn_direction direction, std::shared_ptr<i_dynamics_sign> dynamics,
						std::shared_ptr<i_degree_sign> degree)
				{
					direction_ = direction;

					dynamics_ = dynamics;
					degree_ = degree;

					if (direction == e_turn_direction::NONE)
					{
						throw std::invalid_argument("Direction must not be NONE.");
					}

				}

				turn_symbol::~turn_symbol()
				{
				}

				e_turn_direction turn_symbol::get_direction()
				{
					return direction_;
				}

				std::shared_ptr<i_dynamics_sign> turn_symbol::get_dynamics()
				{
					return dynamics_;
				}
				std::shared_ptr<i_degree_sign> turn_symbol::get_degree()
				{
					return degree_;
				}

				std::string turn_symbol::xml(unsigned int indent)
				{
					std::stringstream indent_stream;

					for (unsigned int i = 0; i < indent; i++)
					{
						indent_stream << "\t";
					}

					std::stringstream sstr;

					//print turn symbol
					sstr << indent_stream.str() << "<turn>" << std::endl;

					if (dynamics_ != nullptr)
					{
						sstr << dynamics_->xml(indent+1);
					}

					sstr << indent_stream.str() << "\t" << "<direction>" << e_turn_direction_str::str(direction_) << "</direction>" << std::endl;

					if (degree_ != nullptr)
					{
						sstr << degree_->xml(indent+1);
					}

					sstr << indent_stream.str() << "</turn>" << std::endl;

					return sstr.str();

				}

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
