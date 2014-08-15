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

				bool space_measurement::equals(std::shared_ptr<i_degree_sign> a)
				{
					if (std::shared_ptr<space_measurement> a_space = std::dynamic_pointer_cast<space_measurement>(a))
					{
						if (type_ == a_space->get_type() && degree_ == a_space->get_degree()
								&& direction_ == a_space->get_direction())
						{
							return true;
						}
					}

					return false;
				}

				std::string space_measurement::xml(unsigned int indent, std::string namesp)
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

					//print accent sign
					sstr << indent_stream.str() << "<" << ns << "spaceMeasurement>" << std::endl;

					sstr << indent_stream.str() << "\t" << "<" << ns << "type>" << e_space_c::str(type_) << "</" << ns
							<< "type>" << std::endl;
					sstr << indent_stream.str() << "\t" << "<" << ns << "degree>" << degree_ << "</" << ns << "degree>"
							<< std::endl;

					if (direction_ != e_space_direction::NONE)
					{
						sstr << indent_stream.str() << "\t" << "<" << ns << "direction>"
								<< e_space_direction_c::str(direction_) << "</" << ns << "direction>" << std::endl;
					}

					sstr << indent_stream.str() << "</" << ns << "spaceMeasurement>" << std::endl;

					return sstr.str();

				}

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
