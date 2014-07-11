/*
 * e_direction.cpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#include "e_direction.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{
				std::string e_direction_str::str(e_direction direction)
				{
					switch (direction)
					{
					case e_direction::NONE         		: return "none";
					case e_direction::PLACE        		: return "place";
					case e_direction::FORWARD      		: return "forward";
					case e_direction::BACKWARD     		: return "backward";
					case e_direction::LEFT         		: return "left";
					case e_direction::RIGHT        		: return "right";
                    case e_direction::LEFT_FORWARD     	: return "left-forward";
                    case e_direction::LEFT_BACKWARD    	: return "left-backward";
                    case e_direction::RIGHT_FORWARD    	: return "right-forward";
                    case e_direction::RIGHT_BACKWARD    : return "right-backward";
					}

					throw std::invalid_argument("Enum value not listed in the str() method");
				}



			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
