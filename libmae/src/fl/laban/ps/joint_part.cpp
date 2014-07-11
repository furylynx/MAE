/*
 * joint_part.cpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

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

				e_joint joint_part::get_joint()
				{
					return joint_;
				}

				std::string joint_part::xml(unsigned int indent)
				{
					std::stringstream indent_stream;

					for (unsigned int i = 0; i < indent; i++)
					{
						indent_stream << "\t";
					}

					std::stringstream sstr;

					//print definition
					sstr << indent_stream.str() << "<joint>" << std::endl;

					//print joint
					sstr << indent_stream.str() << "\t" << "<joint>" << e_joint_str::str(joint_) << "</joint>" << std::endl;

					sstr << indent_stream.str() << "</joint>" << std::endl;

					return sstr.str();
				}

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae
