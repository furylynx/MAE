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

					if (limb_ == e_limb::NONE_LIMB)
					{
						throw std::invalid_argument("NONE is not allowed for a default limb.");
					}
				}

				default_limb::~default_limb()
				{
				}

				e_limb default_limb::get_limb() const
				{
					return limb_;
				}

				std::string default_limb::xml(unsigned int indent, std::string namesp) const
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

					//print definition
					sstr << indent_stream.str() << "<" << ns << "limb>" << std::endl;

					//default
					sstr << indent_stream.str() << "\t" << "<" << ns << "default>" << std::endl;

					//print limb
					sstr << indent_stream.str() << "\t\t" << "<" << ns << "limb>" << e_limb_c::str(limb_) << "</" << ns
							<< "limb>" << std::endl;

					sstr << indent_stream.str() << "\t" << "</" << ns << "default>" << std::endl;

					sstr << indent_stream.str() << "</" << ns << "limb>" << std::endl;

					return sstr.str();
				}

				std::string default_limb::svg(std::string identifier, double posx, double posy, double width,
						double height, bool left) const
				{

					if (width > height)
					{
						posx += width-height;
						width = height;
					}
					else
					{
						height = width;
					}

					std::stringstream sstr;

					sstr << "<path" << std::endl;

					if (limb_ == e_limb::UPPER_ARM)
					{
						sstr << "d=\"m " << posx << "," << posy << " " << 0 << "," << 3.0 * height / 4.0 << "  m  "
								<< width << "," << -2 * height / 4.0 << " " << -3 * width / 4.0 << "," << -height / 4.0
								<< "  " << 0 << "," << 3 * height / 4.0 << " " << 3 * width / 4.0 << "," << height / 4.0
								<< "\"" << std::endl;
					}
					else if (limb_ == e_limb::LOWER_ARM)
					{
						sstr << "d=\"m " << posx << "," << posy << " " << 0 << "," << 3.0 * height / 4.0 << "  m  "
								<< width << "," << -2 * height / 4.0 << " " << -3 * width / 4.0 << "," << -height / 4.0
								<< "  " << 0 << "," << 3 * height / 4.0 << " " << 3 * width / 4.0 << "," << height / 4.0
								<< " m " << -3 * width / 4.0 << "," << -2.5 * height / 4.0 << " " << 3 * width / 4.0
								<< "," << height / 4.0 << "\"" << std::endl;
					}
					else if (limb_ == e_limb::ARM)
					{
						sstr << "d=\"m " << posx << "," << posy + height << " " << 0 << "," << -height << " " << width
								<< "," << height / 4.0 << "  m " << -width / 3.0 << "," << -height / 12.0 << " " << 0
								<< "," << 10 * height / 12.0 << "\"" << std::endl;
					}
					else if (limb_ == e_limb::THIGH)
					{
						sstr << "d=\"m " << posx << "," << posy << " " << 0 << "," << height << "  m  " << width / 2.0
								<< "," << 0 << " " << 0 << "," << -height << " m " << 0 << "," << height / 3.0 << " "
								<< width / 2.0 << "," << 0 << " m " << 0 << "," << height / 3.0 << " " << -width / 2.0
								<< "," << 0 << "\"" << std::endl;
					}
					else if (limb_ == e_limb::LOWER_LEG)
					{
						sstr << "d=\"m " << posx << "," << posy << " " << 0 << "," << height << "  m  " << width / 2.0
								<< "," << 0 << " " << 0 << "," << -height << " m " << 0 << "," << height / 4.0 << " "
								<< width / 2.0 << "," << 0 << " m " << 0 << "," << height / 4.0 << " " << -width / 2.0
								<< "," << 0 << " m " << 0 << "," << height / 4.0 << " " << width / 2.0 << "," << 0
								<< "\"" << std::endl;
					}
					else if (limb_ == e_limb::LEG)
					{
						sstr << "d=\"m " << posx << "," << posy << " " << 0 << "," << height << "  m  " << 0 << ","
								<< -3 * height / 4.0 << " " << width << "," << 0 << " m " << -width / 2.0 << ","
								<< -height / 4.0 << " " << 0 << "," << height << "\"" << std::endl;
					}
					else if (limb_ == e_limb::NECK)
					{
						sstr << "d=\"m " << posx + width / 3.0 << "," << posy + 2 * height / 3.0 << " " << 0 << ","
								<< height / 3.0 << " m " << width / 3.0 << "," << 0 << " " << 0 << "," << -height / 3.0
								<< "  m " << width / 3.0 << "," << -height / 6.0 << " c " << -width * 1.5 << ","
								<< width << " " << -width * 1.5 << "," << -width - height / 2.0 << " " << 0 << ","
								<< -height / 2.0 << "\"" << std::endl;
					}

					if (left && limb_ != e_limb::NECK)
					{
						sstr << "transform=\"matrix(-1,0,0,1," << 2 * posx + width << ",0)\"" << std::endl; //transform=\"translate(" << -width << "), scale(-1, 1)
					}

					sstr << "\t\t\tid=\"" << identifier << "customlimb\"" << std::endl;
					sstr
							<< "\t\t\tstyle=\"fill:none;stroke:#000000;stroke-width:2pt;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\""
							<< std::endl;
					sstr << "\t\t\t/>" << std::endl;

					return sstr.str();
				}

				bool default_limb::equals(std::shared_ptr<i_limb> a) const
				{
					if (std::shared_ptr<default_limb> a_casted = std::dynamic_pointer_cast<default_limb>(a))
					{
						return (limb_ == a_casted->get_limb());
					}

					return false;
				}

				bool default_limb::equals(std::shared_ptr<i_part> a) const
				{
					if (std::shared_ptr<i_limb> a_casted = std::dynamic_pointer_cast<i_limb>(a))
					{
						return equals(a_casted);
					}

					return false;
				}

				bool default_limb::all_types_equal(std::shared_ptr<i_limb> a) const
				{
					if (std::shared_ptr<default_limb> a_casted = std::dynamic_pointer_cast<default_limb>(a))
					{
						return true;
					}

					return false;
				}

				bool default_limb::all_types_equal(std::shared_ptr<i_part> a) const
				{
					if (std::shared_ptr<i_limb> a_casted = std::dynamic_pointer_cast<i_limb>(a))
					{
						return all_types_equal(a_casted);
					}

					return false;
				}

				std::vector<double> default_limb::feature_vector(double hierarchy_factor) const
				{
					std::vector<double> result;

					result.push_back(hierarchy_factor * e_limb_c::to_int(limb_) / (double) e_limb_c::max());

					return result;
				}

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae
