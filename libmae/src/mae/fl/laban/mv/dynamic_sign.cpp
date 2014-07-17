/*
 * dynamics_sign.cpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#include "dynamic_sign.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				dynamic_sign::dynamic_sign(e_dynamic dynamic)
				{
					dynamic_ = dynamic;

					if (dynamic == e_dynamic::NONE)
					{
						throw std::invalid_argument("Dynamic must not be NONE.");
					}
				}

				dynamic_sign::~dynamic_sign()
				{
				}

				e_dynamic dynamic_sign::get_dynamic()
				{
					return dynamic_;
				}

				std::string dynamic_sign::xml(unsigned int indent, std::string namesp)
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

					//print accent sign
					sstr << indent_stream.str() << "<" << ns << "dynamics>" << std::endl;

					sstr << indent_stream.str() << "\t" << "<" << ns << "dynamic>" << e_dynamic_c::str(dynamic_) << "</" << ns << "dynamic>" << std::endl;

					sstr << indent_stream.str() << "</" << ns << "dynamics>" << std::endl;

					return sstr.str();
				}

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
