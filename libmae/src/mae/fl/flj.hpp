/*
 * FLJ.hpp
 *
 *  Created on: 04.06.2014
 *      Author: keks
 */

#ifndef FLJ_HPP_
#define FLJ_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
//...

//global includes
#include <vector>

namespace mae {
	namespace fl{
			enum flj
			{
				FLJ_INVALID = 0,
				FLJ_HEAD,
				FLJ_LEFT_UPPER_ARM,
				FLJ_LEFT_FOREARM,
				FLJ_LEFT_WHOLE_ARM,
				FLJ_RIGHT_UPPER_ARM,
				FLJ_RIGHT_FOREARM,
				FLJ_RIGHT_WHOLE_ARM,
				FLJ_LEFT_THIGH, //Oberschenkel
				FLJ_LEFT_SHANK, //Unterschenkel
				FLJ_LEFT_WHOLE_LEG,
				FLJ_RIGHT_THIGH, //Oberschenkel
				FLJ_RIGHT_SHANK, //Unterschenkel
				FLJ_RIGHT_WHOLE_LEG,
				FLJ_SIZE,
			};

			static const char* flj_str[FLJ_SIZE] = {
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

			static std::vector<int> get_flj_ids()
			{
				std::vector<int> result;
				for ( int joint_id = FLJ_INVALID+1; joint_id != FLJ_SIZE; joint_id++ )
				{
				   result.push_back(joint_id);
				}

				return result;
			}
	} //namespace fl
} //namespace mae


#endif // FLJ_HPP_
