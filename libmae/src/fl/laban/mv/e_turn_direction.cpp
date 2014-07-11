/*
 * e_turn_direction.cpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#include "e_turn_direction.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{
				std::string e_turn_direction_str::str(e_turn_direction turn)
				{
					switch (turn)
					{
					case e_turn_direction::NONE 				: return "none";
					case e_turn_direction::COUNTER_CLOCKWISE	: return "counterClockwise";
					case e_turn_direction::CLOCKWISE        	: return "clockwise";
					case e_turn_direction::ANY               	: return "any";
					}

				}


			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
