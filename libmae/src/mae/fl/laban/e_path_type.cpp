/*
 * e_path_type.cpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#include "e_path_type.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			std::string e_path_type_c::str(e_path_type type)
			{
				switch (type)
				{
				case e_path_type::NONE           		: return "none";
				case e_path_type::STRAIGHT     			: return "straight";
				case e_path_type::CIRCULAR_LEFT 		: return "circularLeft";
                case e_path_type::CIRCULAR_RIGHT        : return "circularRight";
                case e_path_type::ANY                   : return "any";
				}

				throw std::invalid_argument("Enum value not listed in the str() method");
			}


		} // namespace laban
	} // namespace fl
} // namespace mae
