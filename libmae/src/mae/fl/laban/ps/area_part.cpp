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

				e_area area_part::get_area()
				{
					return area_;
				}

				std::string area_part::xml(unsigned int indent, std::string namesp)
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

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae
