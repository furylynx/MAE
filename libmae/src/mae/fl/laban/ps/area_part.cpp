/*
 * area_part.cpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#include "area_part.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{

				area_part::area_part(e_area area)
				{
					area_ = area;
				}

				area_part::~area_part()
				{
				}

				e_area area_part::get_area() const
				{
					return area_;
				}

				std::string area_part::xml(unsigned int indent, std::string namesp)  const
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

					//print side
					sstr << indent_stream.str() << "<" << ns << "part>" << e_area_c::str(area_) << "</" << ns << "part>" << std::endl;

					return sstr.str();
				}

				std::string area_part::svg(std::string identifier, double posx, double posy, double width, double height, bool left) const
				{
					std::stringstream sstr;

					//TODO

					return sstr.str();
				}

				std::shared_ptr<i_endpoint> area_part::get_fixed_end() const
				{
					std::shared_ptr<i_endpoint> result;

					//TODO

					return result;
				}

				bool area_part::equals(std::shared_ptr<i_endpoint> a) const
				{
					if (std::shared_ptr<area_part> a_casted = std::dynamic_pointer_cast<area_part>(a))
					{
						return (area_ == a_casted->get_area());
					}

					return false;
				}

				bool area_part::equals(std::shared_ptr<i_part> a) const
				{
					if (std::shared_ptr<i_endpoint> a_casted = std::dynamic_pointer_cast<i_endpoint>(a))
					{
						return equals(a_casted);
					}

					return false;
				}



			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae
