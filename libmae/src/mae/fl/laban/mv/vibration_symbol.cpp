#include "vibration_symbol.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				vibration_symbol::vibration_symbol(std::shared_ptr<pin> displacement1,
						std::shared_ptr<pin> displacement2, std::shared_ptr<i_dynamics_sign> dynamics)
				{
					displacement1_ = displacement1;
					displacement2_ = displacement2;

					dynamics_ = dynamics;

					if (displacement1 == nullptr || displacement2 == nullptr)
					{
						throw std::invalid_argument("Displacements must not be null");
					}

				}

				vibration_symbol::~vibration_symbol()
				{
				}

				std::shared_ptr<i_dynamics_sign> vibration_symbol::get_dynamics() const
				{
					return dynamics_;
				}

				std::shared_ptr<pin> vibration_symbol::get_displacement1() const
				{
					return displacement1_;
				}

				std::shared_ptr<pin> vibration_symbol::get_displacement2() const
				{
					return displacement2_;
				}

				bool vibration_symbol::equals(std::shared_ptr<i_symbol> a) const
				{
					if (std::shared_ptr<vibration_symbol> a_vib = std::dynamic_pointer_cast<vibration_symbol>(a))
					{
						//check dynamics sign
						if ((dynamics_ != nullptr && dynamics_->equals(a_vib->get_dynamics()))
								|| (dynamics_ == nullptr && a_vib->get_dynamics() == nullptr))
						{
							//check space measurement
							if ((displacement1_->equals(a_vib->get_displacement1())
									&& displacement2_->equals(a_vib->get_displacement2()))
									|| (displacement1_->equals(a_vib->get_displacement2())
											&& displacement2_->equals(a_vib->get_displacement1())))
							{
								return true;
							}
						}
					}

					return false;
				}

				bool vibration_symbol::all_types_equal(std::shared_ptr<i_symbol> a) const
				{
					if (std::shared_ptr<vibration_symbol> a_vib = std::dynamic_pointer_cast<vibration_symbol>(a))
					{
						//check dynamics sign
						if ((dynamics_ != nullptr && dynamics_->all_types_equal(a_vib->get_dynamics()))
							|| (dynamics_ == nullptr && a_vib->get_dynamics() == nullptr))
						{
							//check space measurement
							if ((displacement1_->all_types_equal(a_vib->get_displacement1())
								 && displacement2_->all_types_equal(a_vib->get_displacement2()))
								|| (displacement1_->all_types_equal(a_vib->get_displacement2())
									&& displacement2_->all_types_equal(a_vib->get_displacement1())))
							{
								return true;
							}
						}
					}

					return false;
				}

				std::vector<double> vibration_symbol::feature_vector(double hierarchy_factor) const
				{
					std::vector<double> result;

					std::vector<double> fvec_dyn;

					if (nullptr != dynamics_)
					{
						fvec_dyn = dynamics_->feature_vector(std::pow(hierarchy_factor, 2));
					}

					std::vector<double> fvec_dis1;

					if (nullptr != displacement1_)
					{
						fvec_dis1 = displacement1_->feature_vector(std::pow(hierarchy_factor, 2));
					}

					std::vector<double> fvec_dis2;

					if (nullptr != displacement2_)
					{
						fvec_dis2 = displacement2_->feature_vector(std::pow(hierarchy_factor, 2));
					}

					result.insert(result.end(), fvec_dyn.begin(), fvec_dyn.end());
					result.insert(result.end(), fvec_dis1.begin(), fvec_dis1.end());
					result.insert(result.end(), fvec_dis2.begin(), fvec_dis2.end());

					return result;
				}

				std::vector<std::type_index> vibration_symbol::get_type_path() const
				{
					std::vector<std::type_index> result;
					result.push_back(std::type_index(typeid(mae::fl::laban::mv::i_symbol)));
					result.push_back(std::type_index(typeid(mae::fl::laban::mv::vibration_symbol)));

					return result;
				}

				std::string vibration_symbol::xml(unsigned int indent, std::string namesp) const
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

					//print vibration symbol
					sstr << indent_stream.str() << "<" << ns << "vibration>" << std::endl;

					if (dynamics_ != nullptr)
					{
						sstr << dynamics_->xml(indent + 1, namesp);
					}

					//print displacements
					sstr << indent_stream.str() << "\t" << "<" << ns << "displacement>" << std::endl;
					sstr << displacement1_->xml(indent + 1, namesp);
					sstr << indent_stream.str() << "\t" << "</" << ns << "displacement>" << std::endl;

					sstr << indent_stream.str() << "\t" << "<" << ns << "displacement>" << std::endl;
					sstr << displacement2_->xml(indent + 1, namesp);
					sstr << indent_stream.str() << "\t" << "</" << ns << "displacement>" << std::endl;

					sstr << indent_stream.str() << "</" << ns << "vibration>" << std::endl;

					return sstr.str();

				}

				std::string vibration_symbol::svg(std::string identifier, double posx, double posy, double width, double height, bool left) const
				{
					return svg(identifier, draw_rect(posx, posy, width, height), left);
				}

				std::string vibration_symbol::svg(std::string identifier, draw_rect rect, bool left, svg_style style) const
				{
					double posx = rect.get_posx();
					double posy = rect.get_posy();
					double width = rect.get_width();
					double height = rect.get_height();

					identifier.append("-vibration");

					std::stringstream sstr;

					unsigned int loops = 0;
					double circ_r = width/4.0;
					if (height-2*width > 0)
					{
						loops = (int)((height-2*width)/(width/2.0));
					}

					//draw vibration snake line
					sstr << "\t\t<path" << std::endl;
					sstr << "\t\t\td=\"m " << posx + width / 2.0 << "," << posy + height-2*width << "";

					for (unsigned int i = 0; i < loops; i++)
					{
						if (i % 2 == 0)
						{
							sstr << " c " << -circ_r *1.25 << "," << 0 << " " << -circ_r *1.25 << "," << -circ_r*2.0 << " " << 0 << "," << -circ_r*2.0 << "";
						}
						else
						{
							sstr << " c " << circ_r *1.25 << "," << 0 << " " << circ_r *1.25 << "," << -circ_r*2.0 << " " << 0 << "," << -circ_r*2.0 << "";
						}
					}
					sstr << "\"" << std::endl;
					sstr << "\t\t\tid=\"" << identifier << "-snake\"" << std::endl;
					sstr
							<< "\t\t\tstyle=\"fill:none;fill-opacity:1;stroke:#000000;stroke-width:2pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none";
					sstr << "\" />" << std::endl;

					std::string dsp1id = identifier;
					dsp1id.append("-displacement1");
					sstr << displacement1_->svg(dsp1id, posx, posy+height-2*width, width, width);

					std::string dsp2id = identifier;
					dsp2id.append("-displacement2");
					sstr << displacement2_->svg(dsp2id, posx, posy+height-width, width, width);

					return sstr.str();
				}

				std::string vibration_symbol::str() const
				{
					std::stringstream sstr;

					sstr << "(VIBRATION)";

					return sstr.str();
				}

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
