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
				std::string e_direction_c::str(e_direction direction)
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

				e_direction e_direction_c::dir(e_fl_direction direction)
				{
					if (
							direction == e_fl_direction::P_H	||
							direction == e_fl_direction::P_M	||
							direction == e_fl_direction::P_L
					)
					{
						return e_direction::PLACE;
					}
					else if (
							direction == e_fl_direction::L_H	||
							direction == e_fl_direction::L_M	||
							direction == e_fl_direction::L_L
					)
					{
						return e_direction::LEFT;
					}
					else if (
							direction == e_fl_direction::D_F_L_H	||
							direction == e_fl_direction::D_F_L_M	||
							direction == e_fl_direction::D_F_L_L
					)
					{
						return e_direction::LEFT_FORWARD;
					}
					else if (
							direction == e_fl_direction::F_L_H	||
							direction == e_fl_direction::F_L_M	||
							direction == e_fl_direction::F_L_L  ||
							direction == e_fl_direction::F_R_H	||
							direction == e_fl_direction::F_R_M	||
							direction == e_fl_direction::F_R_L
					)
					{
						return e_direction::FORWARD;
					}
					else if (
							direction == e_fl_direction::D_F_R_H	||
							direction == e_fl_direction::D_F_R_M	||
							direction == e_fl_direction::D_F_R_L
					)
					{
						return e_direction::RIGHT_FORWARD;
					}
					else if (
							direction == e_fl_direction::R_H	||
							direction == e_fl_direction::R_M	||
							direction == e_fl_direction::R_L
					)
					{
						return e_direction::RIGHT;
					}
					else if (
							direction == e_fl_direction::D_B_R_H	||
							direction == e_fl_direction::D_B_R_M	||
							direction == e_fl_direction::D_B_R_L
					)
					{
						return e_direction::RIGHT_BACKWARD;
					}
					else if (
							direction == e_fl_direction::B_R_H	||
							direction == e_fl_direction::B_R_M	||
							direction == e_fl_direction::B_R_L  ||
							direction == e_fl_direction::B_L_H	||
							direction == e_fl_direction::B_L_M	||
							direction == e_fl_direction::B_L_L
					)
					{
						return e_direction::BACKWARD;
					}
					else if (
							direction == e_fl_direction::D_B_L_H	||
							direction == e_fl_direction::D_B_L_M	||
							direction == e_fl_direction::D_B_L_L
					)
					{
						return e_direction::LEFT_BACKWARD;
					}
					else if (direction == e_fl_direction::INVALID)
					{
						return e_direction::NONE;
					}



					throw std::invalid_argument("Enum value not listed in the dir() method");
				}

				std::vector<e_direction> e_direction_c::vec()
				{
					std::vector<e_direction> result;
					result.push_back(e_direction::NONE         	);
					result.push_back(e_direction::PLACE        	);
					result.push_back(e_direction::FORWARD      	);
					result.push_back(e_direction::BACKWARD     	);
					result.push_back(e_direction::LEFT         	);
					result.push_back(e_direction::RIGHT        	);
					result.push_back(e_direction::LEFT_FORWARD  );
					result.push_back(e_direction::LEFT_BACKWARD );
					result.push_back(e_direction::RIGHT_FORWARD );
					result.push_back(e_direction::RIGHT_BACKWARD);

					return result;
				}

				e_direction e_direction_c::parse(std::string str)
				{
					std::string str_l = mstr::to_lower(str);

					std::vector<e_direction> v = e_direction_c::vec();

					for (unsigned int i = 0; i < v.size(); i++)
					{
						std::string t = e_direction_c::str(v.at(i));
						if (str_l == mstr::to_lower(t))
						{
							return v.at(i);
						}
					}

					throw std::invalid_argument("Could not parse the given value since no match was found.");
				}

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
