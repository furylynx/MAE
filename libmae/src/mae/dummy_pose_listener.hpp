#ifndef MAE_DUMMY_POSE_LISTENER_HPP_
#define MAE_DUMMY_POSE_LISTENER_HPP_

//custom includes
#include "i_pose_listener.hpp"

//global includes
//...

namespace mae
{
	namespace demo
	{
		namespace fl
		{
			namespace res
			{

				class dummy_pose_listener: public i_pose_listener
				{
					public:
						dummy_pose_listener();
						virtual ~dummy_pose_listener();

						/** Is invoked each time a pose was quantized (which occurs on every frame).
						 *
						 * @param timestamp The associated timestamp.
						 * @param pose The quantized pose.
						 */
						virtual void on_pose(long timestamp, std::shared_ptr<general_pose> pose);
				};

			} // namespace res
		} // namespace fl
	} // namespace demo
} // namespace mae

#endif // MAE_DUMMY_POSE_LISTENER_HPP_
