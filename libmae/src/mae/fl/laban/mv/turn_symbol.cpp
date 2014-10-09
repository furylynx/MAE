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

					if (direction == e_turn_direction::NONE_TURN_DIRECTION)
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

				bool turn_symbol::equals(std::shared_ptr<i_symbol> a)
				{
					if (std::shared_ptr<turn_symbol> a_turn = std::dynamic_pointer_cast<turn_symbol>(a))
					{
						if (a_turn->get_direction() == direction_)
						{
							//check dynamics sign
							if ((dynamics_ != nullptr && dynamics_->equals(a_turn->get_dynamics()))
									|| (dynamics_ == nullptr && a_turn->get_dynamics() == nullptr))
							{
								//check degree sign
								if ((degree_ != nullptr && degree_->equals(a_turn->get_degree()))
										|| (degree_ == nullptr && a_turn->get_degree() == nullptr))
								{
									return true;
								}
							}
						}
					}

					return false;
				}

				std::string turn_symbol::xml(unsigned int indent, std::string namesp)
				{
					std::stringstream indent_stream;

					for (unsigned int i = 0; i < indent; i++)
					{
						indent_stream << "\t";
					}

					std::string ns = namesp;
					if (ns.size() > 0 && ns.at(ns.size()-1) != ':')
					{
						ns.push_back(':');
					}

					std::stringstream sstr;

					//print turn symbol
					sstr << indent_stream.str() << "<" << ns << "turn>" << std::endl;

					if (dynamics_ != nullptr)
					{
						sstr << dynamics_->xml(indent+1, namesp);
					}

					sstr << indent_stream.str() << "\t" << "<" << ns << "direction>" << e_turn_direction_c::str(direction_) << "</" << ns << "direction>" << std::endl;

					if (degree_ != nullptr)
					{
						sstr << degree_->xml(indent+1, namesp);
					}

					sstr << indent_stream.str() << "</" << ns << "turn>" << std::endl;

					return sstr.str();

				}

				std::string turn_symbol::str() const
				{
					std::stringstream sstr;

					sstr << "(" << e_turn_direction_c::str(direction_) << ")";

					return sstr.str();
				}

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
