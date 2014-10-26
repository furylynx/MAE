/*
 * relationship_bow.cpp
 *
 *  Created on: 22.08.2014
 *      Author: keks
 */

#include "relationship_bow.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			relationship_bow::relationship_bow(e_relationship_type type, bool grasping, bool passing, bool hold,
					unsigned int measure, double beat, std::shared_ptr<mv::relationship_endpoint> left_endpoint,
					std::shared_ptr<mv::relationship_endpoint> right_endpoint)
			{
				type_ = type;
				grasping_ = grasping;
				passing_ = passing;
				hold_ = hold;
				measure_ = measure;
				beat_ = beat;
				left_endpoint_ = left_endpoint;
				right_endpoint_ = right_endpoint;

				if (left_endpoint == nullptr || right_endpoint == nullptr)
				{
					throw std::invalid_argument("Endpoints must not be null.");
				}

				if (beat < 0)
				{
					throw std::invalid_argument("Beat must not be negative.");
				}

				if (type == e_relationship_type::NONE_RELATIONSHIP_TYPE)
				{
					throw std::invalid_argument("Type must not be NONE.");
				}

			}

			relationship_bow::~relationship_bow()
			{
			}

			e_relationship_type relationship_bow::get_type() const
			{
				return type_;
			}

			bool relationship_bow::get_grasping() const
			{
				return grasping_;
			}

			bool relationship_bow::get_passing() const
			{
				return passing_;
			}

			bool relationship_bow::get_hold() const
			{
				return hold_;
			}

			std::shared_ptr<mv::relationship_endpoint> relationship_bow::get_left_endpoint() const
			{
				return left_endpoint_;
			}

			std::shared_ptr<mv::relationship_endpoint> relationship_bow::get_right_endpoint() const
			{
				return right_endpoint_;
			}

			int relationship_bow::get_column() const
			{
				return 0;
			}

			unsigned int relationship_bow::get_measure() const
			{
				return measure_;
			}

			double relationship_bow::get_beat() const
			{
				return beat_;
			}

			double relationship_bow::get_duration() const
			{
				return 0;
			}

			bool relationship_bow::equals(std::shared_ptr<i_movement> a) const
			{
				return (measure_ == a->get_measure() && beat_ == a->get_beat() && symbol_equals(a));
			}

			bool relationship_bow::symbol_equals(std::shared_ptr<i_movement> a) const
			{
				if (std::shared_ptr<relationship_bow> a_rb = std::dynamic_pointer_cast<relationship_bow>(a))
				{
					return (a_rb->get_type() == type_ && a_rb->get_grasping() == grasping_
							&& a_rb->get_passing() == passing_ && a_rb->get_hold() == hold_
							&& a_rb->get_left_endpoint()->equals(left_endpoint_)
							&& a_rb->get_right_endpoint()->equals(right_endpoint_));
				}
				else
				{
					return false;
				}
			}

			std::string relationship_bow::xml(unsigned int indent, std::string namesp) const
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

				sstr << std::boolalpha;

				//print relationship bow
				sstr << indent_stream.str() << "<" << ns << "relationship>" << std::endl;

				sstr << indent_stream.str() << "\t" << "<" << ns << "type>" << e_relationship_type_c::str(type_) << "</"
						<< ns << "type>" << std::endl;

				sstr << indent_stream.str() << "\t" << "<" << ns << "grasping>" << grasping_ << "</" << ns
						<< "grasping>" << std::endl;

				sstr << indent_stream.str() << "\t" << "<" << ns << "passing>" << passing_ << "</" << ns << "passing>"
						<< std::endl;

				sstr << indent_stream.str() << "\t" << "<" << ns << "hold>" << hold_ << "</" << ns << "hold>"
						<< std::endl;

				sstr << indent_stream.str() << "\t" << "<" << ns << "measure>" << measure_ << "</" << ns << "measure>"
						<< std::endl;

				sstr << indent_stream.str() << "\t" << "<" << ns << "beat>" << beat_ << "</" << ns << "beat>"
						<< std::endl;

				//print endpoints
				sstr << indent_stream.str() << "\t" << "<" << ns << "endPoints>" << std::endl;

				//left endpoint
				sstr << indent_stream.str() << "\t\t" << "<" << ns << "left>" << std::endl;
				sstr << left_endpoint_->xml(indent + 3, namesp);
				sstr << indent_stream.str() << "\t\t" << "</" << ns << "left>" << std::endl;

				//right endpoint
				sstr << indent_stream.str() << "\t\t" << "<" << ns << "right>" << std::endl;
				sstr << right_endpoint_->xml(indent + 3, namesp);
				sstr << indent_stream.str() << "\t\t" << "</" << ns << "right>" << std::endl;

				sstr << indent_stream.str() << "\t" << "</" << ns << "endPoints>" << std::endl;

				sstr << indent_stream.str() << "</" << ns << "relationship>" << std::endl;

				return sstr.str();
			}

			std::string relationship_bow::svg(unsigned int im_width, unsigned int im_height, unsigned int max_column, unsigned int measures, unsigned int beats_per_measure) const
			{
				int left_end = (left_endpoint_->get_column() < right_endpoint_->get_column() )? left_endpoint_->get_column() : right_endpoint_->get_column();
				int right_end = (left_endpoint_->get_column() > right_endpoint_->get_column() )? left_endpoint_->get_column() : right_endpoint_->get_column();

				std::stringstream id_sstr;
				id_sstr << "relationship-" << left_end << "-" << right_end << "-" << measure_ << "-" << beat_ ;
				std::string identifier = id_sstr.str();

				std::stringstream sstr;

				int total_beats = (measures + 1) * beats_per_measure;
				double column_width = (im_width)/(max_column * 2.0);
				double beat_height = (im_height*(0.85 - 0.01)) / total_beats;

				double width = (im_width / 2.0) + ((right_end - (mae::math::math::sign(right_end)*0.5) + 0.25)*column_width);
				double posx = (im_width / 2.0) + ((left_end - (mae::math::math::sign(left_end)*0.5) - 0.25)*column_width);

				double posy = 0;
				double height = column_width/2.0;

				if (measure_ != 0)
				{
					posy = im_height*(0.85 - 0.01) - (measure_ * beats_per_measure + beat_) * beat_height + height;
				}
				else
				{
					posy = im_height*(0.85) - height;
				}

				double draw_hold_y = 0;
				double draw_hold_h = height/3.0;

				if (hold_)
				{
					draw_hold_y = posy;

					posy += draw_hold_h;
					height -= draw_hold_h;

					if (height < 0)
					{
						posy += height;
						height = 0.01;
					}
				}

				if (type_ == e_relationship_type::SUPPORT)
				{
					sstr << "\t\t<path" << std::endl;
					sstr << "\t\t\td=\"m " << posx << "," << posy << " " << width/3.0 << "," << height << " " << width/3.0 << "," << 0 << " " << width/3.0 << "," << -height << "\""
							<< std::endl;
					sstr << "\t\t\tid=\"" << identifier << "-line\"" << std::endl;
					sstr << "\t\t\tstyle=\"fill:none;fill-opacity:1;stroke:#000000;stroke-width:2pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none";
					sstr << "\" />" << std::endl;
				}
				else if (type_ == e_relationship_type::NEAR)
				{
					sstr << "\t\t<path" << std::endl;
					sstr << "\t\t\td=\"m " << posx+width << "," << posy << "  a " << width/2.0
							<< "," << height << " 0 1 1 -" << width << ",0 \""
							<< std::endl;
					sstr << "\t\t\tid=\"" << identifier << "-line\"" << std::endl;
					sstr << "\t\t\tstyle=\"fill:none;fill-opacity:1;stroke:#000000;stroke-width:2pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:5,10;stroke-dashoffset:0";
					sstr << "\" />" << std::endl;
				}
				else if (type_ == e_relationship_type::TOUCH)
				{
					sstr << "\t\t<path" << std::endl;
					sstr << "\t\t\td=\"m " << posx+width << "," << posy << "  a " << width/2.0
							<< "," << height << " 0 1 1 -" << width << ",0 \""
							<< std::endl;
					sstr << "\t\t\tid=\"" << identifier << "-line\"" << std::endl;
					sstr << "\t\t\tstyle=\"fill:none;fill-opacity:1;stroke:#000000;stroke-width:2pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none";
					sstr << "\" />" << std::endl;
				}
				else if (type_ == e_relationship_type::ADDRESS)
				{
					sstr << "\t\t<path" << std::endl;
					sstr << "\t\t\td=\"m " << posx << "," << posy << " " << width-height << "," << 0 << " m " << height << "," << 0 << " a " << height/2.0
							<< "," << height/2.0 << " 0 1 1 -" << height << ",0 \""
							<< std::endl;
					sstr << "\t\t\tid=\"" << identifier << "-line\"" << std::endl;
					sstr << "\t\t\tstyle=\"fill:none;fill-opacity:1;stroke:#000000;stroke-width:2pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none";
					sstr << "\" />" << std::endl;
				}


				//draw hold sign
				if (hold_)
				{
					//draw circle
					sstr << "\t\t<path" << std::endl;
					sstr << "\t\t\td=\"m " << posx + width/2.0 + draw_hold_h/2.0 << "," << draw_hold_y + draw_hold_h/2.0 << " a " << draw_hold_h/2.0 << "," << draw_hold_h/2.0 << " 0 1 1 -" << draw_hold_h << ",0 " << draw_hold_h/2.0 << "," << draw_hold_h/2.0 << " 0 1 1 " << draw_hold_h << ",0 z\"" << std::endl;
					sstr << "\t\t\tid=\"" << identifier << "-hold\"" << std::endl;
					sstr << "\t\t\tstyle=\"fill:#ffffff;fill-opacity:1;stroke:#000000;stroke-width:2pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />" << std::endl;
				}

				return sstr.str();
			}

			std::shared_ptr<i_movement> relationship_bow::recreate(std::map<int, int> column_mapping,
					unsigned int measure, double beat, double duration) const
			{
				std::shared_ptr<i_movement> result;

				result = std::shared_ptr<i_movement>(
						new relationship_bow(type_, grasping_, passing_, hold_, measure, beat,
								left_endpoint_->recreate(column_mapping), right_endpoint_->recreate(column_mapping)));

				return result;
			}

			std::string relationship_bow::str() const
			{
				std::stringstream sstr;

				sstr << "(RELATIONSHIP_BOW)";

				return sstr.str();
			}

		} // namespace laban
	} // namespace fl
} // namespace mae
