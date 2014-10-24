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

			e_path_type path::get_type() const
			{
				return type_;
			}

			int path::get_column() const
			{
				return 0;
			}

			unsigned int path::get_measure() const
			{
				return measure_;
			}

			double path::get_beat() const
			{
				return beat_;
			}

			double path::get_duration() const
			{
				return duration_;
			}

			bool path::equals(std::shared_ptr<i_movement> a) const
			{
				return (measure_ == a->get_measure() && beat_ == a->get_beat() && duration_ == a->get_duration()
						&& symbol_equals(a));
			}

			bool path::symbol_equals(std::shared_ptr<i_movement> a) const
			{
				if (std::shared_ptr<path> a_p = std::dynamic_pointer_cast<path>(a))
				{
					return (a_p->get_type() == type_);
				}
				else
				{
					return false;
				}
			}

			std::string path::xml(unsigned int indent, std::string namesp) const
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

				//set fixed decimals and precision
				sstr << std::fixed << std::setprecision(2);

				//print path
				sstr << indent_stream.str() << "<" << ns << "path>" << std::endl;

				sstr << indent_stream.str() << "\t" << "<" << ns << "type>" << e_path_type_c::str(type_) << "</" << ns
						<< "type>" << std::endl;
				sstr << indent_stream.str() << "\t" << "<" << ns << "measure>" << measure_ << "</" << ns << "measure>"
						<< std::endl;
				sstr << indent_stream.str() << "\t" << "<" << ns << "beat>" << beat_ << "</" << ns << "beat>"
						<< std::endl;
				sstr << indent_stream.str() << "\t" << "<" << ns << "duration>" << duration_ << "</" << ns
						<< "duration>" << std::endl;

				sstr << indent_stream.str() << "</" << ns << "path>" << std::endl;

				return sstr.str();

			}

			std::string path::svg(unsigned int im_width, unsigned int im_height, unsigned int max_column, unsigned int measures, unsigned int beats_per_measure) const
			{
				std::stringstream id_sstr;
				id_sstr << "path-" << measure_ << "-" << beat_ ;
				std::string identifier = id_sstr.str();

				std::stringstream sstr;

				int total_beats = (measures + 1) * beats_per_measure;
				double column_width = (im_width)/(max_column * 2.0);
				double beat_height = (im_height*(0.85 - 0.01)) / total_beats;

				double draw_w = column_width / 2.0;
				double draw_x_pos = (im_width / 2.0) + ((max_column - 0.5 - 0.25)*column_width);

				double draw_y_pos = 0;
				double draw_h = 0;

				if (measure_ != 0)
				{
					draw_y_pos = im_height*(0.85 - 0.01) - (measure_ * beats_per_measure + beat_
															+ duration_) * beat_height;
					draw_h = beat_height * duration_;
				}
				else
				{
					draw_y_pos = im_height*(0.85) - (measure_ * beats_per_measure + beat_
						+ beats_per_measure) * beat_height;
					draw_h = beat_height * beats_per_measure;
				}

				//TODO remove
				sstr << "\t\t<rect" << std::endl;
		        sstr << "\t\t\twidth=\"" << 2*draw_w/3.0 <<  "\"" << std::endl;
		        sstr << "\t\t\theight=\"" << 2*draw_h/3.0 <<  "\"" << std::endl;
		        sstr << "\t\t\tx=\"" << draw_x_pos+draw_w/6.0 <<  "\"" << std::endl;
		        sstr << "\t\t\ty=\"" << draw_y_pos+draw_h/6.0 <<  "\"" << std::endl;
		        sstr << "\t\t\tid=\"" << identifier << "-rect\"" << std::endl;
				sstr << "\t\t\tstyle=\"fill:#ffffff;fill-opacity:1;stroke:#000000;stroke-width:2pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none";
				sstr << "\" />" << std::endl;


				return sstr.str();
			}

			std::shared_ptr<i_movement> path::recreate(std::map<int, int> column_mapping, unsigned int measure,
					double beat, double duration) const
			{
				std::shared_ptr<i_movement> result;

				result = std::shared_ptr<i_movement>(new path(type_, measure, beat, duration));

				return result;
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
