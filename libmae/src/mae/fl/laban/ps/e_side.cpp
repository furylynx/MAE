/*
 * e_side.cpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#include "e_side.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{

				std::string e_side_c::str(e_side e_side_)
				{
					switch (e_side_)
					{
					case e_side::NONE:
						return "none";
					case e_side::LEFT:
						return "left";
					case e_side::RIGHT:
						return "right";
					}

					throw std::invalid_argument("Enum value not listed in the str() method");
				}

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae
