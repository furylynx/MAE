/*
 * path.cpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#include "path.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			path::path(e_path_type type, unsigned int measure, double beat, double duration)
			{
				type_ = type;
				measure_ = measure;
				beat_ = beat;
				duration_ = duration;

				if (beat < 0 || duration < 0)
				{
					throw std::invalid_argument("Beat and duration must not be negative.");
				}
			}

			path::~path()
			{
			}

			e_path_type path::get_type()
			{
				return type_;
			}

			int path::get_column()
			{
				return 0;
			}

			unsigned int path::get_measure()
			{
				return measure_;
			}

			double path::get_beat()
			{
				return beat_;
			}

			double path::get_duration()
			{
				return duration_;
			}

			std::string path::xml(unsigned int indent, std::string namesp)
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

				//set fixed decimals and precision
				sstr << std::fixed << std::setprecision(2);

				//print path
				sstr << indent_stream.str() << "<" << ns << "path>" << std::endl;

				sstr << indent_stream.str() << "\t" << "<" << ns << "type>" << e_path_type_c::str(type_) << "</" << ns << "type>" << std::endl;
				sstr << indent_stream.str() << "\t" << "<" << ns << "measure>" << measure_ << "</" << ns << "measure>" << std::endl;
				sstr << indent_stream.str() << "\t" << "<" << ns << "beat>" << beat_ << "</" << ns << "beat>" << std::endl;
				sstr << indent_stream.str() << "\t" << "<" << ns << "duration>" << duration_ << "</" << ns << "duration>" << std::endl;

				sstr << indent_stream.str() << "</" << ns << "path>" << std::endl;

				return sstr.str();

			}

			std::string path::str() const
			{
				std::stringstream sstr;

				sstr << "(" << e_path_type_c::str(type_) << ")";

				return sstr.str();
			}

		} // namespace laban
	} // namespace fl
} // namespace mae
