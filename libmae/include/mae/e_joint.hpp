/*
 * e_joint.hpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#ifndef E_JOINT_HPP_
#define E_JOINT_HPP_

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

	enum class e_joint : int
	{
			INVALID_JOINT = 0,
			HEAD,
			NECK,
			LEFT_SHOULDER,
			LEFT_ELBOW,
			LEFT_HAND,
			RIGHT_SHOULDER,
			RIGHT_ELBOW,
			RIGHT_HAND,
			TORSO,
			LEFT_HIP,
			LEFT_KNEE,
			LEFT_FOOT,
			RIGHT_HIP,
			RIGHT_KNEE,
			RIGHT_FOOT,

			TLS, 		//dummy joint for torso, this joint is parent of the left shoulder
			TRS, 		//dummy joint for torso, this joint is parent of the right shoulder
			TLH, 		//dummy joint for torso, this joint is parent of the left hip
			TRH, 		//dummy joint for torso, this joint is parent of the right hip
			TN,  		//dummy joint for torso, this joint is parent of the neck

			END_LH, 	//dummy joint for end site, this joint is child of the left hand
			END_RH, 	//dummy joint for end site, this joint is child of the right hand
			END_LF, 	//dummy joint for end site, this joint is child of the left foot
			END_RF, 	//dummy joint for end site, this joint is child of the right foot
			END_H,  	//dummy joint for end site, this joint is child of the head
	};

	class e_joint_c
	{
		public:
			/**
			 * Returns the string representation for this enum value.
			 *
			 * @param unit The element.
			 * @return The string representation.
			 */
			static std::string str(e_joint joint);

			/**
			 * Returns the integer value corresponding to this element.
			 *
			 * @param joint The element.
			 * @return The integer ID.
			 */
			static int to_int(e_joint joint);

			/**
			 * Returns a vector containing all possible enum values.
			 *
			 * @return A vector.
			 */
			static std::vector<e_joint> vec();

			/**
			 * Returns true if the joint ID represents a dummy joint.
			 *
			 * @param joint The element.
			 * @return True if dummy element.
			 */
			static bool is_dummy(e_joint joint);

			/**
			 * Returns true if the joint ID represents a torso joint.
			 *
			 * @param joint The element.
			 * @return True if torso element.
			 */
			static bool is_torso(e_joint joint);

			/**
			 * Parses the string and returns the corresponding element.
			 *
			 * @param str The string to be parsed.
			 * @return The element.
			 */
			static e_joint parse(std::string str);

	};

} // namespace mae

#endif // E_JOINT_HPP_
