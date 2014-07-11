/*
 * e_fl_joint.hpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#ifndef E_FL_JOINT_HPP_
#define E_FL_JOINT_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
//...

//global includes
#include <string>
#include <vector>
#include <stdexcept>

namespace mae
{
	namespace fl
	{

		enum class e_fl_joint
		{
				INVALID = 0,
				HEAD,
				LEFT_UPPER_ARM,
				LEFT_FOREARM,
				LEFT_WHOLE_ARM,
				RIGHT_UPPER_ARM,
				RIGHT_FOREARM,
				RIGHT_WHOLE_ARM,
				LEFT_THIGH, //Oberschenkel
				LEFT_SHANK, //Unterschenkel
				LEFT_WHOLE_LEG,
				RIGHT_THIGH, //Oberschenkel
				RIGHT_SHANK, //Unterschenkel
				RIGHT_WHOLE_LEG
		};

		class e_fl_joint_c
		{
			public:
				static std::string str(e_fl_joint joint);
				static int to_int(e_fl_joint joint);
				static std::vector<e_fl_joint> vec();
		};

	} // namespace fl
} // namespace mae

#endif // E_FL_JOINT_HPP_
