#include "pin.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				pin::pin(e_level level, int horizontal)
				{
					level_ = level;
					horizontal_ = horizontal;

					if (level == e_level::NONE_LEVEL)
					{
						throw std::invalid_argument("Level must not be NONE.");
					}

					if (horizontal < -1 || horizontal > 360)
					{
						throw std::invalid_argument("Horizontal must be a value between -1 and 360.");
					}
				}

				pin::~pin()
				{
				}

				e_level pin::get_level() const
				{
					return level_;
				}

				int pin::get_horizontal() const
				{
					return horizontal_;
				}

				bool pin::equals(std::shared_ptr<i_degree_sign> a) const
				{
					if (std::shared_ptr<pin> a_pin = std::dynamic_pointer_cast<pin>(a))
					{
						if (a_pin->get_horizontal() == horizontal_ && a_pin->get_level() == level_)
						{
							return true;
						}
					}

					return false;
				}

				bool pin::all_types_equal(std::shared_ptr<i_degree_sign> a) const
				{
					if (std::shared_ptr<pin> a_pin = std::dynamic_pointer_cast<pin>(a))
					{
						return true;
					}

					return false;
				}

				std::vector<double> pin::feature_vector(double hierarchy_factor) const
				{
					std::vector<double> result;

					result.push_back(hierarchy_factor * e_level_c::to_int(level_) / (double) e_level_c::max());
					result.push_back(hierarchy_factor * horizontal_ / (double) 360);

					return result;
				}

				    std::vector<std::type_index> pin::get_type_path() const
				{
					std::vector<std::type_index> result;
					result.push_back(std::type_index(typeid(mae::fl::laban::mv::i_degree_sign)));
					result.push_back(std::type_index(typeid(mae::fl::laban::mv::pin)));
					return result;
				}

				std::string pin::xml(unsigned int indent, std::string namesp, bool print_type) const
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

					//print pin

					if (print_type)
					{
						sstr << indent_stream.str() << "<" << ns << "quantitative>" << std::endl;
						sstr << indent_stream.str() << "\t<" << ns << "vertical>" << e_level_c::str(level_) << "</"
								<< ns << "vertical>" << std::endl;
						sstr << indent_stream.str() << "\t<" << ns << "horizontal>" << horizontal_ << "</" << ns
								<< "horizontal>" << std::endl;
						sstr << indent_stream.str() << "</" << ns << "quantitative>" << std::endl;
					}
					else
					{
						sstr << indent_stream.str() << "<" << ns << "vertical>" << e_level_c::str(level_) << "</" << ns
								<< "vertical>" << std::endl;
						sstr << indent_stream.str() << "<" << ns << "horizontal>" << horizontal_ << "</" << ns
								<< "horizontal>" << std::endl;
					}

					return sstr.str();

				}

				std::string pin::svg(std::string identifier, double posx, double posy, double width, double height, bool left) const
				{
					return svg(identifier, draw_rect(posx, posy, width, height), left);
				}

				std::string pin::svg(std::string identifier, draw_rect rect, bool left, svg_style style) const
				{
					double posx = rect.get_posx();
					double posy = rect.get_posy();
					double width = rect.get_width();
					double height = rect.get_height();

					if (level_ == e_level::NONE_LEVEL)
					{
						return "";
					}

					std::stringstream sstr;

					int ah = 270;

					if (horizontal_ >= 0)
					{
						ah = ((int) (horizontal_ / 45.0)) * 45;
					}
					double c = std::cos((ah / 360.0) * M_PI * 2);
					double s = std::sin((ah / 360.0) * M_PI * 2);

					//draw line
					if (horizontal_ >= 0)
					{
						sstr << "\t<path d=\"m " << posx + width / 2.0 << "," << posy + height / 2.0 << " "
								<< (height / 2.0 * s) << "," << -height / 2.0 * c << "\" id=\"" << identifier
								<< "-pindir\"" << std::endl;
						sstr
								<< "\t\t style=\"fill:none;stroke:#" << style.get_draw_color() << ";stroke-width:" << style.get_reduced_stroke_width() << "pt;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\" />"
								<< std::endl;
					}
					else
					{
						sstr << "\t<path d=\"m " << posx << "," << posy + height / 2.0 << " "
								<< width << "," << 0 << "\" id=\"" << identifier
								<< "-pindir\"" << std::endl;
						sstr
								<< "\t\t style=\"fill:none;stroke:#" << style.get_draw_color() << ";stroke-width:" << style.get_reduced_stroke_width() << "pt;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\" />"
								<< std::endl;
					}

					//draw bullet or segment
					if (level_ == e_level::HIGH || level_ == e_level::LOW)
					{
						//draw bullet
                        double radius = (width / 12.0);
						sstr << "\t\t<path" << std::endl;
						sstr << "\t\t\td=\"m " << posx + width / 2.0 + radius << "," << posy + height / 2.0
								<< " a " << radius << "," << radius << " 0 1 1 -" << 2*radius << ",0 "
								<< radius << "," << radius << " 0 1 1 " << 2*radius << ",0 z\""
								<< std::endl;
						sstr << "\t\t\tid=\"" << identifier << "-circle\"" << std::endl;

						if (level_ == e_level::HIGH)
						{
							sstr
									<< "\t\t\tstyle=\"fill:#" << style.get_fill_color() << ";fill-opacity:1;stroke:#" << style.get_draw_color() << ";stroke-width:" << style.get_reduced_stroke_width() << "pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />"
									<< std::endl;
						}
						else
						{
							sstr
									<< "\t\t\tstyle=\"fill:#" << style.get_draw_color() << ";fill-opacity:1;stroke:#" << style.get_draw_color() << ";stroke-width:" << style.get_reduced_stroke_width() << "pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />"
									<< std::endl;
						}
					}
					else
					{
						//draw segment
						double c90 = std::cos(((ah + 90) / 360.0) * M_PI * 2);
						double s90 = std::sin(((ah + 90) / 360.0) * M_PI * 2);
						double c270 = std::cos(((ah + 270) / 360.0) * M_PI * 2);
						double s270 = std::sin(((ah + 270) / 360.0) * M_PI * 2);

						sstr << "\t<path d=\"m " << posx + width / 2.0 + height / 6.0 * s270 << ","
								<< posy + height / 2.0 - height / 6.0 * c270 << " " << (height / 3.0 * s90) << ","
								<< -height / 3.0 * c90 << "\" id=\"" << identifier << "-segment\"" << std::endl;
						sstr
								<< "\t\t style=\"fill:none;stroke:#" << style.get_draw_color() << ";stroke-width:" << style.get_reduced_stroke_width() << "pt;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\" />"
								<< std::endl;
					}

					return sstr.str();
				}

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
