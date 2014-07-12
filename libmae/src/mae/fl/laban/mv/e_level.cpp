/*
 * e_level.cpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#include "e_level.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{
				std::string e_level_c::str(e_level level)
				{
					switch (level)
					{
					case e_level::NONE 		: return "none";
					case e_level::HIGH  		: return "high";
					case e_level::MIDDLE		: return "middle";
					case e_level::LOW    		: return "low";
					}

					throw std::invalid_argument("Enum value not listed in the str() method");
				}

				e_level e_level_c::lvl(e_fl_direction direction)
				{
					if (
							direction == e_fl_direction::P_H 		||
							direction == e_fl_direction::L_H 		||
							direction == e_fl_direction::D_F_L_H 	||
							direction == e_fl_direction::F_L_H 		||
							direction == e_fl_direction::F_R_H 		||
							direction == e_fl_direction::D_F_R_H 	||
							direction == e_fl_direction::R_H 		||
							direction == e_fl_direction::D_B_R_H 	||
							direction == e_fl_direction::B_R_H 		||
							direction == e_fl_direction::B_L_H 		||
							direction == e_fl_direction::D_B_L_H
					)
					{
						return e_level::HIGH;
					}
					else if (
							direction == e_fl_direction::P_M 		||
							direction == e_fl_direction::L_M 		||
							direction == e_fl_direction::D_F_L_M 	||
							direction == e_fl_direction::F_L_M 		||
							direction == e_fl_direction::F_R_M 		||
							direction == e_fl_direction::D_F_R_M 	||
							direction == e_fl_direction::R_M 		||
							direction == e_fl_direction::D_B_R_M 	||
							direction == e_fl_direction::B_R_M 		||
							direction == e_fl_direction::B_L_M 		||
							direction == e_fl_direction::D_B_L_M
					)
					{
						return e_level::MIDDLE;
					}
					else if (
							direction == e_fl_direction::P_L 		||
							direction == e_fl_direction::L_L 		||
							direction == e_fl_direction::D_F_L_L 	||
							direction == e_fl_direction::F_L_L 		||
							direction == e_fl_direction::F_R_L 		||
							direction == e_fl_direction::D_F_R_L 	||
							direction == e_fl_direction::R_L 		||
							direction == e_fl_direction::D_B_R_L 	||
							direction == e_fl_direction::B_R_L 		||
							direction == e_fl_direction::B_L_L 		||
							direction == e_fl_direction::D_B_L_L
					)
					{
						return e_level::LOW;
					}
					else if (direction == e_fl_direction::INVALID)
					{
						return e_level::NONE;
					}

					throw std::invalid_argument("Enum value not listed in the lvl() method");
				}

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
