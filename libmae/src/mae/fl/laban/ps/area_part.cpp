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

				std::string area_part::xml(unsigned int indent)
				{
					std::stringstream indent_stream;

					for (unsigned int i = 0; i < indent; i++)
					{
						indent_stream << "\t";
					}

					std::stringstream sstr;

					//print side
					sstr << indent_stream.str() << "<part>" << e_area_str::str(area_) << "</part>" << std::endl;

					return sstr.str();
				}

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae
