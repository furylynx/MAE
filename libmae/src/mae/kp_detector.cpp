/*
 * GeneralKeyPoseDetector.cpp
 *
 *  Created on: 29.05.2014
 *      Author: keks
 */

#include "kp_detector.hpp"


namespace mae
{

	kp_detector::kp_detector(bool debug)
	{
		this->debug_ = debug;
	}

	kp_detector::~kp_detector()
	{

	}

	std::shared_ptr<general_enriched_pose> kp_detector::estimate_frame(double framerate, std::shared_ptr<general_pose> current_pose,
			std::list<std::shared_ptr<general_enriched_pose> > previous_sequence, std::vector<bone> body_parts)
	{

		if (debug_)
		{
			std::cout << "kp_detector: estimate fame" << std::endl;
		}

		std::shared_ptr<general_enriched_pose> result = std::shared_ptr<general_enriched_pose>(
				new general_enriched_pose(current_pose));

		//initialize with false
		for (unsigned int i = 0; i < body_parts.size(); i++)
		{
			if (previous_sequence.empty())
			{
				result->set_key_pose(body_parts.at(i).get_id(), true);
			}
			else
			{
				result->set_key_pose(body_parts.at(i).get_id(), false);
			}
			result->set_in_motion(body_parts.at(i).get_id(), false);
		}

		if (!previous_sequence.empty())
		{
			for (unsigned int i = 0; i < body_parts.size(); i++)
			{
				int body_part_id = body_parts.at(i).get_id();

				//find the last key pose
				std::shared_ptr<general_enriched_pose> prev_kp = *previous_sequence.begin();
				unsigned int dist = 1;

				for (std::list<std::shared_ptr<general_enriched_pose> >::iterator it = previous_sequence.begin();
						it != previous_sequence.end(); it++)
				{
					if ((*it)->is_key_pose(body_part_id))
					{
						prev_kp = (*it);
						break;
					}
					dist++;
				}

				//check for same or different direction
				if (prev_kp->get_direction(body_part_id) == result->get_direction(body_part_id))
				{
					//same direction, therefore check whether current pose is closer to the direction

					if (dist < RANGE_KP
							&& prev_kp->get_distance(body_part_id, prev_kp->get_direction(body_part_id))
									> result->get_distance(body_part_id, result->get_direction(body_part_id)))
					{
						//update key pose if new pose is closer to the direction than the previous key pose
						//and the distance between the two is not greater than the RANGE_KP const
						prev_kp->set_key_pose(body_part_id, false);
						result->set_key_pose(body_part_id, true);
					}
				}
				else
				{
					//different direction, therefore a new key pose was detected

					result->set_key_pose(body_part_id, true);

					//search for beginning of the motion
					unsigned int dist_max = 1;
					double curr_max = -1;
					std::shared_ptr<general_enriched_pose> curr_max_pose = result;

					for (std::list<std::shared_ptr<general_enriched_pose> >::iterator it = previous_sequence.begin();
							it != previous_sequence.end(); it++)
					{
						if (curr_max == -1
								|| curr_max < (*it)->get_distance(body_part_id, result->get_direction(body_part_id)))
						{
							//update maximum distance pose
							dist_max = 1;
							curr_max_pose = (*it);
							curr_max = curr_max_pose->get_distance(body_part_id, result->get_direction(body_part_id));
						}
						else
						{
							//count distance to last max distance
							dist_max++;
						}

						if ((*it)->is_key_pose(body_part_id) || dist_max > RANGE_KP)
						{
							//found last key pose or distance to last max exceeded the range
							//therefore current maximum is accepted
							break;
						}
					}

					curr_max_pose->set_in_motion(body_part_id, true);
				}
			}
		}

		return result;
	}

	void kp_detector::clear_buffer()
	{

	}

} // namespace mae
