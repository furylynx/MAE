#include "turn_symbol.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				turn_symbol::turn_symbol(e_turn_direction direction, std::shared_ptr<i_dynamics_sign> dynamics,
						std::shared_ptr<i_degree_sign> degree)
				{
					direction_ = direction;

					dynamics_ = dynamics;
					degree_ = degree;

					if (direction == e_turn_direction::NONE_TURN_DIRECTION)
					{
						throw std::invalid_argument("Direction must not be NONE.");
					}

				}

				turn_symbol::~turn_symbol()
				{
				}

				e_turn_direction turn_symbol::get_direction() const
				{
					return direction_;
				}

				std::shared_ptr<i_dynamics_sign> turn_symbol::get_dynamics() const
				{
					return dynamics_;
				}

				std::shared_ptr<i_degree_sign> turn_symbol::get_degree() const
				{
					return degree_;
				}

				bool turn_symbol::equals(std::shared_ptr<i_symbol> a) const
				{
					if (std::shared_ptr<turn_symbol> a_turn = std::dynamic_pointer_cast<turn_symbol>(a))
					{
						if (a_turn->get_direction() == direction_)
						{
							//check dynamics sign
							if ((dynamics_ != nullptr && dynamics_->equals(a_turn->get_dynamics()))
									|| (dynamics_ == nullptr && a_turn->get_dynamics() == nullptr))
							{
								//check degree sign
								if ((degree_ != nullptr && degree_->equals(a_turn->get_degree()))
										|| (degree_ == nullptr && a_turn->get_degree() == nullptr))
								{
									return true;
								}
							}
						}
					}

					return false;
				}

				bool turn_symbol::all_types_equal(std::shared_ptr<i_symbol> a) const
				{
					if (std::shared_ptr<turn_symbol> a_turn = std::dynamic_pointer_cast<turn_symbol>(a))
					{
						//check dynamics sign
						if ((dynamics_ != nullptr && dynamics_->all_types_equal(a_turn->get_dynamics()))
							|| (dynamics_ == nullptr && a_turn->get_dynamics() == nullptr))
						{
							//check degree sign
							if ((degree_ != nullptr && degree_->all_types_equal(a_turn->get_degree()))
								|| (degree_ == nullptr && a_turn->get_degree() == nullptr))
							{
								return true;
							}
						}
					}

					return false;
				}

				std::vector<double> turn_symbol::feature_vector(double hierarchy_factor) const
				{
					std::vector<double> result;

					std::vector<double> fvec_dyn;

					if (nullptr != dynamics_)
					{
						fvec_dyn = dynamics_->feature_vector(std::pow(hierarchy_factor, 2));
					}

					std::vector<double> fvec_deg;

					if (nullptr != degree_)
					{
						fvec_deg = degree_->feature_vector(std::pow(hierarchy_factor, 2));
					}

					result.insert(result.end(), fvec_dyn.begin(), fvec_dyn.end());
					result.insert(result.end(), fvec_deg.begin(), fvec_deg.end());

					result.push_back(hierarchy_factor * e_turn_direction_c::to_int(direction_) / (double) e_turn_direction_c::max());

					return result;
				}

				std::vector<std::type_index> turn_symbol::get_type_path() const
				{
					std::vector<std::type_index> result;
					result.push_back(std::type_index(typeid(mae::fl::laban::mv::i_symbol)));
					result.push_back(std::type_index(typeid(mae::fl::laban::mv::turn_symbol)));
					return result;
				}

				std::string turn_symbol::xml(unsigned int indent, std::string namesp) const
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

					//print turn symbol
					sstr << indent_stream.str() << "<" << ns << "turn>" << std::endl;

					if (dynamics_ != nullptr)
					{
						sstr << dynamics_->xml(indent+1, namesp);
					}

					sstr << indent_stream.str() << "\t" << "<" << ns << "direction>" << e_turn_direction_c::str(direction_) << "</" << ns << "direction>" << std::endl;


					if (degree_ != nullptr)
					{
						sstr << indent_stream.str() << "\t<" << ns << "degree>" << std::endl;
						sstr << degree_->xml(indent+2, namesp, true);
						sstr << indent_stream.str() << "\t</" << ns << "degree>" << std::endl;
					}


					sstr << indent_stream.str() << "</" << ns << "turn>" << std::endl;

					return sstr.str();

				}

				std::string turn_symbol::svg(std::string identifier, double posx, double posy, double width, double height, bool left) const
				{
					if (direction_ == e_turn_direction::NONE_TURN_DIRECTION)
					{
						return "";
					}

					std::stringstream sstr;

					if (direction_ == e_turn_direction::CLOCKWISE || direction_ == e_turn_direction::ANY)
					{
						sstr << "\t\t<path" << std::endl;
						sstr << "\t\t\td=\"m " << posx << "," << posy+height/3.0 << " " << width << "," << -height/3.0 << " " << 0 << "," << 2*height/3.0 << " " << -width << "," << height/3.0 << " " << 0 << "," << -2*height/3.0 << " z\"" << std::endl;
				        sstr << "\t\t\tid=\"" << identifier << "-clockwise\"" << std::endl;
						sstr << "\t\t\tstyle=\"";
						sstr << "fill:#ffffff;fill-opacity:1;stroke:#000000;stroke-width:2pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none";
						sstr << "\" />" << std::endl;
					}

					if (direction_ == e_turn_direction::COUNTER_CLOCKWISE || direction_ == e_turn_direction::ANY)
					{
						sstr << "\t\t<path" << std::endl;
						sstr << "\t\t\td=\"m " << posx+width << "," << posy+height/3.0 << " " << -width << "," << -height/3.0 << " " << 0 << "," << 2*height/3.0 << " " << width << "," << height/3.0 << " " << 0 << "," << -2*height/3.0 << " z\"" << std::endl;
				        sstr << "\t\t\tid=\"" << identifier << "-counterclockwise\"" << std::endl;
						sstr << "\t\t\tstyle=\"";
						sstr << "fill:#ffffff;fill-opacity:1;stroke:#000000;stroke-width:2pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none";
						sstr << "\" />" << std::endl;
					}

					if (degree_ != nullptr)
					{
						//draw the pin
						double pin_x = posx+width/2.0-width/3.0;
						double pin_y = posy+height/2.0-width/3.0;
						double pin_w = width/1.5;
						double pin_h = width/1.5;

						if (height < pin_h)
						{
							pin_w = height;
							pin_h = height;
						}

						std::string pin_id = identifier;
						pin_id.append("-pin");
						sstr << degree_->svg(pin_id, pin_x, pin_y, pin_w, pin_h);
					}

					if (dynamics_ != nullptr)
					{
						//draw dynamics
						double mpin_w = width*0.8;
						double mpin_h = width*0.8;
						double mpin_y = posy + height - mpin_h;
						double mpin_x = posx + width;

						std::string d_id = identifier;
						d_id.append("-dyn");

						sstr << dynamics_->svg(d_id, mpin_x, mpin_y, mpin_w, mpin_h);
					}

					return sstr.str();
				}

				std::string turn_symbol::str() const
				{
					std::stringstream sstr;

					sstr << "(" << e_turn_direction_c::str(direction_) << ")";

					return sstr.str();
				}

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
