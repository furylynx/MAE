#include "joint_part.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{

				joint_part::joint_part(e_joint joint)
				{
					joint_ = joint;
				}

				joint_part::~joint_part()
				{
				}

				e_joint joint_part::get_joint() const
				{
					return joint_;
				}

				std::string joint_part::xml(unsigned int indent, std::string namesp) const
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
					sstr << indent_stream.str() << "<" << ns << "joint>" << std::endl;

					//print joint
					sstr << indent_stream.str() << "\t" << "<" << ns << "joint>" << e_joint_c::str(joint_) << "</" << ns << "joint>" << std::endl;

					sstr << indent_stream.str() << "</" << ns << "joint>" << std::endl;

					return sstr.str();
				}

				std::string joint_part::svg(std::string identifier, double posx, double posy, double width, double height, bool left) const
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

					if (joint_ == e_joint::SHOULDER)
					{
						sstr << "d=\"m " << posx + (width / 4.0) << "," << posy + height << " " << 0 << "," << -height << " "
							 << width / 2.0 << "," << height / 3.0 << "\"" << std::endl;
					}
					else if (joint_ == e_joint::ELBOW)
					{
                        sstr << "d=\"m " << posx + (width / 4.0) << "," << posy + (height / 4.0) << " " << -width / 2.0 << "," << -height / 4.0
                             << "  " << 0 << "," << 3 * height / 4.0 << " " << width / 2.0 << "," << height / 4.0
                             << "\"" << std::endl;
					}
					else if (joint_ == e_joint::WRIST)
					{
                        sstr << "d=\"m " << posx + (width / 4.0) << "," << posy + (height / 4.0) << " " << -width / 2.0 << "," << -height / 4.0
                             << "  " << 0 << "," << 3 * height / 4.0 << " " << width / 2.0 << "," << height / 4.0
                             << " m " << -width / 2.0 << "," << -2.5 * height / 4.0 << " " << width / 2.0
                             << "," << height / 4.0 << "\"" << std::endl;
                        //done
					}
					else if (joint_ == e_joint::HAND)
					{
                        sstr << "d=\"m " << posx + (width / 4.0) << "," << posy + (height / 4.0) << " " << -width / 2.0 << "," << -height / 4.0
                             << "  " << 0 << "," << 3 * height / 4.0 << " " << width / 2.0 << "," << height / 4.0
                             << " m " << 0 << "," << -3 * height / 12.0 << " " << -width / 2.0 << "," << -height / 4.0
                             << " m " << 0 << "," << -3 * height / 12.0 << " " << width / 2.0 << "," << height / 4.0
                             << "\"" << std::endl;
					}
					else if (joint_ == e_joint::FINGERS)
					{
                        sstr << "d=\"m " << posx + (width / 4.0) << "," << posy + (height / 4.0) << " " << -width / 2.0 << "," << -height / 4.0
                             << "  " << 0 << "," << 3 * height / 4.0 << " " << width / 2.0 << "," << height / 4.0
                             << " m " << 0 << "," << -3 * height / 16.0 << " " << -width / 2.0 << "," << -height / 4.0
                             << " m " << 0 << "," << -3 * height / 16.0 << " " << width / 2.0 << "," << height / 4.0
                             << " m " << 0 << "," << -3 * height / 16.0 << " " << -width / 2.0 << "," << -height / 4.0
                             << "\"" << std::endl;
					}
					else if (joint_ == e_joint::HIP)
					{
						sstr << "d=\"m " << posx + (width / 4.0) << "," << posy + height << " " << 0 << "," << -height
						     << " m  " << 0 << "," << height / 3.0 << " " << width / 2.0 << "," << 0
						     << "\"" << std::endl;
					}
					else if (joint_ == e_joint::KNEE)
					{
                        sstr << "d=\"m " << posx + (width / 4.0) << "," << posy + height << " " << 0 << "," << -height
                             << " m  " << 0 << "," << height / 3.0 << " " << width / 2.0 << "," << 0
                             << " m  " << 0 << "," << height / 3.0 << " " << -width / 2.0 << "," << 0
                             << "\"" << std::endl;
					}
					else if (joint_ == e_joint::ANKLE)
					{
                        sstr << "d=\"m " << posx + (width / 4.0) << "," << posy + height << " " << 0 << "," << -height
                             << " m  " << 0 << "," << height / 4.0 << " " << width / 2.0 << "," << 0
                             << " m  " << 0 << "," << height / 4.0 << " " << -width / 2.0 << "," << 0
                             << " m  " << 0 << "," << height / 4.0 << " " << width / 2.0 << "," << 0
                             << "\"" << std::endl;
					}
					else if (joint_ == e_joint::FOOT)
					{
                        sstr << "d=\"m " << posx + (width / 4.0) << "," << posy + height << " " << 0 << "," << -height
                             << " m  " << 0 << "," << height / 5.0 << " " << width / 2.0 << "," << 0
                             << " m  " << 0 << "," << height / 5.0 << " " << -width / 2.0 << "," << 0
                             << " m  " << 0 << "," << height / 5.0 << " " << width / 2.0 << "," << 0
                             << " m  " << 0 << "," << height / 5.0 << " " << -width / 2.0 << "," << 0
                             << "\"" << std::endl;
					}
					else if (joint_ == e_joint::TOES)
					{
                        sstr << "d=\"m " << posx + (width / 4.0) << "," << posy + height << " " << 0 << "," << -height
                             << " m  " << 0 << "," << height / 6.0 << " " << width / 2.0 << "," << 0
                             << " m  " << 0 << "," << height / 6.0 << " " << -width / 2.0 << "," << 0
                             << " m  " << 0 << "," << height / 6.0 << " " << width / 2.0 << "," << 0
                             << " m  " << 0 << "," << height / 6.0 << " " << -width / 2.0 << "," << 0
                             << " m  " << 0 << "," << height / 6.0 << " " << width / 2.0 << "," << 0
                             << "\"" << std::endl;
					}

					if (left)
					{
					    //mirror horizontally
						sstr << "transform=\"matrix(-1,0,0,1," << 2 * posx + width << ",0)\"" << std::endl; //transform=\"translate(" << -width << "), scale(-1, 1)
					}

					sstr << "\t\t\tid=\"" << identifier << "customlimb\"" << std::endl;
					sstr
							<< "\t\t\tstyle=\"fill:none;stroke:#000000;stroke-width:2pt;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\""
							<< std::endl;
					sstr << "\t\t\t/>" << std::endl;

					return sstr.str();

					return sstr.str();
				}

				bool joint_part::equals(std::shared_ptr<i_endpoint> a) const
				{
					if (std::shared_ptr<joint_part> a_casted = std::dynamic_pointer_cast<joint_part>(a))
					{
						return (joint_ == a_casted->get_joint());
					}

					return false;
				}

				bool joint_part::equals(std::shared_ptr<i_part> a) const
				{
					if (std::shared_ptr<i_endpoint> a_casted = std::dynamic_pointer_cast<i_endpoint>(a))
					{
						return equals(a_casted);
					}

					return false;
				}

				bool joint_part::all_types_equal(std::shared_ptr<i_endpoint> a) const
				{
					if (std::shared_ptr<joint_part> a_casted = std::dynamic_pointer_cast<joint_part>(a))
					{
						return true;
					}

					return false;
				}

				bool joint_part::all_types_equal(std::shared_ptr<i_part> a) const
				{
					if (std::shared_ptr<i_endpoint> a_casted = std::dynamic_pointer_cast<i_endpoint>(a))
					{
						return all_types_equal(a_casted);
					}

					return false;
				}

				std::vector<double> joint_part::feature_vector(double hierarchy_factor) const
				{
					std::vector<double> result;

					result.push_back(hierarchy_factor * e_joint_c::to_int(joint_)/(double) e_joint_c::max());

					return result;
				}

				std::shared_ptr<i_endpoint> joint_part::get_fixed_end() const
				{
					if (joint_ == e_joint::FINGERS)
					{
						return std::shared_ptr<i_endpoint>(new joint_part(e_joint::HAND));
					}
					else if (joint_ == e_joint::HAND)
					{
						return std::shared_ptr<i_endpoint>(new joint_part(e_joint::WRIST));
					}
					else if (joint_ == e_joint::WRIST)
					{
						return std::shared_ptr<i_endpoint>(new joint_part(e_joint::ELBOW));
					}
					else if (joint_ == e_joint::ELBOW)
					{
						return std::shared_ptr<i_endpoint>(new joint_part(e_joint::SHOULDER));
					}
					else if (joint_ == e_joint::TOES)
					{
						return std::shared_ptr<i_endpoint>(new joint_part(e_joint::FOOT));
					}
					else if (joint_ == e_joint::FOOT)
					{
						return std::shared_ptr<i_endpoint>(new joint_part(e_joint::ANKLE));
					}
					else if (joint_ == e_joint::ANKLE)
					{
						return std::shared_ptr<i_endpoint>(new joint_part(e_joint::KNEE));
					}
					else if (joint_ == e_joint::KNEE)
					{
						return std::shared_ptr<i_endpoint>(new joint_part(e_joint::HIP));
					}
					else if (joint_ == e_joint::SHOULDER || joint_ == e_joint::HIP)
					{
						throw std:: invalid_argument("Shoulder or hip cannot be extremity joints.");
					}
					else
					{
						throw std:: invalid_argument("Invalid joint.");
					}
				}

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae
