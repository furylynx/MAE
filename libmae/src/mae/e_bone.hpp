/*
 * e_bone.hpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#ifndef E_BONE_HPP_
#define E_BONE_HPP_

//eclipse indexer fix
#include "indexer_fix.hpp"

//custom includes
//...

//global includes
#include <string>
#include <stdexcept>

namespace mae
{

	enum class e_bone : int
	{
			INVALID 			= 	0,
			HEAD 				= 	5,
			LEFT_UPPER_ARM 		= -	8,
			LEFT_FOREARM 		= -	9,
			LEFT_WHOLE_ARM 		= -	4,
			RIGHT_UPPER_ARM 	= 	8,
			RIGHT_FOREARM 		= 	9,
			RIGHT_WHOLE_ARM 	= 	4,
			LEFT_THIGH 			= -	6, 		//Oberschenkel
			LEFT_SHANK 			= -	7, 		//Unterschenkel
			LEFT_WHOLE_LEG 		= -	2,
			RIGHT_THIGH 		= 	6, 		//Oberschenkel
			RIGHT_SHANK 		= 	7, 		//Unterschenkel
			RIGHT_WHOLE_LEG 	= 	2
	};

	class e_bone_c
	{
		public:
			static std::string str(e_bone bone);
			static int to_int(e_bone bone);
	};

} // namespace mae

#endif // E_BONE_HPP_
