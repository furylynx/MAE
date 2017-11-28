#include "space_symbol.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				space_symbol::space_symbol(std::shared_ptr<space_measurement> space_measurement,
						std::shared_ptr<i_dynamics_sign> dynamics)
				{
					dynamics_ = dynamics;
					space_measurement_ = space_measurement;

					if (space_measurement == nullptr)
					{
						throw std::invalid_argument("Space measurement must not be null.");
					}
				}

				space_symbol::~space_symbol()
				{
				}

				std::shared_ptr<i_dynamics_sign> space_symbol::get_dynamics() const
				{
					return dynamics_;
				}

				std::shared_ptr<space_measurement> space_symbol::get_space_measurement() const
				{
					return space_measurement_;
				}

				bool space_symbol::equals(std::shared_ptr<i_symbol> a) const
				{
					if (std::shared_ptr<space_symbol> a_space = std::dynamic_pointer_cast<space_symbol>(a))
					{
						//check dynamics sign
						if ((dynamics_ != nullptr && dynamics_->equals(a_space->get_dynamics()))
								|| (dynamics_ == nullptr && a_space->get_dynamics() == nullptr))
						{
							//check space measurement
							if ((space_measurement_ != nullptr && space_measurement_->equals(a_space->get_space_measurement()))
									|| (space_measurement_ == nullptr && a_space->get_space_measurement() == nullptr))
							{
								return true;
							}
						}

					}

					return false;
				}

				bool space_symbol::all_types_equal(std::shared_ptr<i_symbol> a) const
				{
					if (std::shared_ptr<space_symbol> a_space = std::dynamic_pointer_cast<space_symbol>(a))
					{
						//check dynamics sign
						if ((dynamics_ != nullptr && dynamics_->all_types_equal(a_space->get_dynamics()))
							|| (dynamics_ == nullptr && a_space->get_dynamics() == nullptr))
						{
							//check space measurement
							if ((space_measurement_ != nullptr && space_measurement_->all_types_equal(a_space->get_space_measurement()))
								|| (space_measurement_ == nullptr && a_space->get_space_measurement() == nullptr))
							{
								return true;
							}
						}

					}

					return false;
				}

				std::vector<double> space_symbol::feature_vector(double hierarchy_factor) const
				{
					std::vector<double> result;

					std::vector<double> fvec_dyn;

					if (nullptr != dynamics_)
					{
						fvec_dyn = dynamics_->feature_vector(std::pow(hierarchy_factor,2));
					}

					std::vector<double> fvec_spacem;

					if (nullptr != space_measurement_)
					{
						fvec_spacem = space_measurement_->feature_vector(std::pow(hierarchy_factor, 2));
					}

					result.insert(result.end(), fvec_dyn.begin(), fvec_dyn.end());
					result.insert(result.end(), fvec_spacem.begin(), fvec_spacem.end());

					return result;
				}

				std::vector<std::type_index> space_symbol::get_type_path() const
				{
					std::vector<std::type_index> result;
					result.push_back(std::type_index(typeid(mae::fl::laban::mv::i_symbol)));
					result.push_back(std::type_index(typeid(mae::fl::laban::mv::space_symbol)));

					return result;
				}

				std::string space_symbol::xml(unsigned int indent, std::string namesp) const
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
					sstr << indent_stream.str() << "<" << ns << "space>" << std::endl;

					if (dynamics_ != nullptr)
					{
						sstr << dynamics_->xml(indent+1, namesp);
					}

					sstr << space_measurement_->xml(indent+1, namesp);

					sstr << indent_stream.str() << "</" << ns << "space>" << std::endl;

					return sstr.str();
				}

				std::string space_symbol::svg(std::string identifier, double posx, double posy, double width, double height, bool left) const
				{
					identifier.append("-space_symbol");

					std::stringstream sstr;

					double nheight = height-width;

					if (nheight < 0)
					{
						nheight = 0.01;
					}

					//draw line
					sstr << "\t\t<path" << std::endl;
					sstr << "\t\t\td=\"m " << posx+width/2.0 << "," << posy << " " << 0 << "," << nheight*0.98 << "\""
							<< std::endl;
					sstr << "\t\t\tid=\"" << identifier << "-line\"" << std::endl;
					sstr << "\t\t\tstyle=\"fill:none;fill-opacity:1;stroke:#000000;stroke-width:2pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none";
					sstr << "\" />" << std::endl;

					//draw measurement
					sstr << space_measurement_->svg(identifier, posx, posy+nheight, width, width, left);

					return sstr.str();
				}

				std::string space_symbol::str() const
				{
					return space_measurement_->str();
				}

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
