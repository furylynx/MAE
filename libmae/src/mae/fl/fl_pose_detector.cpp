/*
 * FLPoseDetector.cpp
 *
 *  Created on: 29.05.2014
 *      Author: keks
 */

#include "fl_pose_detector.hpp"

namespace mae
{
	namespace fl
	{

		fl_pose_detector::fl_pose_detector()
		{
			//initialize directions on circle
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::P_H), cv::Vec3d(-1, 0, 0)));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::P_M), cv::Vec3d(0, 0, 0)));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::P_L), cv::Vec3d(1, 0, 0)));

			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::L_H), cv::Vec3d(-1, 1, 0)));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::L_M), cv::Vec3d(0, 1, 0)));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::L_L), cv::Vec3d(1, 1, 0)));

			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::D_F_L_H), cv::Vec3d(-1, 1, 1)));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::D_F_L_M), cv::Vec3d(0, 1, 1)));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::D_F_L_L), cv::Vec3d(1, 1, 1)));

			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::F_L_H), cv::Vec3d(-1, 0, 1)));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::F_L_M), cv::Vec3d(0, 0, 1)));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::F_L_L), cv::Vec3d(1, 0, 1)));

			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::F_R_H), cv::Vec3d(-1, 0, 1)));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::F_R_M), cv::Vec3d(0, 0, 1)));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::F_R_L), cv::Vec3d(1, 0, 1)));

			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::D_F_R_H), cv::Vec3d(-1, -1, 1)));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::D_F_R_M), cv::Vec3d(0, -1, 1)));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::D_F_R_L), cv::Vec3d(1, -1, 1)));

			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::R_H), cv::Vec3d(-1, -1, 0)));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::R_M), cv::Vec3d(0, -1, 0)));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::R_L), cv::Vec3d(1, -1, 0)));

			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::D_B_R_H), cv::Vec3d(-1, -1, -1)));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::D_B_R_M), cv::Vec3d(0, -1, -1)));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::D_B_R_L), cv::Vec3d(1, -1, -1)));

			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::B_R_H), cv::Vec3d(-1, 0, -1)));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::B_R_M), cv::Vec3d(0, 0, -1)));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::B_R_L), cv::Vec3d(1, 0, -1)));

			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::B_L_H), cv::Vec3d(-1, 0, -1)));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::B_L_M), cv::Vec3d(0, 0, -1)));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::B_L_L), cv::Vec3d(1, 0, -1)));

			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::D_B_L_H), cv::Vec3d(-1, 1, -1)));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::D_B_L_M), cv::Vec3d(0, 1, -1)));
			map_directions_.insert(std::make_pair(e_fl_direction_c::to_int(e_fl_direction::D_B_L_L), cv::Vec3d(1, 1, -1)));

		}

		fl_pose_detector::~fl_pose_detector()
		{
		}

		std::shared_ptr<general_pose> fl_pose_detector::pose(std::shared_ptr<fl_skeleton> skeleton,
				std::vector<bone> body_parts)
		{
			return vector_pose(skeleton, body_parts);
		}

		std::shared_ptr<mae::general_pose> fl_pose_detector::vector_pose(std::shared_ptr<fl_skeleton> skeleton,
				std::vector<bone> body_parts)
		{
			std::shared_ptr<general_pose> result = std::shared_ptr<general_pose>(new general_pose());

			//calculated distances for all bones
			for (unsigned int bone_index = 0; bone_index < body_parts.size(); bone_index++)
			{
				for (e_fl_direction dir : e_fl_direction_c::vec())
				{
					if (dir == e_fl_direction::P_M)
					{
						if (body_parts.at(bone_index).has_middle_joint())
						{
							//calculate angle between two extremity bones
							//set value should is 180 degrees
							cv::Vec3d v = math::jointToVec(
									skeleton->get_orig_skeleton()->get_joint(
											body_parts.at(bone_index).get_middle_joint()))
									- math::jointToVec(
											skeleton->get_orig_skeleton()->get_joint(
													body_parts.at(bone_index).get_from()));

							cv::Vec3d w = math::jointToVec(
									skeleton->get_orig_skeleton()->get_joint(body_parts.at(bone_index).get_to()))
									- math::jointToVec(
											skeleton->get_orig_skeleton()->get_joint(
													body_parts.at(bone_index).get_middle_joint()));

							double angle = 180 - math::calcAngleHalf(v,w);

							result->set_distance(body_parts.at(bone_index).get_id(), e_fl_direction_c::to_int(dir), angle);
						}
						else
						{
							//no joint bone therefore place middle does not exist for this body part
							//set distance to the maximum
							result->set_distance(body_parts.at(bone_index).get_id(), e_fl_direction_c::to_int(dir), 180);
						}
					}
					else
					{
						//set value for the direction
						cv::Vec3d set_dir = map_directions_.at(e_fl_direction_c::to_int(dir));

						//real value for the direction
						cv::Vec3d real_dir;
						if (skeleton->get_hierarchy()->at(body_parts.at(bone_index).get_to())->get_parent()->get_id()
								== body_parts.at(bone_index).get_from())
						{
							real_dir = math::jointToVec(
									skeleton->get_offset_skeleton()->get_joint(body_parts.at(bone_index).get_to()));
						}
						else
						{
							//get bone vector in {u,r,t}
							std::vector<std::vector<double> > coord = skeleton->get_coord_sys();
							cv::Vec3d u = math::stdVecToVec3d(coord[0]);
							cv::Vec3d r = math::stdVecToVec3d(coord[1]);
							cv::Vec3d t = math::stdVecToVec3d(coord[2]);

							real_dir = math::projectToBasis(
									math::jointToVec(
											skeleton->get_orig_skeleton()->get_joint(
													body_parts.at(bone_index).get_to())),
									math::jointToVec(
											skeleton->get_orig_skeleton()->get_joint(
													body_parts.at(bone_index).get_from())), u, r, t);
						}

						//angle between the vectors is the distance
						double angle = math::calcAngleHalf(set_dir, real_dir);

						result->set_distance(body_parts.at(bone_index).get_id(), e_fl_direction_c::to_int(dir), angle);
					}
				}

				//handle place middle different than the other directions
				if (result->get_distance(body_parts.at(bone_index).get_id(), e_fl_direction_c::to_int(e_fl_direction::P_M)) < PM_ACCEPT_DIST)
				{
					//favor place mid since the distance is less than the defined PM_ACCEPT_DIST distance
					result->set_direction(body_parts.at(bone_index).get_id(), e_fl_direction_c::to_int(e_fl_direction::P_M));
				}
				else
				{
					//find minimum distance to set direction
					e_fl_direction min_dist_dir = e_fl_direction::INVALID;
					for (e_fl_direction dir : e_fl_direction_c::vec())
					{
						if ((min_dist_dir == e_fl_direction::INVALID
								&& result->get_distance(body_parts.at(bone_index).get_id(), e_fl_direction_c::to_int(dir)) >= 0)
								|| (result->get_distance(body_parts.at(bone_index).get_id(), e_fl_direction_c::to_int(dir))
										< result->get_distance(body_parts.at(bone_index).get_id(), e_fl_direction_c::to_int(min_dist_dir))
										&& result->get_distance(body_parts.at(bone_index).get_id(), e_fl_direction_c::to_int(dir)) >= 0))
						{
							min_dist_dir = dir;
						}
					}
					result->set_direction(body_parts.at(bone_index).get_id(), e_fl_direction_c::to_int(min_dist_dir));
				}
			}

			return result;
		}

	} // namespace fl
} // namespace mae
