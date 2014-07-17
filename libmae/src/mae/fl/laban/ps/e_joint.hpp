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
//...

//global includes
#include <string>
#include <stdexcept>

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{

				enum class e_joint
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
						static std::string str(e_joint joint_);
				};


			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_JOINT_H_
