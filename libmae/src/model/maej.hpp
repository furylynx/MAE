/*
 * MAEJ.hpp
 *
 *  Created on: 04.06.2014
 *      Author: keks
 */

#ifndef MAEJ_HPP_
#define MAEJ_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
//...

//global includes
//...

namespace mae {
			enum maej
			{
				MAEJ_INVALID = 0,
				MAEJ_HEAD,
				MAEJ_NECK,
				MAEJ_LEFT_SHOULDER,
				MAEJ_LEFT_ELBOW,
				MAEJ_LEFT_HAND,
				MAEJ_RIGHT_SHOULDER,
				MAEJ_RIGHT_ELBOW,
				MAEJ_RIGHT_HAND,
				MAEJ_TORSO,
				MAEJ_LEFT_HIP,
				MAEJ_LEFT_KNEE,
				MAEJ_LEFT_FOOT,
				MAEJ_RIGHT_HIP,
				MAEJ_RIGHT_KNEE,
				MAEJ_RIGHT_FOOT,
				MAEJ_SIZE,
			};

			static const char* maej_str[MAEJ_SIZE] = {
					"INVALID",
                    "HEAD",
					"NECK",
					"LEFT_SHOULDER",
					"LEFT_ELBOW",
                    "LEFT_HAND",
					"RIGHT_SHOULDER",
					"RIGHT_ELBOW",
					"RIGHT_HAND",
                    "TORSO",
					"LEFT_HIP",
					"LEFT_KNEE",
					"LEFT_FOOT",
                    "RIGHT_HIP",
                    "RIGHT_KNEE",
                    "RIGHT_FOOT",
					};
} // namespace mae


#endif // MAEJ_HPP_
