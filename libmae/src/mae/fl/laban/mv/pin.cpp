/*
 * pin.cpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#include "pin.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				pin::pin(e_level level, int horizontal)
				{
					level_ = level;
					horizontal_ = horizontal;

					if (level == e_level::NONE_LEVEL)
					{
						throw std::invalid_argument("Level must not be NONE.");
					}

					if (horizontal < -1 || horizontal > 360)
					{
						throw std::invalid_argument("Horizontal must be a value between -1 and 360.");
					}

				}

				pin::~pin()
				{
				}

				e_level pin::get_level()
				{
					return level_;
				}

				int pin::get_horizontal()
				{
					return horizontal_;
				}

				bool pin::equals(std::shared_ptr<i_degree_sign> a)
				{
					if (std::shared_ptr<pin> a_pin = std::dynamic_pointer_cast<pin>(a))
					{
						if (a_pin->get_horizontal() == horizontal_ && a_pin->get_level() == level_)
						{
							return true;
						}
					}

					return false;
				}

				std::string pin::xml(unsigned int indent, std::string namesp)
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

					//print accent sign
					sstr << indent_stream.str() << "<" << ns << "vertical>" << e_level_c::str(level_) << "</" << ns << "vertical>" << std::endl;
					sstr << indent_stream.str() << "<" << ns << "horizontal>" << horizontal_ << "</" << ns << "horizontal>" << std::endl;

					return sstr.str();

				}


			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
