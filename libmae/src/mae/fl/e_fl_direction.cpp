/*
 * e_fl_direction.cpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#include "e_fl_direction.hpp"

namespace mae
{
	namespace fl
	{

		std::string e_fl_direction_c::str(e_fl_direction direction)
		{
			switch (direction)
			{
			case e_fl_direction::INVALID : return "INVALID";
			case e_fl_direction::P_H     : return "PLACE HIGH";
			case e_fl_direction::P_M     : return "PLACE MID";
	        case e_fl_direction::P_L     : return "PLACE LOW";
	        case e_fl_direction::L_H     : return "LEFT HIGH";
			case e_fl_direction::L_M     : return "LEFT MID";
			case e_fl_direction::L_L     : return "LEFT LOW";
			case e_fl_direction::D_F_L_H : return "DIAGONAL FRONT LEFT HIGH";
			case e_fl_direction::D_F_L_M : return "DIAGONAL FRONT LEFT MID";
			case e_fl_direction::D_F_L_L : return "DIAGONAL FRONT LEFT LOW";
			case e_fl_direction::F_L_H   : return "FRONT LEFT HIGH";
			case e_fl_direction::F_L_M   : return "FRONT LEFT MID";
			case e_fl_direction::F_L_L   : return "FRONT LEFT LOW";
			case e_fl_direction::F_R_H   : return "FRONT RIGHT HIGH";
			case e_fl_direction::F_R_M   : return "FRONT RIGHT MID";
			case e_fl_direction::F_R_L   : return "FRONT RIGHT LOW";
			case e_fl_direction::D_F_R_H : return "DIAGONAL FRONT RIGHT HIGH";
			case e_fl_direction::D_F_R_M : return "DIAGONAL FRONT RIGHT MID";
			case e_fl_direction::D_F_R_L : return "DIAGONAL FRONT RIGHT LOW";
			case e_fl_direction::R_H     : return "RIGHT HIGH";
			case e_fl_direction::R_M     : return "RIGHT MID";
			case e_fl_direction::R_L     : return "RIGHT LOW";
	        case e_fl_direction::D_B_R_H : return "DIAGONAL BACK RIGHT HIGH";
	        case e_fl_direction::D_B_R_M : return "DIAGONAL BACK RIGHT MID";
	        case e_fl_direction::D_B_R_L : return "DIAGONAL BACK RIGHT LOW";
			case e_fl_direction::B_R_H   : return "BACK RIGHT HIGH";
			case e_fl_direction::B_R_M   : return "BACK RIGHT MID";
			case e_fl_direction::B_R_L   : return "BACK RIGHT LOW";
			case e_fl_direction::B_L_H   : return "BACK LEFT HIGH";
			case e_fl_direction::B_L_M   : return "BACK LEFT MID";
			case e_fl_direction::B_L_L   : return "BACK LEFT LOW";
			case e_fl_direction::D_B_L_H : return "DIAGONAL BACK LEFT HIGH";
	        case e_fl_direction::D_B_L_M : return "DIAGONAL BACK LEFT MID";
			case e_fl_direction::D_B_L_L : return "DIAGONAL BACK LEFT LOW";
			}

			throw std::invalid_argument("Enum value not listed in the str() method");

		}

		int e_fl_direction_c::to_int(e_fl_direction direction)
		{
			return (int) direction;
		}

		std::vector<e_fl_direction> e_fl_direction_c::vec()
		{
			std::vector<e_fl_direction> result;

			result.push_back(e_fl_direction::INVALID  );
			result.push_back(e_fl_direction::P_H      );
			result.push_back(e_fl_direction::P_M      );
			result.push_back(e_fl_direction::P_L      );
			result.push_back(e_fl_direction::L_H      );
			result.push_back(e_fl_direction::L_M      );
			result.push_back(e_fl_direction::L_L      );
			result.push_back(e_fl_direction::D_F_L_H  );
			result.push_back(e_fl_direction::D_F_L_M  );
			result.push_back(e_fl_direction::D_F_L_L  );
			result.push_back(e_fl_direction::F_L_H    );
			result.push_back(e_fl_direction::F_L_M    );
			result.push_back(e_fl_direction::F_L_L    );
			result.push_back(e_fl_direction::F_R_H    );
			result.push_back(e_fl_direction::F_R_M    );
			result.push_back(e_fl_direction::F_R_L    );
			result.push_back(e_fl_direction::D_F_R_H  );
			result.push_back(e_fl_direction::D_F_R_M  );
			result.push_back(e_fl_direction::D_F_R_L  );
			result.push_back(e_fl_direction::R_H      );
			result.push_back(e_fl_direction::R_M      );
			result.push_back(e_fl_direction::R_L      );
			result.push_back(e_fl_direction::D_B_R_H  );
			result.push_back(e_fl_direction::D_B_R_M  );
			result.push_back(e_fl_direction::D_B_R_L  );
			result.push_back(e_fl_direction::B_R_H    );
			result.push_back(e_fl_direction::B_R_M    );
			result.push_back(e_fl_direction::B_R_L    );
			result.push_back(e_fl_direction::B_L_H    );
			result.push_back(e_fl_direction::B_L_M    );
			result.push_back(e_fl_direction::B_L_L    );
			result.push_back(e_fl_direction::D_B_L_H  );
			result.push_back(e_fl_direction::D_B_L_M  );
			result.push_back(e_fl_direction::D_B_L_L  );

			return result;

		}

	} // namespace fl
} // namespace mae
