/*
 * e_fl_direction.hpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#ifndef E_FL_DIRECTION_HPP_
#define E_FL_DIRECTION_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "../mstr.hpp"

//global includes
#include <string>
#include <vector>
#include <stdexcept>

namespace mae
{
	namespace fl
	{

		enum class e_fl_direction
		{
				INVALID = 0,
				P_H,
				P_M,
				P_L,

				L_H,
				L_M,
				L_L,

				D_F_L_H,
				D_F_L_M,
				D_F_L_L,

				F_L_H,
				F_L_M,
				F_L_L,

				F_R_H,
				F_R_M,
				F_R_L,

				D_F_R_H,
				D_F_R_M,
				D_F_R_L,

				R_H,
				R_M,
				R_L,

				D_B_R_H,
				D_B_R_M,
				D_B_R_L,

				B_R_H,
				B_R_M,
				B_R_L,

				B_L_H,
				B_L_M,
				B_L_L,

				D_B_L_H,
				D_B_L_M,
				D_B_L_L
		};

		class e_fl_direction_c
		{
			public:
				/**
				 * Returns the string representation for this enum value.
				 *
				 * @param direction The element.
				 * @return The string representation.
				 */
				static std::string str(e_fl_direction direction);

				/**
				 * Returns the integer value corresponding to this element.
				 *
				 * @param direction The element.
				 * @return The integer ID.
				 */
				static int to_int(e_fl_direction direction);

				/**
				 * Returns a vector containing all possible enum values.
				 *
				 * @return A vector.
				 */
				static std::vector<e_fl_direction> vec();

				/**
				 * Parses the string and returns the corresponding element.
				 *
				 * @param str The string to be parsed.
				 * @return The element.
				 */
				static e_fl_direction parse(std::string str);

		};


	} // namespace fl
} // namespace mae

#endif // E_FL_DIRECTION_HPP_
