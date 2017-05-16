#include "surface_part.hpp"

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
					std::stringstream sstr;

					//TODO

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

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae
