/*
 * pose_listener.hpp
 *
 *  Created on: 23.06.2014
 *      Author: keks
 */

#ifndef _I_POSE_LISTENER_HPP_
#define _I_POSE_LISTENER_HPP_

//eclipse indexer fix
#include "indexer_fix.hpp"

//custom includes
#include "general_pose.hpp"

//global includes
#include <memory>

namespace mae
{

	class i_pose_listener
	{
		public:
			virtual ~i_pose_listener(){}

			virtual void on_pose(long timestamp, std::shared_ptr<general_pose> pose) = 0;
	};

} // namespace mae

#endif // POSE_LISTENER_HPP_
