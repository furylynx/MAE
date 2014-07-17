/*
 * default_limb.cpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#include "default_limb.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{

				default_limb::default_limb(e_limb limb)
				{
					limb_ = limb;

					if (limb_ == e_limb::NONE)
					{
						throw std::invalid_argument("NONE is not allowed for a default limb.");
					}
				}

				default_limb::~default_limb()
				{
				}

				e_limb default_limb::get_limb()
				{
					return limb_;
				}

				std::string default_limb::xml(unsigned int indent, std::string namesp)
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
					sstr << indent_stream.str() << "<" << ns << "limb>" << std::endl;

					//default
					sstr << indent_stream.str() << "\t" << "<" << ns << "default>" << std::endl;

					//print limb
					sstr << indent_stream.str() << "\t\t" << "<" << ns << "limb>" << e_limb_c::str(limb_) << "</" << ns << "limb>"
							<< std::endl;

					sstr << indent_stream.str() << "\t" << "</" << ns << "default>" << std::endl;

					sstr << indent_stream.str() << "</" << ns << "limb>" << std::endl;

					return sstr.str();
				}

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae
