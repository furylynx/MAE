/*
 * e_space_direction.cpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#include "e_space_direction.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{
				std::string e_space_direction_c::str(e_space_direction space_direction)
				{
					switch (space_direction)
					{
					case e_space_direction::NONE       		: return "none";
					case e_space_direction::LEFT 			: return "left";
					case e_space_direction::FRONT_LEFT 		: return "frontLeft";
					case e_space_direction::FRONT      		: return "front";
					case e_space_direction::FRONT_RIGHT		: return "frontRight";
					case e_space_direction::RIGHT      		: return "right";
					case e_space_direction::BACK_RIGHT 		: return "backRight";
                    case e_space_direction::BACK          	: return "back";
                    case e_space_direction::BACK_LEFT     	: return "backLeft";
					}

					throw std::invalid_argument("Enum value not listed in the str() method");
				}

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
