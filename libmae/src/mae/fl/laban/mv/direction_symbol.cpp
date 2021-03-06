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
					std::stringstream sstr;

					//TODO relationship pin, dynamics, contact hook

					//double orig_height = height;

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
						sstr << "fill:url(#fillpattern);fill-opacity:1;stroke:#000000;stroke-width:2pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none";
					}
					else if (vertical_ == e_level::LOW)
					{
						sstr << "fill:#000000;fill-opacity:1;stroke:#000000;stroke-width:2pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none";
					}
					else if (vertical_ == e_level::MIDDLE)
					{
						sstr << "fill:#ffffff;fill-opacity:1;stroke:#000000;stroke-width:2pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none";
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
					    sstr << "\t\t\tstyle=\"fill:#000000;fill-opacity:1;stroke:none\" />" << std::endl;
					}


					if (space_measurement_ != nullptr)
					{
						//draw space measurement
						double spm_y = posy + height + width*0.1;
						double spm_w = width*0.8;
						double spm_h = width*0.8;
						double spm_x = posx + width*0.1;

						sstr << space_measurement_->svg(identifier, spm_x, spm_y, spm_w, spm_h);
					}

					if (modification_pin_ != nullptr)
					{
						//draw pin
						double mpin_w = width*0.8;
						double mpin_h = width*0.8;
						double mpin_y = posy + height/2.0 - mpin_h/2.0;
						double mpin_x = posx + width/2.0 - mpin_w/2.0;

						sstr << space_measurement_->svg(identifier, mpin_x, mpin_y, mpin_w, mpin_h);
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
