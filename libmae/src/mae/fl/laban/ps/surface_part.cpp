#include "surface_part.hpp"
#include "custom_limb.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{

				surface_part::surface_part(e_limb_side lside, std::shared_ptr<i_limb> limb)
				{
					lside_ = lside;
					limb_ = limb;
				}

				surface_part::~surface_part()
				{
				}

				e_limb_side surface_part::get_limb_side() const
				{
					return lside_;
				}

				std::shared_ptr<i_limb> surface_part::get_limb() const
				{
					return limb_;
				}

				std::string surface_part::xml(unsigned int indent, std::string namesp) const
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

					//print definition
					sstr << indent_stream.str() << "<" << ns << "surface>" << std::endl;

					//print part
					sstr << limb_->xml(indent + 1, namesp);

					//print side
					sstr << indent_stream.str() << "\t" << "<" << ns << "side>" << e_limb_side_c::str(lside_) << "</" << ns << "side>" << std::endl;

					sstr << indent_stream.str() << "</" << ns << "surface>" << std::endl;

					return sstr.str();

				}

                std::string surface_part::svg(std::string identifier, double posx, double posy, double width, double height, bool left) const
                {
				    return svg(identifier, draw_rect(posx, posy, width, height), left);
                }

				std::string surface_part::svg(std::string identifier, draw_rect rect, bool left, svg_style style) const
				{
                    double posx = rect.get_posx();
                    double posy = rect.get_posy();
                    double width = rect.get_width();
                    double height = rect.get_height();

                    identifier.append("surface-part");

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

                    double nposx = posx + width/6.0;
                    if (left)
                    {
                        nposx = posx - width/6.0;
                    }

                    sstr << limb_->svg(identifier,nposx, posy, 5 * width / 6.0, height, left);

                    double radius = (width / 12.0);
                    double offsetx = 5.0*width / 24.0 + (width/6.0);
                    //width / 4.0
                    double offsety = height / 2.0 - radius;

                    bool draw_additional_line = false;
                    double draw_additional_line_length = 3 * height / 4.0;

                    if (std::shared_ptr<default_limb> limb_casted = std::dynamic_pointer_cast<default_limb>(limb_))
                    {
                        if (limb_casted->get_limb() == e_limb::UPPER_ARM || limb_casted->get_limb() == e_limb::LOWER_ARM || limb_casted->get_limb() == e_limb::ARM)
                        {
                            offsetx = (5.0*width / 48.0) + (width/6.0);
                            //width/8.0
                            offsety = height / 3.0 - radius/2.0;
                        }
                    }
                    else if (std::shared_ptr<custom_limb> limb_casted = std::dynamic_pointer_cast<custom_limb>(limb_))
					{
						offsetx = (5.0*width / 48.0) + (width/6.0);
						//width/8.0
                        offsety = height / 3.0 - radius/2.0;
                        draw_additional_line = true;

					}

                    if (left)
                    {
                        offsetx = width - offsetx;
                    }

					if (lside_ != e_limb_side::THUMB && lside_ != e_limb_side::LITTLEFINGER )
					{
						//draw bullet
						sstr << "\t\t<path" << std::endl;
						sstr << "\t\t\td=\"m " << posx + offsetx + radius << "," << posy + offsety
							 << " a " << radius << "," << radius << " 0 1 1 -" << radius * 2.0 << ",0 "
							 << radius << "," << radius << " 0 1 1 " << radius * 2.0 << ",0 z\""
							 << std::endl;
						sstr << "\t\t\tid=\"" << identifier << "-surface-circle\"" << std::endl;

						if (lside_ == e_limb_side::OUTER || lside_ == e_limb_side::OUTERLITTLEFINGER || lside_ == e_limb_side::OUTERTHUMB)
						{
							sstr << "\t\t\tstyle=\"fill:#" << style.get_fill_color() << ";fill-opacity:1;stroke:#" << style.get_draw_color() << ";stroke-width:" << style.get_reduced_stroke_width() << "pt;stroke-miterlimit:1;stroke-opacity:1;stroke-dasharray:none\" />"
								 << std::endl;
						}
						else
						{
							sstr << "\t\t\tstyle=\"fill:#" << style.get_fill_color() << ";fill-opacity:1;stroke:#" << style.get_draw_color() << ";stroke-width:" << style.get_reduced_stroke_width() << "pt;stroke-miterlimit:1;stroke-opacity:1;stroke-dasharray:none\" />"
								 << std::endl;
						}
					}

					if (lside_ == e_limb_side::OUTERLITTLEFINGER || lside_ == e_limb_side::LITTLEFINGER || lside_ == e_limb_side::THUMB || lside_ == e_limb_side::INNERLITTLEFINGER || lside_ == e_limb_side::INNERTHUMB || lside_ == e_limb_side::OUTERTHUMB)
                    {
					    if (left)
                        {
                            sstr << "\t<path d=\"m " << posx+width << "," << posy + offsety << " "
                                 << -width / 6.0 << "," << 0 << "\" id=\"" << identifier
                                 << "-tick\"" << std::endl;
                            sstr << "\t\t style=\"fill:none;stroke:#" << style.get_draw_color() << ";stroke-width:" << style.get_stroke_width() << "pt;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\" />"
                                 << std::endl;
                        }
                        else
                        {
                            sstr << "\t<path d=\"m " << posx << "," << posy + offsety << " "
                                 << width / 6.0 << "," << 0 << "\" id=\"" << identifier
                                 << "-tick\"" << std::endl;
                            sstr << "\t\t style=\"fill:none;stroke:#" << style.get_draw_color() << ";stroke-width:" << style.get_stroke_width() << "pt;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\" />"
                                 << std::endl;
                        }
                    }

                    if (draw_additional_line)
                    {
                        double loffset = width/6.0;

                        if (left)
                        {
                            loffset = 5*width / 6.0;
                        }

                        sstr << "\t<path d=\"m " << posx + loffset << "," << posy - height / 12.0 << " "
                             << 0 << "," << draw_additional_line_length << "\" id=\"" << identifier
                             << "-tick\"" << std::endl;
                        sstr << "\t\t style=\"fill:none;stroke:#" << style.get_draw_color() << ";stroke-width:" << style.get_stroke_width() << "pt;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\" />"
                             << std::endl;
                    }

					return sstr.str();
				}

				bool surface_part::equals(std::shared_ptr<i_part> a) const
				{
					if (std::shared_ptr<surface_part> a_casted = std::dynamic_pointer_cast<surface_part>(a))
					{
						return (lside_ == a_casted->get_limb_side() && limb_->equals(a_casted->get_limb()));
					}

					return false;
				}

				bool surface_part::all_types_equal(std::shared_ptr<i_part> a) const
				{
					if (std::shared_ptr<surface_part> a_casted = std::dynamic_pointer_cast<surface_part>(a))
					{
						return true;
					}

					return false;
				}

				std::vector<double> surface_part::feature_vector(double hierarchy_factor) const
				{
					std::vector<double> result;

					result.push_back(hierarchy_factor * e_limb_side_c::to_int(lside_) / (double) e_limb_side_c::max());

					std::vector<double> fvec_limb = limb_->feature_vector(std::pow(hierarchy_factor,2));

					result.insert(result.end(), fvec_limb.begin(), fvec_limb.end());

					return result;
				}

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae
