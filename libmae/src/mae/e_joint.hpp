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
//...

//global includes
#include <string>
#include <stdexcept>
#include <vector>

namespace mae
{

	enum class e_joint
	{
			INVALID = 0,
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
			static std::string str(e_joint joint);
			static int to_int(e_joint joint);
			static std::vector<e_joint> vec();
			static bool is_dummy(e_joint joint);
			static bool is_torso(e_joint joint);
	};

} // namespace mae

#endif // E_JOINT_HPP_
