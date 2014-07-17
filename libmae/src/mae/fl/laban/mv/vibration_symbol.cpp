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

				vibration_symbol::vibration_symbol(std::shared_ptr<pin> displacement1, std::shared_ptr<pin> displacement2, std::shared_ptr<i_dynamics_sign> dynamics)
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

				std::shared_ptr<i_dynamics_sign> vibration_symbol::get_dynamics()
				{
					return dynamics_;
				}

				std::shared_ptr<pin> vibration_symbol::get_displacement1()
				{
					return displacement1_;
				}

				std::shared_ptr<pin> vibration_symbol::get_displacement2()
				{
					return displacement2_;
				}


				std::string vibration_symbol::xml(unsigned int indent, std::string namesp)
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

					//print vibration symbol
					sstr << indent_stream.str() << "<" << ns << "vibration>" << std::endl;

					if (dynamics_ != nullptr)
					{
						sstr << dynamics_->xml(indent+1, namesp);
					}

					//print displacements
					sstr << indent_stream.str() << "\t" << "<" << ns << "displacement>" << std::endl;
					sstr << displacement1_->xml(indent+1, namesp);
					sstr << indent_stream.str() << "\t" << "</" << ns << "displacement>" << std::endl;

					sstr << indent_stream.str() << "\t" << "<" << ns << "displacement>" << std::endl;
					sstr << displacement2_->xml(indent+1, namesp);
					sstr << indent_stream.str() << "\t" << "</" << ns << "displacement>" << std::endl;

					sstr << indent_stream.str() << "</" << ns << "vibration>" << std::endl;

					return sstr.str();

				}



			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
