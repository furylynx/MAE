#include "cancellation_symbol.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				cancellation_symbol::cancellation_symbol(e_cancel cancel)
				{
					cancel_ = cancel;

					if (cancel == e_cancel::NONE_CANCEL)
					{
						throw std::invalid_argument("Cancel must not be NONE.");
					}
				}

				cancellation_symbol::~cancellation_symbol()
				{
				}

				e_cancel cancellation_symbol::get_cancel() const
				{
					return cancel_;
				}

				bool cancellation_symbol::equals(std::shared_ptr<i_symbol> a) const
				{
					if (std::shared_ptr<cancellation_symbol> a_c = std::dynamic_pointer_cast<cancellation_symbol>(a))
					{
						if (a_c->get_cancel() == cancel_)
						{
							return true;
						}
					}

					return false;
				}

				std::vector<double> cancellation_symbol::feature_vector() const
				{
					std::vector<double> result;

					result.push_back(e_cancel_c::to_int(cancel_));

					return result;
				}

				std::string cancellation_symbol::xml(unsigned int indent, std::string namesp) const
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

					//print cancel symbol
					sstr << indent_stream.str() << "<" << ns << "cancel>" << std::endl;

					sstr << indent_stream.str() << "\t" << "<" << ns << "cancel>" << e_cancel_c::str(cancel_) << "</" << ns << "cancel>" << std::endl;

					sstr << indent_stream.str() << "</" << ns << "cancel>" << std::endl;

					return sstr.str();

				}

				std::string cancellation_symbol::svg(std::string identifier, double posx, double posy, double width, double height, bool left) const
				{
					std::stringstream sstr;

					height = width;
					posy = posy-height;

					if (cancel_ == e_cancel::BACK_NORMAL)
					{
						double circ_r = width/2.0;

						//draw circle
						sstr << "\t\t<path" << std::endl;
						sstr << "\t\t\td=\"m " << posx + width/2.0 + circ_r << "," << posy+width/2.0 << " a " << circ_r << "," << circ_r << " 0 1 1 -" << circ_r*2.0 << ",0 " << circ_r << "," << circ_r << " 0 1 1 " << circ_r*2 << ",0 z\"" << std::endl;
						sstr << "\t\t\tid=\"" << identifier << "-cancel-backnormal-outer\"" << std::endl;
						sstr << "\t\t\tstyle=\"fill:#ffffff;fill-opacity:1;stroke:#000000;stroke-width:2pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />" << std::endl;

						double center_r = width/12.0;

						//draw circle
					    sstr << "\t\t<path" << std::endl;
					    sstr << "\t\t\td=\"m " << posx + width/2.0 + center_r << "," << posy+width/2.0 << " a " << center_r << "," << center_r << " 0 1 1 -" << center_r*2 << ",0 " << center_r << "," << center_r << " 0 1 1 " << center_r*2 << ",0 z\"" << std::endl;
					    sstr << "\t\t\tid=\"" << identifier << "-cancel-backnormal-inner\"" << std::endl;
					    sstr << "\t\t\tstyle=\"fill:#000000;fill-opacity:1;stroke:none\" />" << std::endl;
					}
					else if (cancel_ == e_cancel::RELEASE_CONTACT)
					{
						double circ_r = width/3.0;

					    sstr << "\t\t<path" << std::endl;
					    sstr << "\t\t\td=\"m " << posx + width/3.0 + circ_r << "," << posy+width/2.0 << " a " << circ_r << "," << circ_r << " 0 1 1 -" << circ_r*2 << ",0\"" << std::endl;
					    sstr << "\t\t\tid=\"" << identifier << "-cancel-release1\"" << std::endl;
					    sstr << "\t\t\tstyle=\"fill:#ffffff;fill-opacity:1;stroke:#000000;stroke-width:2pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />" << std::endl;

					    sstr << "\t\t<path" << std::endl;
					    sstr << "\t\t\td=\"m " << posx + 2*width/3.0 - circ_r << "," << posy+width/2.0 << " a " << circ_r << "," << circ_r << " 0 1 1 " << circ_r*2 << ",0\"" << std::endl;
					    sstr << "\t\t\tid=\"" << identifier << "-cancel-release2\"" << std::endl;
					    sstr << "\t\t\tstyle=\"fill:#ffffff;fill-opacity:1;stroke:#000000;stroke-width:2pt;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />" << std::endl;

					}

					return sstr.str();
				}

				std::string cancellation_symbol::str() const
				{
					std::stringstream sstr;

					sstr << "(" << e_cancel_c::str(cancel_) << ")";

					return sstr.str();
				}

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
