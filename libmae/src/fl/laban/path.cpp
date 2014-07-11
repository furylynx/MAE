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

			std::string path::xml(unsigned int indent)
			{
				std::stringstream indent_stream;

				for (unsigned int i = 0; i < indent; i++)
				{
					indent_stream << "\t";
				}

				std::stringstream sstr;

				//set fixed decimals and precision
				sstr << std::fixed << std::setprecision(2);

				//print path
				sstr << indent_stream.str() << "<path>" << std::endl;

				sstr << indent_stream.str() << "\t" << "<type>" << e_path_type_str::str(type_) << "</type>" << std::endl;
				sstr << indent_stream.str() << "\t" << "<measure>" << measure_ << "</measure>" << std::endl;
				sstr << indent_stream.str() << "\t" << "<beat>" << beat_ << "</beat>" << std::endl;
				sstr << indent_stream.str() << "\t" << "<duration>" << duration_ << "</duration>" << std::endl;

				sstr << indent_stream.str() << "</path>" << std::endl;

				return sstr.str();

			}


		} // namespace laban
	} // namespace fl
} // namespace mae
