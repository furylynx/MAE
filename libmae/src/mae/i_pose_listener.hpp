#ifndef MAE_I_POSE_LISTENER_HPP_
#define MAE_I_POSE_LISTENER_HPP_

//custom includes
#include "general_pose.hpp"

//global includes
#include <memory>
#include <cstdint>

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
			virtual void on_pose(uint64_t timestamp, std::shared_ptr<general_pose> pose) = 0;
	};

} // namespace mae

#endif // MAE_I_POSE_LISTENER_HPP_
