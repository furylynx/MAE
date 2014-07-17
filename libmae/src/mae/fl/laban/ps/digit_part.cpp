/*
 * digit_part.cpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#include "digit_part.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{

				digit_part::digit_part(e_digit digit, unsigned int knuckle)
				{
					digit_ = digit;
					knuckle_ = knuckle;

					if (digit == e_digit::INDEXFINGER || digit == e_digit::LITTLEFINGER
							|| digit == e_digit::MIDDLEFINGER || digit == e_digit::RINGFINGER
							|| digit == e_digit::THUMB)
					{
						if (knuckle > 4)
						{
							throw std::invalid_argument(
									"Knuckle must not be greater than 4 since a finger is addressed.");
						}
					}
					else if (digit == e_digit::NONE)
					{
						throw std::invalid_argument("Digit is set to NONE which is invalid.");
					}
					else
					{
						if (knuckle > 3)
						{
							throw std::invalid_argument("Knuckle must not be greater than 3 since a toe is addressed.");
						}
					}
				}

				digit_part::~digit_part()
				{
				}

				e_digit digit_part::get_digit()
				{
					return digit_;
				}
				unsigned int digit_part::get_knuckle()
				{
					return knuckle_;
				}

				std::string digit_part::xml(unsigned int indent, std::string namesp)
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

					//print definition
					sstr << indent_stream.str() << "<" << ns << "digit>" << std::endl;

					//print digit
					sstr << indent_stream.str() << "\t" << "<" << ns << "digit>" << e_digit_c::str(digit_) << "</" << ns << "digit>"
							<< std::endl;

					//print joint
					sstr << indent_stream.str() << "\t" << "<" << ns << "joint>" << knuckle_ << "</" << ns << "joint>" << std::endl;

					sstr << indent_stream.str() << "</" << ns << "digit>" << std::endl;

					return sstr.str();
				}

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae
