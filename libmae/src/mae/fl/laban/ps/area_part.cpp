#include "area_part.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{

				area_part::area_part(e_area area)
				{
					area_ = area;
				}

				area_part::~area_part()
				{
				}

				e_area area_part::get_area() const
				{
					return area_;
				}

				std::string area_part::xml(unsigned int indent, std::string namesp) const
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

					//print side
					sstr << indent_stream.str() << "<" << ns << "part>" << e_area_c::str(area_) << "</" << ns << "part>"
							<< std::endl;

					return sstr.str();
				}

				std::string area_part::svg(std::string identifier, double posx, double posy, double width,
						double height, bool left) const
				{
					identifier.append("-areapart");

					std::stringstream sstr;

					if (width > height)
					{
						posx += (width - height) / 2.0;
						width = height;
					}
					else if (height > width)
					{
						posy += (height - width) / 2.0;
						height = width;
					}

					double circ_r = width / 3.0;

					//print rect
					if (area_ == e_area::TORSO)
					{
						circ_r = width / 6.0;

						sstr << "\t\t<rect" << std::endl;
						sstr << "\t\t\twidth=\"" << width / 2.0 << "\"" << std::endl;
						sstr << "\t\t\theight=\"" << height << "\"" << std::endl;
						sstr << "\t\t\tx=\"" << posx + width / 4.0 << "\"" << std::endl;
						sstr << "\t\t\ty=\"" << posy << "\"" << std::endl;
						sstr << "\t\t\tid=\"" << identifier << "-rect\"" << std::endl;
						sstr
								<< "\t\t\tstyle=\"fill:#ffffff;fill-opacity:1;stroke:#000000;stroke-width:2pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none";
						sstr << "\" />" << std::endl;
					}
					else
					{
						sstr << "\t\t<rect" << std::endl;
						sstr << "\t\t\twidth=\"" << width << "\"" << std::endl;
						sstr << "\t\t\theight=\"" << height << "\"" << std::endl;
						sstr << "\t\t\tx=\"" << posx << "\"" << std::endl;
						sstr << "\t\t\ty=\"" << posy << "\"" << std::endl;
						sstr << "\t\t\tid=\"" << identifier << "-rect\"" << std::endl;
						sstr
								<< "\t\t\tstyle=\"fill:#ffffff;fill-opacity:1;stroke:#000000;stroke-width:2pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none";
						sstr << "\" />" << std::endl;
					}

					if (area_ == e_area::CHEST)
					{
						//draw circle
						sstr << "\t\t<path" << std::endl;
						sstr << "\t\t\td=\"m " << posx + width / 2.0 + circ_r << "," << posy + height / 2.0 << " a "
								<< circ_r << "," << circ_r << " 0 1 1 -" << 2 * circ_r << ",0 " << circ_r << ","
								<< circ_r << " 0 1 1 " << 2 * circ_r << ",0 z\"" << std::endl;
						sstr << "\t\t\tid=\"" << identifier << "-chest\"" << std::endl;
						sstr
								<< "\t\t\tstyle=\"fill:#ffffff;fill-opacity:1;stroke:#000000;stroke-width:2pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />"
								<< std::endl;
					}
					else if (area_ == e_area::HEAD)
					{
						//draw circle
						sstr << "\t\t<path" << std::endl;
						sstr << "\t\t\td=\"m " << posx + width * 5 / 6.0 << "," << posy + height * 3 / 4.0 << " c "
								<< -width * 5 / 6.0 << "," << width / 2.0 << " " << -width * 5 / 6.0 << ","
								<< -width / 2.0 - height / 2.0 << " " << 0 << "," << -height / 2.0 << "\"" << std::endl;
						sstr << "\t\t\tid=\"" << identifier << "-head\"" << std::endl;
						sstr
								<< "\t\t\tstyle=\"fill:#ffffff;fill-opacity:1;stroke:#000000;stroke-width:2pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />"
								<< std::endl;
					}
					else if (area_ == e_area::PELVIS)
					{
						//draw circle
						sstr << "\t\t<path" << std::endl;
						sstr << "\t\t\td=\"m " << posx + width / 2.0 + circ_r << "," << posy + height / 2.0 << " a "
								<< circ_r << "," << circ_r << " 0 1 1 -" << 2 * circ_r << ",0 " << circ_r << ","
								<< circ_r << " 0 1 1 " << 2 * circ_r << ",0 z\"" << std::endl;
						sstr << "\t\t\tid=\"" << identifier << "-pelvis\"" << std::endl;
						sstr
								<< "\t\t\tstyle=\"fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />"
								<< std::endl;
					}
					else if (area_ == e_area::TORSO)
					{
						//draw circle
						sstr << "\t\t<path" << std::endl;
						sstr << "\t\t\td=\"m " << posx + width / 2.0 + circ_r << "," << posy + height / 4.0 << " a "
								<< circ_r << "," << circ_r << " 0 1 1 -" << 2 * circ_r << ",0 " << circ_r << ","
								<< circ_r << " 0 1 1 " << 2 * circ_r << ",0 z\"" << std::endl;
						sstr << "\t\t\tid=\"" << identifier << "-torso1\"" << std::endl;
						sstr
								<< "\t\t\tstyle=\"fill:#ffffff;fill-opacity:1;stroke:#000000;stroke-width:2pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />"
								<< std::endl;

						//draw circle
						sstr << "\t\t<path" << std::endl;
						sstr << "\t\t\td=\"m " << posx + width / 2.0 + circ_r << "," << posy + 3 * height / 4.0 << " a "
								<< circ_r << "," << circ_r << " 0 1 1 -" << 2 * circ_r << ",0 " << circ_r << ","
								<< circ_r << " 0 1 1 " << 2 * circ_r << ",0 z\"" << std::endl;
						sstr << "\t\t\tid=\"" << identifier << "-torso2\"" << std::endl;
						sstr
								<< "\t\t\tstyle=\"fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />"
								<< std::endl;
					}
					else if (area_ == e_area::WAIST)
					{
						sstr << "\t\t<path" << std::endl;
						sstr << "\t\t\td=\"m " << posx + width / 6.0 << "," << posy + height / 6.0 << " "
								<< width * 2 / 3.0 << "," << height * 2 / 3.0 << " m " << 0 << "," << -height * 2 / 3.0
								<< "" << -width * 2 / 3.0 << "," << height * 2 / 3.0 << "\"" << std::endl;
						sstr << "\t\t\tid=\"" << identifier << "-waist\"" << std::endl;
						sstr
								<< "\t\t\tstyle=\"fill:none;fill-opacity:1;stroke:#000000;stroke-width:2pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none";
						sstr << "\" />" << std::endl;
					}

					return sstr.str();
				}

				std::shared_ptr<i_endpoint> area_part::get_fixed_end() const
				{
					if (area_ == e_area::PELVIS)
					{
						return std::shared_ptr<i_endpoint>(new area_part(e_area::WAIST));
					}
					else if (area_ == e_area::WAIST)
					{
						return std::shared_ptr<i_endpoint>(new area_part(e_area::TORSO));
					}
					else if (area_ == e_area::HEAD)
					{
						return std::shared_ptr<i_endpoint>(new area_part(e_area::CHEST));
					}
					else if (area_ == e_area::CHEST)
					{
						return std::shared_ptr<i_endpoint>(new area_part(e_area::TORSO));
					}
					else if (area_ == e_area::TORSO)
					{
						throw std::invalid_argument("Shoulder or hip cannot be extremity joints.");
					}
					else
					{
						throw std::invalid_argument("Invalid area part.");
					}
				}

				bool area_part::equals(std::shared_ptr<i_endpoint> a) const
				{
					if (std::shared_ptr<area_part> a_casted = std::dynamic_pointer_cast<area_part>(a))
					{
						return (area_ == a_casted->get_area());
					}

					return false;
				}

				bool area_part::equals(std::shared_ptr<i_part> a) const
				{
					if (std::shared_ptr<i_endpoint> a_casted = std::dynamic_pointer_cast<i_endpoint>(a))
					{
						return equals(a_casted);
					}

					return false;
				}

				bool area_part::all_types_equal(std::shared_ptr<i_endpoint> a) const
				{
					if (std::shared_ptr<area_part> a_casted = std::dynamic_pointer_cast<area_part>(a))
					{
						return true;
					}

					return false;
				}

				bool area_part::all_types_equal(std::shared_ptr<i_part> a) const
				{
					if (std::shared_ptr<i_endpoint> a_casted = std::dynamic_pointer_cast<i_endpoint>(a))
					{
						return all_types_equal(a_casted);
					}

					return false;
				}

				std::vector<double> area_part::feature_vector(double hierarchy_factor) const
				{
					std::vector<double> result;

					result.push_back(hierarchy_factor * e_area_c::to_int(area_)/(double)e_area_c::max());

					return result;
				}

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae
