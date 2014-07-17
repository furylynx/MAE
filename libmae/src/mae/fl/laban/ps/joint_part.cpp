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

				std::string joint_part::xml(unsigned int indent, std::string namesp)
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

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae
