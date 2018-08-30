#include "accent_sign.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				accent_sign::accent_sign(unsigned int accent)
				{
					accent_ = accent;

					if (accent > 5 || accent == 0)
					{
						throw std::invalid_argument("Accent must be a value between 1 and 5.");
					}
				}

				accent_sign::~accent_sign()
				{
				}

				unsigned int accent_sign::get_accent() const
				{
					return accent_;
				}

				bool accent_sign::equals(std::shared_ptr<i_dynamics_sign> a) const
				{
					if (std::shared_ptr<accent_sign> a_dyn = std::dynamic_pointer_cast<accent_sign>(a))
					{
						if (a_dyn->get_accent() == accent_)
						{
							return true;
						}
					}

					return false;
				}

				bool accent_sign::all_types_equal(std::shared_ptr<i_dynamics_sign> a) const
				{
					if (std::shared_ptr<accent_sign> a_dyn = std::dynamic_pointer_cast<accent_sign>(a))
					{
						return true;
					}

					return false;
				}

				std::vector<double> accent_sign::feature_vector(double hierarchy_factor) const
				{
					std::vector<double> result;

					result.push_back(hierarchy_factor * accent_/(double) 5);

					return result;
				}

				std::string accent_sign::xml(unsigned int indent, std::string namesp) const
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

					sstr << indent_stream.str() << "\t" << "<" << ns << "accent>" << accent_ << "</" << ns << "accent>" << std::endl;

					sstr << indent_stream.str() << "</" << ns << "dynamics>" << std::endl;

					return sstr.str();
				}

				std::string accent_sign::svg(std::string identifier, double posx, double posy, double width, double height, bool left) const
				{
					return svg(identifier, draw_rect(posx, posy, width, height), left);
				}

				std::string accent_sign::svg(std::string identifier, draw_rect rect, bool left, svg_style style) const
				{
					double posx = rect.get_posx();
					double posy = rect.get_posy();
					double width = rect.get_width();
					double height = rect.get_height();

					int count = 1;

					if (accent_ >= 2)
                    {
					    count = accent_ - 1;
                    }

					std::stringstream sstr;

					for (std::size_t i = 0; i < count; i++)
                    {
                        sstr << "\t\t<path" << std::endl;
//                        sstr << "\t\t\td=\"M 0.01437266,0.12304805 0.57438403,0.01614424 C 0.48268614,0.40587404 0.59500185,0.7382117 0.98970756,0.98566687 0.40020711,0.84115434 0.08271567,0.53150185 0.01437266,0.12304805 Z\"" << std::endl;
                        sstr << "\t\t\td=\"M "<< posx << "," << posy + height/10.0 << " " << posx+width/2.0 << "," << posy-height/10.0 << " C " << posx + width/2.0 << "," << posy+4*height/10.0 << " " << posx + 6*width/10.0 << "," << posy+7*height/10.0 << " " << posx + width << "," << posy+height << " " << posx + 4*width/10.0 << "," << posy+8*height/10.0 << " " << posx << "," << posy+height/2.0 << " " << posx << "," << posy+height/10.0 << " Z\"" << std::endl;

                        if (!left)
                        {
                            //transform for the right side
                            sstr << "transform=\"matrix(-1,0,0,1," << 2 * posx + width << ",0)\"" << std::endl;
                        }

                        sstr << "\t\t\tid=\"" << identifier << "-dynamic-curve\"" << std::endl;
                        if (1 == accent_)
                        {
                            sstr << "\t\t\tstyle=\"fill:#" << style.get_fill_color() << ";stroke:#" << style.get_draw_color() << ";stroke-width:" << style.get_reduced_stroke_width() << "pt;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\" />" << std::endl;
                        }
                        else
                        {
                            sstr << "\t\t\tstyle=\"fill:#" << style.get_draw_color() << ";stroke:#" << style.get_draw_color() << ";stroke-width:" << style.get_reduced_stroke_width() << "pt;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\" />" << std::endl;
                        }
                    }



					return sstr.str();
				}


			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
