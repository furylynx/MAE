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

					if (level == e_level::NONE)
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

				std::string pin::xml(unsigned int indent)
				{
					std::stringstream indent_stream;

					for (unsigned int i = 0; i < indent; i++)
					{
						indent_stream << "\t";
					}

					std::stringstream sstr;

					//print accent sign
					sstr << indent_stream.str() << "<vertical>" << e_level_str::str(level_) << "</vertical>" << std::endl;
					sstr << indent_stream.str() << "<horizontal>" << horizontal_ << "</horizontal>" << std::endl;

					return sstr.str();

				}


			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
