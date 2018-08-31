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

                    if (width > height)
                    {
                        posx += (width - height) / 2.0;
                        width = height;
                    }
                    else if (height > width)
                    {
                        posy = posy + height - width;
                        height = width;
                    }

					std::stringstream sstr;

					if (dynamic_ == e_dynamic::STRONG || dynamic_ == e_dynamic::GENTLE || dynamic_ == e_dynamic::RELAXED || dynamic_ == e_dynamic::LIMP)
					{
						double circ_r = width/2.0;
                        double radius = (width / 5.0);
                        double offsetx = 3*radius;
                        double offsety = height - radius;

                        if (left)
                        {
                            offsetx = width - 2*radius;
                        }

						//draw bow
						sstr << "\t\t<path" << std::endl;
						sstr << "\t\t\td=\"m " << posx+width/5.0 << "," << posy+height << " a " << circ_r << "," << circ_r << " 0 1 1 " << circ_r*2 << ",0\"" << std::endl;

						if (dynamic_ == e_dynamic::RELAXED || dynamic_ == e_dynamic::LIMP)
                        {
						    //mirror vertically
						    sstr << "\t\t\ttransform=\"matrix(1,0,0,-1," << 0 << "," << 2 * posy + height << ")\"" << std::endl;

						    offsety = radius;
						}

						sstr << "\t\t\tid=\"" << identifier << "-dynamic-curve\"" << std::endl;
						sstr << "\t\t\tstyle=\"fill:#" << style.get_fill_color() << ";fill-opacity:1;stroke:#" << style.get_draw_color() << ";stroke-width:" << style.get_reduced_stroke_width() << "pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />" << std::endl;

                        //draw circle
                        sstr << "\t\t<path" << std::endl;
                        sstr << "\t\t\td=\"m " << posx + offsetx << "," << posy + offsety
                             << " a " << radius << "," << radius << " 0 1 1 -" << 2*radius << ",0 "
                             << radius << "," << radius << " 0 1 1 " << 2*radius << ",0 z\""
                             << std::endl;
                        sstr << "\t\t\tid=\"" << identifier << "-dynamic-circle\"" << std::endl;

                        if (dynamic_ == e_dynamic::GENTLE || dynamic_ == e_dynamic::RELAXED)
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
					else if (dynamic_ == e_dynamic::RESILIENT || dynamic_ == e_dynamic::VERY_RESILIENT)
                    {
                        sstr << "\t\t<path" << std::endl;
                        sstr << "\t\t\td=\"M "<< posx << "," << posy + height/10.0 << " " << posx+width/2.0 << "," << posy-height/10.0 << " C " << posx + width/2.0 << "," << posy+4*height/10.0 << " " << posx + 6*width/10.0 << "," << posy+7*height/10.0 << " " << posx + width << "," << posy+height << " " << posx + 4*width/10.0 << "," << posy+8*height/10.0 << " " << posx << "," << posy+height/2.0 << " " << posx << "," << posy+height/10.0 << " Z\"" << std::endl;

                        if (!left)
                        {
                            //transform for the right side
                            sstr << "transform=\"matrix(-1,0,0,1," << 2 * posx + width << ",0)\"" << std::endl;
                        }

                        sstr << "\t\t\tid=\"" << identifier << "-dynamic-curve\"" << std::endl;
                        if (dynamic_ == e_dynamic::RESILIENT)
                        {
                            sstr << "\t\t\tstyle=\"fill:#" << style.get_fill_color() << ";stroke:#" << style.get_draw_color() << ";stroke-width:" << style.get_reduced_stroke_width() << "pt;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\" />" << std::endl;
                        }
                        else
                        {
                            sstr << "\t\t\tstyle=\"fill:#" << style.get_draw_color() << ";stroke:#" << style.get_draw_color() << ";stroke-width:" << style.get_reduced_stroke_width() << "pt;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\" />" << std::endl;
                        }


                        //draw circle
                        double radius = (width / 6.0);
                        double offsetx = 2*radius;
                        if (left)
                        {
                            offsetx = width;
                        }
                        double offsety = height - radius;

                        sstr << "\t\t<path" << std::endl;
                        sstr << "\t\t\td=\"m " << posx + offsetx << "," << posy + offsety
                             << " a " << radius << "," << radius << " 0 1 1 -" << 2*radius << ",0 "
                             << radius << "," << radius << " 0 1 1 " << 2*radius << ",0 z\""
                             << std::endl;
                        sstr << "\t\t\tid=\"" << identifier << "-dynamic-circle\"" << std::endl;

                        sstr << "\t\t\tstyle=\"fill:#" << style.get_fill_color() << ";fill-opacity:1;stroke:#" << style.get_draw_color() << ";stroke-width:" << style.get_reduced_stroke_width() << "pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />"
                             << std::endl;
                    }
                    else if (dynamic_ == e_dynamic::UNEMPHASIZED || dynamic_ == e_dynamic::EMPHASIZED)
                    {
                        sstr << "\t\t<path" << std::endl;
                        //"M 1,1 C 0.66,1 0,0.33 0,0"
                        sstr << "\t\t\td=\"M "<< posx + width << "," << posy + height << " C " << posx+2*width/3.0 << "," << posy + height << " " << posx << "," << posy + height/3.0 << " " << posx << "," << posy << "\"" << std::endl;

                        if (!left)
                        {
                            //transform for the right side
                            sstr << "transform=\"matrix(-1,0,0,1," << 2 * posx + width << ",0)\"" << std::endl;
                        }

                        sstr << "\t\t\tid=\"" << identifier << "-dynamic-curve\"" << std::endl;
                        sstr << "\t\t\tstyle=\"fill:none;stroke:#" << style.get_draw_color() << ";stroke-width:" << style.get_reduced_stroke_width() << "pt;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\" />" << std::endl;

                        //draw circle
                        double radius = (width / 6.0);
                        double offsetx = width;
                        double offsety = radius;

                        if ((left && dynamic_ == e_dynamic::EMPHASIZED) || (!left && dynamic_ == e_dynamic::UNEMPHASIZED))
                        {
                            offsetx = 2*radius;
                        }

                        if (dynamic_ == e_dynamic::UNEMPHASIZED)
                        {
                            offsety = height-radius;
                        }

                        sstr << "\t\t<path" << std::endl;
                        sstr << "\t\t\td=\"m " << posx + offsetx << "," << posy + offsety
                             << " a " << radius << "," << radius << " 0 1 1 -" << 2*radius << ",0 "
                             << radius << "," << radius << " 0 1 1 " << 2*radius << ",0 z\""
                             << std::endl;
                        sstr << "\t\t\tid=\"" << identifier << "-dynamic-circle\"" << std::endl;

                        if (dynamic_ == e_dynamic::EMPHASIZED)
                        {
                            sstr << "\t\t\tstyle=\"fill:#" << style.get_draw_color() ;
                        }
                        else
                        {
                            sstr << "\t\t\tstyle=\"fill:#" << style.get_fill_color() ;
                        }
                        sstr << ";fill-opacity:1;stroke:#" << style.get_draw_color() << ";stroke-width:" << style.get_reduced_stroke_width() << "pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />"
                             << std::endl;
                    }



					return sstr.str();
				}


			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
