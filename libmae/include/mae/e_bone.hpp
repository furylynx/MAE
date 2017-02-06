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
#include "mstr.hpp"

//global includes
#include <string>
#include <stdexcept>
#include <vector>

namespace mae
{

	enum class e_bone : int
	{
			INVALID_BONE 		= 	0,
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
			RIGHT_WHOLE_LEG 	= 	2,

			//bones provided by the kinect skeleton
			RIGHT_HAND 	= 	10,
			RIGHT_FOOT 	= 	11,
			LEFT_HAND 	= 	-10,
			LEFT_FOOT 	= 	-11,

	};

	class e_bone_c
	{
		public:
			/**
			 * Returns the string representation for this enum value.
			 *
			 * @param bone The element.
			 * @return The string representation.
			 */
			static std::string str(e_bone bone);

			/**
			 * Returns the integer value corresponding to this element.
			 *
			 * @param bone The element.
			 * @return The integer ID.
			 */
			static int to_int(e_bone bone);

			/**
			 * Returns a vector containing all possible enum values.
			 *
			 * @return A vector.
			 */
			static std::vector<e_bone> vec();

			/**
			 * Parses the string and returns the corresponding element.
			 *
			 * @param str The string to be parsed.
			 * @return The element.
			 */
			static e_bone parse(std::string str);

	};

} // namespace mae

#endif // E_BONE_HPP_
