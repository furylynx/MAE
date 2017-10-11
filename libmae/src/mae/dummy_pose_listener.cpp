#include "dummy_pose_listener.hpp"

namespace mae
{
	namespace demo
	{
		namespace fl
		{
			namespace res
			{

				dummy_pose_listener::dummy_pose_listener()
				{
					// TODO Auto-generated constructor stub

				}

				dummy_pose_listener::~dummy_pose_listener()
				{
					// TODO Auto-generated destructor stub
				}

				void dummy_pose_listener::on_pose(long timestamp, std::shared_ptr<general_pose> pose)
				{
					//do nothing
				}

			} // namespace res
		} // namespace fl
	} // namespace demo
} // namespace mae
