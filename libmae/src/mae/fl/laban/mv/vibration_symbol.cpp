/*
 * vibration_symbol.cpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#include "vibration_symbol.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				vibration_symbol::vibration_symbol(std::shared_ptr<pin> displacement1,
						std::shared_ptr<pin> displacement2, std::shared_ptr<i_dynamics_sign> dynamics)
				{
					displacement1_ = displacement1;
					displacement2_ = displacement2;

					dynamics_ = dynamics;

					if (displacement1 == nullptr || displacement2 == nullptr)
					{
						throw std::invalid_argument("Displacements must not be null");
					}

				}

				vibration_symbol::~vibration_symbol()
				{
				}

				std::shared_ptr<i_dynamics_sign> vibration_symbol::get_dynamics() const
				{
					return dynamics_;
				}

				std::shared_ptr<pin> vibration_symbol::get_displacement1() const
				{
					return displacement1_;
				}

				std::shared_ptr<pin> vibration_symbol::get_displacement2() const
				{
					return displacement2_;
				}

				bool vibration_symbol::equals(std::shared_ptr<i_symbol> a) const
				{
					if (std::shared_ptr<vibration_symbol> a_vib = std::dynamic_pointer_cast<vibration_symbol>(a))
					{
						//check dynamics sign
						if ((dynamics_ != nullptr && dynamics_->equals(a_vib->get_dynamics()))
								|| (dynamics_ == nullptr && a_vib->get_dynamics() == nullptr))
						{
							//check space measurement
							if ((displacement1_->equals(a_vib->get_displacement1())
									&& displacement2_->equals(a_vib->get_displacement2()))
									|| (displacement1_->equals(a_vib->get_displacement2())
											&& displacement2_->equals(a_vib->get_displacement1())))
							{
								return true;
							}
						}
					}

					return false;
				}

				std::string vibration_symbol::xml(unsigned int indent, std::string namesp) const
				{
					std::stringstream indent_stream;

					for (unsigned int i = 0; i < indent; i++)
					{
						indent_stream << "\t";
					}

					std::string ns = namesp;
					if (ns.size() > 0 && ns.at(ns.size() - 1) != ':')
					{
						ns.push_back(':');
					}

					std::stringstream sstr;

					//print vibration symbol
					sstr << indent_stream.str() << "<" << ns << "vibration>" << std::endl;

					if (dynamics_ != nullptr)
					{
						sstr << dynamics_->xml(indent + 1, namesp);
					}

					//print displacements
					sstr << indent_stream.str() << "\t" << "<" << ns << "displacement>" << std::endl;
					sstr << displacement1_->xml(indent + 1, namesp);
					sstr << indent_stream.str() << "\t" << "</" << ns << "displacement>" << std::endl;

					sstr << indent_stream.str() << "\t" << "<" << ns << "displacement>" << std::endl;
					sstr << displacement2_->xml(indent + 1, namesp);
					sstr << indent_stream.str() << "\t" << "</" << ns << "displacement>" << std::endl;

					sstr << indent_stream.str() << "</" << ns << "vibration>" << std::endl;

					return sstr.str();

				}

				std::string vibration_symbol::svg(std::string identifier, double posx, double posy, double width, double height, bool left) const
				{
					std::stringstream sstr;

					//TODO

					return sstr.str();
				}

				std::string vibration_symbol::str() const
				{
					std::stringstream sstr;

					sstr << "(VIBRATION)";

					return sstr.str();
				}

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
