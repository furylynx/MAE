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

					if (dynamic == e_dynamic::NONE_DYNAMIC)
					{
						throw std::invalid_argument("Dynamic must not be NONE.");
					}
				}

				dynamic_sign::~dynamic_sign()
				{
				}

				e_dynamic dynamic_sign::get_dynamic() const
				{
					return dynamic_;
				}

				bool dynamic_sign::equals(std::shared_ptr<i_dynamics_sign> a) const
				{
					if (std::shared_ptr<dynamic_sign> a_dyn = std::dynamic_pointer_cast<dynamic_sign>(a))
					{
						if (a_dyn->get_dynamic() == dynamic_)
						{
							return true;
						}
					}

					return false;
				}

				bool dynamic_sign::all_types_equal(std::shared_ptr<i_dynamics_sign> a) const
				{
					if (std::shared_ptr<dynamic_sign> a_dyn = std::dynamic_pointer_cast<dynamic_sign>(a))
					{
						return true;
					}

					return false;
				}


				std::vector<double> dynamic_sign::feature_vector(double hierarchy_factor) const
				{
					std::vector<double> result;

					result.push_back(hierarchy_factor * e_dynamic_c::to_int(dynamic_) / (double) e_dynamic_c::max());

					return result;
				}

				std::string dynamic_sign::xml(unsigned int indent, std::string namesp) const
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

				std::string dynamic_sign::svg(std::string identifier, double posx, double posy, double width, double height, bool left) const
				{
					return svg(identifier, draw_rect(posx, posy, width, height), left);
				}

				std::string dynamic_sign::svg(std::string identifier, draw_rect rect, bool left, svg_style style) const
				{
					double posx = rect.get_posx();
					double posy = rect.get_posy();
					double width = rect.get_width();
					double height = rect.get_height();

					std::stringstream sstr;

					//TODO
					if (dynamic_ == e_dynamic::STRONG || dynamic_ == e_dynamic::GENTLE || dynamic_ == e_dynamic::RELAXED || dynamic_ == e_dynamic::LIMP)
					{
						double circ_r = width/3.0;

						//draw half circle
						sstr << "\t\t<path" << std::endl;
						sstr << "\t\t\td=\"m " << posx + width/3.0 + circ_r << "," << posy+width/2.0 << " a " << circ_r << "," << circ_r << " 0 1 1 -" << circ_r*2 << ",0\"" << std::endl;


						if (left)
						{
							sstr << "transform=\"matrix(-1,0,0,1," << 2 * posx + width << ",0)\"" << std::endl;
						}

						//TODO
						if (dynamic_ == e_dynamic::RELAXED || dynamic_ == e_dynamic::LIMP)
						{
							//TODO mirror vertically
						}

						sstr << "\t\t\tid=\"" << identifier << "-cancel-release1\"" << std::endl;
						sstr << "\t\t\tstyle=\"fill:#" << style.get_fill_color() << ";fill-opacity:1;stroke:#" << style.get_draw_color() << ";stroke-width:" << style.get_stroke_width() << "pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />" << std::endl;

						//TODO draw circle

					}


					return sstr.str();
				}


			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
