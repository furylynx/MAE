/*
 * space_measurement.cpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#include "space_measurement.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				space_measurement::space_measurement(e_space type, unsigned int degree, e_space_direction direction)
				{
					type_ = type;
					degree_ = degree;
					direction_ = direction;

					if (type_ == e_space::NONE)
					{
						throw std::invalid_argument("Type must not be NONE.");
					}
				}

				space_measurement::~space_measurement()
				{
					// TODO Auto-generated destructor stub
				}

				e_space space_measurement::get_type()
				{
					return type_;
				}

				unsigned int space_measurement::get_degree()
				{
					return degree_;
				}

				e_space_direction space_measurement::get_direction()
				{
					return direction_;
				}

				std::string space_measurement::xml(unsigned int indent)
				{
					std::stringstream indent_stream;

					for (unsigned int i = 0; i < indent; i++)
					{
						indent_stream << "\t";
					}

					std::stringstream sstr;

					//print accent sign
					sstr << indent_stream.str() << "<spaceMeasurement>" << std::endl;

					sstr << indent_stream.str() << "\t" << "<type>" << e_space_str::str(type_) << "</type>" << std::endl;
					sstr << indent_stream.str() << "\t" << "<degree>" << degree_ << "</degree>" << std::endl;

					if (direction_ != e_space_direction::NONE)
					{
						sstr << indent_stream.str() << "\t" << "<direction>" << e_space_direction_str::str(direction_) << "</direction>" << std::endl;
					}

					sstr << indent_stream.str() << "</spaceMeasurement>" << std::endl;

					return sstr.str();

				}


			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
