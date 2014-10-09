/*
 * e_joint.h
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef E_JOINT_H_
#define E_JOINT_H_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "../../../mstr.hpp"

//global includes
#include <string>
#include <stdexcept>
#include <vector>

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{

				enum class e_joint : int
				{
						NONE,
						SHOULDER,
						ELBOW,
						WRIST,
						HAND,
						FINGERS,
						HIP,
						KNEE,
						ANKLE,
						FOOT,
						TOES
				};

				class e_joint_c
				{
					public:
						/**
						 * Returns the string representation for this enum value.
						 *
						 * @param joint The element.
						 * @return The string representation.
						 */
						static std::string str(e_joint joint);

						/**
						 * Returns a vector containing all possible enum values.
						 *
						 * @return A vector.
						 */
						static std::vector<e_joint> vec();

						/**
						 * Parses the string and returns the corresponding element.
						 *
						 * @param str The string to be parsed.
						 * @return The element.
						 */
						static e_joint parse(std::string str);
				};


			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_JOINT_H_
