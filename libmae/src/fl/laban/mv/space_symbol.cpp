/*
 * space_symbol.cpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

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

				std::shared_ptr<i_dynamics_sign> space_symbol::get_dynamics()
				{
					return dynamics_;
				}

				std::shared_ptr<space_measurement> space_symbol::get_space_measurement()
				{
					return space_measurement_;
				}

				std::string space_symbol::xml(unsigned int indent)
				{
					std::stringstream indent_stream;

					for (unsigned int i = 0; i < indent; i++)
					{
						indent_stream << "\t";
					}

					std::stringstream sstr;

					//print accent sign
					sstr << indent_stream.str() << "<space>" << std::endl;

					if (dynamics_ != nullptr)
					{
						sstr << dynamics_->xml(indent+1);
					}

					sstr << space_measurement_->xml(indent+1);

					sstr << indent_stream.str() << "</space>" << std::endl;

					return sstr.str();
				}

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
