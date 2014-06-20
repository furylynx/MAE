/*
 * FLJ.hpp
 *
 *  Created on: 04.06.2014
 *      Author: keks
 */

#ifndef MAEB_HPP_
#define MAEB_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
//...

//global includes
#include <vector>

namespace mae {
			enum maeb
			{
				MAEB_INVALID = 0,
				MAEB_HEAD,
				MAEB_LEFT_UPPER_ARM,
				MAEB_LEFT_FOREARM,
				MAEB_LEFT_WHOLE_ARM,
				MAEB_RIGHT_UPPER_ARM,
				MAEB_RIGHT_FOREARM,
				MAEB_RIGHT_WHOLE_ARM,
				MAEB_LEFT_THIGH, //Oberschenkel
				MAEB_LEFT_SHANK, //Unterschenkel
				MAEB_LEFT_WHOLE_LEG,
				MAEB_RIGHT_THIGH, //Oberschenkel
				MAEB_RIGHT_SHANK, //Unterschenkel
				MAEB_RIGHT_WHOLE_LEG,
				MAEB_SIZE,
			};

			static const char* maeb_str[MAEB_SIZE] = {
					"INVALID",
                    "HEAD",
					"LEFT_UPPER_ARM",
					"LEFT_FOREARM",
					"LEFT_WHOLE_ARM",
                    "RIGHT_UPPER_ARM",
					"RIGHT_FOREARM",
					"RIGHT_WHOLE_ARM",
					"LEFT_THIGH", //Oberschenkel
                    "LEFT_SHANK", //Unterschenkel
					"LEFT_WHOLE_LEG",
					"RIGHT_THIGH", //Oberschenkel
					"RIGHT_SHANK", //Unterschenkel
                    "RIGHT_WHOLE_LEG",
					};
} //namespace mae


#endif // FLJ_HPP_
