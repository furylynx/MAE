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

				e_joint joint_part::get_joint() const
				{
					return joint_;
				}

				std::string joint_part::xml(unsigned int indent, std::string namesp) const
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

				bool joint_part::equals(std::shared_ptr<i_endpoint> a) const
				{
					if (std::shared_ptr<joint_part> a_casted = std::dynamic_pointer_cast<joint_part>(a))
					{
						return (joint_ == a_casted->get_joint());
					}

					return false;
				}

				bool joint_part::equals(std::shared_ptr<i_part> a) const
				{
					if (std::shared_ptr<i_endpoint> a_casted = std::dynamic_pointer_cast<i_endpoint>(a))
					{
						return equals(a_casted);
					}

					return false;
				}

				std::shared_ptr<i_endpoint> joint_part::get_fixed_end() const
				{
					std::shared_ptr<i_endpoint> result;

					//TODO

					return result;
				}

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae
