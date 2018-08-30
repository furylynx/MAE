#include "direction_symbol.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				direction_symbol::direction_symbol(e_level vertical, e_direction horizontal,
						std::shared_ptr<pin> modification_pin, std::shared_ptr<pin> relationship_pin,
						std::shared_ptr<i_dynamics_sign> dynamics, std::shared_ptr<space_measurement> space_measurement,
						e_contact_hook contact_hook)
				{
					vertical_ = vertical;
					horizontal_ = horizontal;
					modification_pin_ = modification_pin;
					relationship_pin_ = relationship_pin;
					dynamics_ = dynamics;
					space_measurement_ = space_measurement;
					contact_hook_ = contact_hook;

					if (vertical == e_level::NONE_LEVEL || horizontal == e_direction::NONE_DIRECTION)
					{
						throw std::invalid_argument("Direction and level must not be NONE.");
					}
				}

				direction_symbol::~direction_symbol()
				{
				}

				e_level direction_symbol::get_vertical() const
				{
					return vertical_;
				}

				e_direction direction_symbol::get_horizontal() const
				{
					return horizontal_;
				}

				std::shared_ptr<pin> direction_symbol::get_modification_pin() const
				{
					return modification_pin_;
				}

				std::shared_ptr<pin> direction_symbol::get_relationship_pin() const
				{
					return relationship_pin_;
				}

				std::shared_ptr<i_dynamics_sign> direction_symbol::get_dynamics() const
				{
					return dynamics_;
				}

				std::shared_ptr<space_measurement> direction_symbol::get_space_measurement() const
				{
					return space_measurement_;
				}

				e_contact_hook direction_symbol::get_contact_hook() const
				{
					return contact_hook_;
				}

				bool direction_symbol::equals(std::shared_ptr<i_symbol> a) const
				{
					if (std::shared_ptr<direction_symbol> a_dir = std::dynamic_pointer_cast<direction_symbol>(a))
					{
						if (a_dir->get_horizontal() == horizontal_ && a_dir->get_vertical() == vertical_
								&& a_dir->get_contact_hook() == contact_hook_)
						{
							//check modification pin
							if ((modification_pin_ != nullptr
									&& modification_pin_->equals(a_dir->get_modification_pin()))
									|| (modification_pin_ == nullptr && a_dir->get_modification_pin() == nullptr))
							{
								//check relationship pin
								if ((relationship_pin_ != nullptr
										&& relationship_pin_->equals(a_dir->get_relationship_pin()))
										|| (relationship_pin_ == nullptr && a_dir->get_relationship_pin() == nullptr))
								{
									//check dynamics sign
									if ((dynamics_ != nullptr && dynamics_->equals(a_dir->get_dynamics()))
											|| (dynamics_ == nullptr && a_dir->get_dynamics() == nullptr))
									{
										//check space measurement
										if ((space_measurement_ != nullptr && space_measurement_->equals(a_dir->get_space_measurement()))
												|| (space_measurement_ == nullptr && a_dir->get_space_measurement() == nullptr))
										{
											return true;
										}
									}
								}
							}

						}
					}

					return false;
				}

				bool direction_symbol::all_types_equal(std::shared_ptr<i_symbol> a) const
				{
					if (std::shared_ptr<direction_symbol> a_dir = std::dynamic_pointer_cast<direction_symbol>(a))
					{
						//check modification pin
						if ((modification_pin_ != nullptr
							 && modification_pin_->all_types_equal(a_dir->get_modification_pin()))
							|| (modification_pin_ == nullptr && a_dir->get_modification_pin() == nullptr))
						{
							//check relationship pin
							if ((relationship_pin_ != nullptr
								 && relationship_pin_->all_types_equal(a_dir->get_relationship_pin()))
								|| (relationship_pin_ == nullptr && a_dir->get_relationship_pin() == nullptr))
							{
								//check dynamics sign
								if ((dynamics_ != nullptr && dynamics_->all_types_equal(a_dir->get_dynamics()))
									|| (dynamics_ == nullptr && a_dir->get_dynamics() == nullptr))
								{
									//check space measurement
									if ((space_measurement_ != nullptr && space_measurement_->all_types_equal(a_dir->get_space_measurement()))
										|| (space_measurement_ == nullptr && a_dir->get_space_measurement() == nullptr))
									{
										return true;
									}
								}
							}
						}
					}

					return false;
				}

				std::vector<double> direction_symbol::feature_vector(double hierarchy_factor) const
				{
					std::vector<double> result;

					//set value for the direction
					fl_direction_map  map;
					std::shared_ptr<mae::math::vec3d> set_dir = map.get_vec(horizontal_, vertical_);

					result.push_back(hierarchy_factor * set_dir->get_x());
					result.push_back(hierarchy_factor * set_dir->get_y());
					result.push_back(hierarchy_factor * set_dir->get_z());

					std::vector<double> fvec_mpin;

					if (nullptr != modification_pin_)
					{
						fvec_mpin = modification_pin_->feature_vector(std::pow(hierarchy_factor, 2));
					}

					std::vector<double> fvec_rpin;

					if (nullptr != relationship_pin_)
					{
						fvec_rpin = relationship_pin_->feature_vector(std::pow(hierarchy_factor, 2));
					}

					std::vector<double> fvec_dyn;

					if (nullptr != dynamics_)
					{
						fvec_dyn = dynamics_->feature_vector(std::pow(hierarchy_factor, 2));
					}

					std::vector<double> fvec_spacem;

					if (nullptr != space_measurement_)
					{
						fvec_spacem = space_measurement_->feature_vector(std::pow(hierarchy_factor, 2));
					}

					result.insert(result.end(), fvec_mpin.begin(), fvec_mpin.end());
					result.insert(result.end(), fvec_rpin.begin(), fvec_rpin.end());
					result.insert(result.end(), fvec_dyn.begin(), fvec_dyn.end());
					result.insert(result.end(), fvec_spacem.begin(), fvec_spacem.end());

					result.push_back(hierarchy_factor * e_contact_hook_c::to_int(contact_hook_) / (double) e_contact_hook_c::max());

					return result;
				}

				std::vector<std::type_index> direction_symbol::get_type_path() const
				{
					std::vector<std::type_index> result;
					result.push_back(std::type_index(typeid(mae::fl::laban::mv::i_symbol)));
					result.push_back(std::type_index(typeid(mae::fl::laban::mv::direction_symbol)));

					return result;
				}

				std::string direction_symbol::xml(unsigned int indent, std::string namesp) const
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

					//print accent sign
					sstr << indent_stream.str() << "<" << ns << "direction>" << std::endl;

					sstr << indent_stream.str() << "\t" << "<" << ns << "vertical>" << e_level_c::str(vertical_) << "</"
							<< ns << "vertical>" << std::endl;
					sstr << indent_stream.str() << "\t" << "<" << ns << "horizontal>" << e_direction_c::str(horizontal_)
							<< "</" << ns << "horizontal>" << std::endl;

					if (modification_pin_ != nullptr)
					{
						sstr << indent_stream.str() << "\t" << "<" << ns << "modificationPin>" << std::endl;
						sstr << modification_pin_->xml(indent + 1, namesp);
						sstr << indent_stream.str() << "\t" << "</" << ns << "modificationPin>" << std::endl;
					}

					if (relationship_pin_ != nullptr)
					{
						sstr << indent_stream.str() << "\t" << "<" << ns << "relationshipPin>" << std::endl;
						sstr << relationship_pin_->xml(indent + 1, namesp);
						sstr << indent_stream.str() << "\t" << "</" << ns << "relationshipPin>" << std::endl;
					}

					if (space_measurement_ != nullptr)
					{
						sstr << space_measurement_->xml(indent + 1, namesp);
					}

					if (dynamics_ != nullptr)
					{
						sstr << dynamics_->xml(indent + 1, namesp);
					}

					if (contact_hook_ != e_contact_hook::NONE_CONTACT_HOOK)
					{
						sstr << indent_stream.str() << "\t" << "<" << ns << "contactHook>"
								<< e_contact_hook_c::str(contact_hook_) << "</" << ns << "contactHook>" << std::endl;
					}

					sstr << indent_stream.str() << "</" << ns << "direction>" << std::endl;

					return sstr.str();
				}

                std::string direction_symbol::svg(std::string identifier, double posx, double posy, double width, double height, bool left) const
                {
                    return svg(identifier, draw_rect(posx, posy, width, height), left);
                }

				std::string direction_symbol::svg(std::string identifier, draw_rect rect, bool left, svg_style style) const
				{
                    double posx = rect.get_posx();
                    double posy = rect.get_posy();
                    double width = rect.get_width();
                    double height = rect.get_height();

					std::stringstream sstr;

					//TODO contact hook

					if (space_measurement_ != nullptr)
					{
						height -= width;

						if (height < 0)
						{
							height = 0.01;
						}
					}

					if (horizontal_ == e_direction::PLACE)
					{
						sstr << "\t\t<rect" << std::endl;
				        sstr << "\t\t\twidth=\"" << width <<  "\"" << std::endl;
				        sstr << "\t\t\theight=\"" << height <<  "\"" << std::endl;
				        sstr << "\t\t\tx=\"" << posx <<  "\"" << std::endl;
				        sstr << "\t\t\ty=\"" << posy <<  "\"" << std::endl;
					}
					else if (horizontal_ == e_direction::LEFT)
					{
						sstr << "\t\t<path" << std::endl;
						sstr << "\t\t\td=\"m " << posx+width << "," << posy << " " << 0 << "," << height << " " << -width << "," << -height/2.0 << " " << width << "," << -height/2.0 << " z\"" << std::endl;
					}
					else if (horizontal_ == e_direction::RIGHT)
					{
						sstr << "\t\t<path" << std::endl;
						sstr << "\t\t\td=\"m " << posx << "," << posy << " " << 0 << "," << height << " " << width << "," << -height/2.0 << " " << -width << "," << -height/2.0 << " z\"" << std::endl;
					}
					else if (horizontal_ == e_direction::FORWARD && left)
					{
						sstr << "\t\t<path" << std::endl;
						sstr << "\t\t\td=\"m " << posx << "," << posy+height/3.0 << " " << width/2.0 << "," << 0 << " " << 0 << "," << -height/3.0 << " " << width/2.0 << "," << 0 << " " << 0 << "," << height << " " << -width << "," << 0 << " " << 0 << "," << -2*height/3.0 << " z\"" << std::endl;
					}
					else if (horizontal_ == e_direction::FORWARD && !left)
					{
						sstr << "\t\t<path" << std::endl;
						sstr << "\t\t\td=\"m " << posx+width << "," << posy+height/3.0 << " " << -width/2.0 << "," << 0 << " " << 0 << "," << -height/3.0 << " " << -width/2.0 << "," << 0 << " " << 0 << "," << height << " " << width << "," << 0 << " " << 0 << "," << -2*height/3.0 << " z\"" << std::endl;
					}
					else if (horizontal_ == e_direction::BACKWARD && left)
					{
						sstr << "\t\t<path" << std::endl;
						sstr << "\t\t\td=\"m " << posx << "," << posy+height-height/3.0 << " " << width/2.0 << "," << 0 << " " << 0 << "," << height/3.0 << " " << width/2.0 << "," << 0 << " " << 0 << "," << -height << " " << -width << "," << 0 << " " << 0 << "," << 2*height/3.0 << " z\"" << std::endl;
					}
					else if (horizontal_ == e_direction::BACKWARD && !left)
					{
						sstr << "\t\t<path" << std::endl;
						sstr << "\t\t\td=\"m " << posx+width << "," << posy+height-height/3.0 << " " << -width/2.0 << "," << 0 << " " << 0 << "," << height/3.0 << " " << -width/2.0 << "," << 0 << " " << 0 << "," << -height << " " << width << "," << 0 << " " << 0 << "," << 2*height/3.0 << " z\"" << std::endl;
					}
					else if (horizontal_ == e_direction::RIGHT_FORWARD)
					{
						sstr << "\t\t<path" << std::endl;
						sstr << "\t\t\td=\"m " << posx << "," << posy+height/3.0 << " " << width << "," << -height/3.0 << " " << 0 << "," << height << " " << -width << "," << 0 << " " << 0 << "," << -2*height/3.0 << " z\"" << std::endl;
					}
					else if (horizontal_ == e_direction::LEFT_FORWARD)
					{
						sstr << "\t\t<path" << std::endl;
						sstr << "\t\t\td=\"m " << posx+width << "," << posy+height/3.0 << " " << -width << "," << -height/3.0 << " " << 0 << "," << height << " " << width << "," << 0 << " " << 0 << "," << -2*height/3.0 << " z\"" << std::endl;
					}
					else if (horizontal_ == e_direction::RIGHT_BACKWARD)
					{
						sstr << "\t\t<path" << std::endl;
						sstr << "\t\t\td=\"m " << posx << "," << posy+height-height/3.0 << " " << width << "," << height/3.0 << " " << 0 << "," << -height << " " << -width << "," << 0 << " " << 0 << "," << 2*height/3.0 << " z\"" << std::endl;
					}
					else if (horizontal_ == e_direction::LEFT_BACKWARD)
					{
						sstr << "\t\t<path" << std::endl;
						sstr << "\t\t\td=\"m " << posx+width << "," << posy+height-height/3.0 << " " << -width << "," << height/3.0 << " " << 0 << "," << -height << " " << width << "," << 0 << " " << 0 << "," << 2*height/3.0 << " z\"" << std::endl;
					}
					else
					{
						return "";
					}

			        sstr << "\t\t\tid=\"" << identifier << "\"" << std::endl;

					sstr << "\t\t\tstyle=\"";
					if (vertical_ == e_level::HIGH)
					{
						sstr << "fill:url(#fillpattern);fill-opacity:1;stroke:#" << style.get_draw_color() << ";stroke-width:" << style.get_stroke_width() << "pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none";
					}
					else if (vertical_ == e_level::LOW)
					{
						sstr << "fill:#" << style.get_draw_color() << ";fill-opacity:1;stroke:#" << style.get_draw_color() << ";stroke-width:" << style.get_stroke_width() << "pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none";
					}
					else if (vertical_ == e_level::MIDDLE)
					{
						sstr << "fill:#" << style.get_fill_color() << ";fill-opacity:1;stroke:#" << style.get_draw_color() << ";stroke-width:" << style.get_stroke_width() << "pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none";
					}
					else
					{
						return "";
					}
					sstr << "\" />" << std::endl;

					if (vertical_ == e_level::MIDDLE)
					{
						double circ_x = posx + width/2.0;
						double circ_y = posy + height/2.0;
						double circ_r = width/12.0;

						if (horizontal_ == e_direction::RIGHT)
						{
							circ_x -= width/6.0;
						}
						else if (horizontal_ == e_direction::LEFT)
						{
							circ_x += width/6.0;
						}
						else if (horizontal_ == e_direction::FORWARD)
						{
							circ_y += height/6.0;
						}
						else if (horizontal_ == e_direction::BACKWARD)
						{
							circ_y -= height/6.0;
						}

						if (height < circ_r)
						{
							circ_r = height;
						}

						//draw circle
					    sstr << "\t\t<path" << std::endl;
					    sstr << "\t\t\td=\"m " << circ_x + circ_r << "," << circ_y << " a " << circ_r << "," << circ_r << " 0 1 1 -" << circ_r*2 << ",0 " << circ_r << "," << circ_r << " 0 1 1 " << circ_r*2 << ",0 z\"" << std::endl;
					    sstr << "\t\t\tid=\"" << identifier << "-middot\"" << std::endl;
					    sstr << "\t\t\tstyle=\"fill:#" << style.get_draw_color() << ";fill-opacity:1;stroke:none\" />" << std::endl;
					}


					if (space_measurement_ != nullptr)
					{
						//draw space measurement
						double spm_y = posy + height + width*0.1;
						double spm_w = width*0.8;
						double spm_h = width*0.8;
						double spm_x = posx + width*0.1;


						std::string spacem_id = identifier;
						spacem_id.append("-spacem");

						sstr << space_measurement_->svg(spacem_id, spm_x, spm_y, spm_w, spm_h);
					}

					if (modification_pin_ != nullptr)
					{
						//draw pin
						double mpin_w = width*0.8;
						double mpin_h = width*0.8;
						double mpin_y = posy + height/2.0 - mpin_h/2.0;
						double mpin_x = posx + width/2.0 - mpin_w/2.0;

						std::string pin_id = identifier;
						pin_id.append("-mpin");

						sstr << space_measurement_->svg(pin_id, mpin_x, mpin_y, mpin_w, mpin_h);
					}

					if (relationship_pin_ != nullptr)
					{
						//draw pin
						double mpin_w = width*0.8;
						double mpin_h = width*0.8;
						double mpin_y = posy + height/2.0 - mpin_h/2.0;
						double mpin_x = posx + width;

						std::string pin_id = identifier;
						pin_id.append("-rpin");

						sstr << relationship_pin_->svg(pin_id, mpin_x, mpin_y, mpin_w, mpin_h);
					}

					if (dynamics_ != nullptr)
					{
						//draw dynamics
						double mpin_w = width / 2.0;
						double mpin_h = width / 2.0;
						double mpin_y = posy + height - mpin_h;
						double mpin_x = posx + width;

						std::string d_id = identifier;
						d_id.append("-dyn");

						sstr << dynamics_->svg(identifier, mpin_x, mpin_y, mpin_w, mpin_h);
					}

					return sstr.str();
				}

				std::string direction_symbol::str() const
				{
					std::stringstream sstr;

					sstr << "(" << e_direction_c::str(horizontal_) << "+" << e_level_c::str(vertical_) << ")";

					return sstr.str();
				}

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
