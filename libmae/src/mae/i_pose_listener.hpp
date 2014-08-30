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

	/**
	 * Listener for poses. In notified each frame after the pose quantization.
	 */
	class i_pose_listener
	{
		public:
			virtual ~i_pose_listener(){}

			/**
			 * Is invoked each time a pose was quantized (which occurs on every frame).
			 *
			 * @param timestamp The associated timestamp.
			 * @param pose The quantized pose.
			 */
			virtual void on_pose(long timestamp, std::shared_ptr<general_pose> pose) = 0;
	};

} // namespace mae

#endif // POSE_LISTENER_HPP_
