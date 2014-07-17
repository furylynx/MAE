/*
 * prop.cpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#include "prop.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{

				prop::prop(std::string name, std::string description)
				{
					name_ = name;
					description_ = description;
				}

				prop::~prop()
				{

				}

				std::string prop::get_name()
				{
					return name_;
				}

				std::string prop::get_description()
				{
					return description_;
				}

				std::string prop::xml(unsigned int indent, std::string namesp)
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
					sstr << indent_stream.str() << "<" << ns << "preSign>" << std::endl;

					sstr << indent_stream.str() << "\t" << "<" << ns << "prop>" << std::endl;
					sstr << indent_stream.str() << "\t\t" << "<" << ns << "name>" << name_ << "</" << ns << "name>" << std::endl;
					sstr << indent_stream.str() << "\t\t" << "<" << ns << "description>" << description_ << "</" << ns << "description>" << std::endl;
					sstr << indent_stream.str() << "\t" << "</" << ns << "prop>" << std::endl;

					sstr << indent_stream.str() << "</" << ns << "preSign>" << std::endl;

					return sstr.str();
				}

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae
