/*
 * room_direction.cpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#include "room_direction.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			room_direction::room_direction(unsigned int measure, double beat, std::shared_ptr<mv::pin> direction)
			{
				measure_ = measure;
				beat_ = beat;
				direction_ = direction;

				if (beat < 0)
				{
					throw std::invalid_argument("Beat must not be negative.");
				}

				if (direction == nullptr)
				{
					throw std::invalid_argument("Direction must not be null.");
				}

			}

			room_direction::~room_direction()
			{
			}

			int room_direction::get_column() const
			{
				return 0;
			}

			unsigned int room_direction::get_measure() const
			{
				return measure_;
			}

			double room_direction::get_beat() const
			{
				return beat_;
			}

			double room_direction::get_duration() const
			{
				return 0;
			}

			std::shared_ptr<mv::pin> room_direction::get_direction() const
			{
				return direction_;
			}

			bool room_direction::equals(std::shared_ptr<i_movement> a) const
			{
				return (measure_ == a->get_measure() && beat_ == a->get_beat() && symbol_equals(a));
			}

			bool room_direction::symbol_equals(std::shared_ptr<i_movement> a) const
			{
				if (std::shared_ptr<room_direction> a_rd = std::dynamic_pointer_cast<room_direction>(a))
				{
					return (a_rd->get_direction()->equals(direction_));
				}
				else
				{
					return false;
				}
			}

			std::string room_direction::xml(unsigned int indent, std::string namesp) const
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

				sstr << std::fixed << std::setprecision(2);

				//print turn symbol
				sstr << indent_stream.str() << "<" << ns << "roomDirection>" << std::endl;

				sstr << indent_stream.str() << "\t" << "<" << ns << "measure>" << measure_ << "</" << ns << "measure>"
						<< std::endl;
				sstr << indent_stream.str() << "\t" << "<" << ns << "beat>" << beat_ << "</" << ns << "beat>"
						<< std::endl;
				sstr << direction_->xml(indent + 1, namesp);

				sstr << indent_stream.str() << "</" << ns << "roomDirection>" << std::endl;

				return sstr.str();

			}

			std::string room_direction::svg(unsigned int im_width, unsigned int im_height, unsigned int max_column, unsigned int measures, unsigned int beats_per_measure) const
			{
				std::stringstream id_sstr;
				id_sstr << "room_direction-" << measure_ << "-" << beat_ ;
				std::string identifier = id_sstr.str();

				std::stringstream sstr;

				int total_beats = (measures + 1) * beats_per_measure;
				double column_width = (im_width)/(max_column * 2.0);
				double beat_height = (im_height*(0.85 - 0.01)) / total_beats;

				double draw_w = column_width / 2.0;
				double draw_x_pos = (im_width / 2.0) + ((-max_column - (-0.5) - 0.25)*column_width);

				double draw_y_pos = 0;
				double draw_h = 0;

				if (measure_ != 0)
				{
					draw_y_pos = im_height*(0.85 - 0.01) - (measure_ * beats_per_measure + beat_) * beat_height - draw_h;
					draw_h = draw_w;
				}
				else
				{
					draw_h = draw_w;
					draw_y_pos = im_height*(0.85) - (measure_ * beats_per_measure + beat_
						+ beats_per_measure/2.0) * beat_height - draw_h;
				}

				//draw rect
				sstr << "\t\t<rect" << std::endl;
		        sstr << "\t\t\twidth=\"" << 2*draw_w/3.0 <<  "\"" << std::endl;
		        sstr << "\t\t\theight=\"" << 2*draw_h/3.0 <<  "\"" << std::endl;
		        sstr << "\t\t\tx=\"" << draw_x_pos+draw_w/6.0 <<  "\"" << std::endl;
		        sstr << "\t\t\ty=\"" << draw_y_pos+draw_h/6.0 <<  "\"" << std::endl;
		        sstr << "\t\t\tid=\"" << identifier << "-rect\"" << std::endl;
				sstr << "\t\t\tstyle=\"fill:#ffffff;fill-opacity:1;stroke:#000000;stroke-width:2pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none";
				sstr << "\" />" << std::endl;

				sstr << direction_->svg(identifier, draw_x_pos, draw_y_pos, draw_w, draw_h, true);

				return sstr.str();
			}

			std::shared_ptr<i_movement> room_direction::recreate(std::map<int, int> column_mapping,
					unsigned int measure, double beat, double duration) const
			{
				std::shared_ptr<i_movement> result;

				result = std::shared_ptr<i_movement>(new room_direction(measure, beat, direction_));

				return result;
			}

			std::string room_direction::str() const
			{
				std::stringstream sstr;

				sstr << "(ROOM_DIRECTION)";

				return sstr.str();
			}

		} // namespace laban
	} // namespace fl
} // namespace mae
