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
			map_directions_.insert(std::make_pair(FLD_P_H, cv::Vec3d(-1, 0, 0)));
			map_directions_.insert(std::make_pair(FLD_P_M, cv::Vec3d(0, 0, 0))); //TODO not as vector possible
			map_directions_.insert(std::make_pair(FLD_P_L, cv::Vec3d(1, 0, 0)));

			map_directions_.insert(std::make_pair(FLD_L_H, cv::Vec3d(-1, 1, 0)));
			map_directions_.insert(std::make_pair(FLD_L_M, cv::Vec3d(0, 1, 0)));
			map_directions_.insert(std::make_pair(FLD_L_L, cv::Vec3d(1, 1, 0)));

			map_directions_.insert(std::make_pair(FLD_D_F_L_H, cv::Vec3d(-1, 1, 1)));
			map_directions_.insert(std::make_pair(FLD_D_F_L_M, cv::Vec3d(0, 1, 1)));
			map_directions_.insert(std::make_pair(FLD_D_F_L_L, cv::Vec3d(1, 1, 1)));

			map_directions_.insert(std::make_pair(FLD_F_L_H, cv::Vec3d(-1, 0, 1)));
			map_directions_.insert(std::make_pair(FLD_F_L_M, cv::Vec3d(0, 0, 1)));
			map_directions_.insert(std::make_pair(FLD_F_L_L, cv::Vec3d(1, 0, 1)));

			map_directions_.insert(std::make_pair(FLD_F_R_H, cv::Vec3d(-1, 0, 1)));
			map_directions_.insert(std::make_pair(FLD_F_R_M, cv::Vec3d(0, 0, 1)));
			map_directions_.insert(std::make_pair(FLD_F_R_L, cv::Vec3d(1, 0, 1)));

			map_directions_.insert(std::make_pair(FLD_D_F_R_H, cv::Vec3d(-1, -1, 1)));
			map_directions_.insert(std::make_pair(FLD_D_F_R_M, cv::Vec3d(0, -1, 1)));
			map_directions_.insert(std::make_pair(FLD_D_F_R_L, cv::Vec3d(1, -1, 1)));

			map_directions_.insert(std::make_pair(FLD_R_H, cv::Vec3d(-1, -1, 0)));
			map_directions_.insert(std::make_pair(FLD_R_M, cv::Vec3d(0, -1, 0)));
			map_directions_.insert(std::make_pair(FLD_R_L, cv::Vec3d(1, -1, 0)));

			map_directions_.insert(std::make_pair(FLD_D_B_R_H, cv::Vec3d(-1, -1, -1)));
			map_directions_.insert(std::make_pair(FLD_D_B_R_M, cv::Vec3d(0, -1, -1)));
			map_directions_.insert(std::make_pair(FLD_D_B_R_L, cv::Vec3d(1, -1, -1)));

			map_directions_.insert(std::make_pair(FLD_B_R_H, cv::Vec3d(-1, 0, -1)));
			map_directions_.insert(std::make_pair(FLD_B_R_M, cv::Vec3d(0, 0, -1)));
			map_directions_.insert(std::make_pair(FLD_B_R_L, cv::Vec3d(1, 0, -1)));

			map_directions_.insert(std::make_pair(FLD_B_L_H, cv::Vec3d(-1, 0, -1)));
			map_directions_.insert(std::make_pair(FLD_B_L_M, cv::Vec3d(0, 0, -1)));
			map_directions_.insert(std::make_pair(FLD_B_L_L, cv::Vec3d(1, 0, -1)));

			map_directions_.insert(std::make_pair(FLD_D_B_L_H, cv::Vec3d(-1, 1, -1)));
			map_directions_.insert(std::make_pair(FLD_D_B_L_M, cv::Vec3d(0, 1, -1)));
			map_directions_.insert(std::make_pair(FLD_D_B_L_L, cv::Vec3d(1, 1, -1)));

		}

		fl_pose_detector::~fl_pose_detector()
		{
		}

		std::shared_ptr<general_pose> fl_pose_detector::pose(std::shared_ptr<fl_skeleton> skeleton,
				std::vector<bone> body_parts)
		{
			const bool angles = false;

			std::shared_ptr<general_pose> result = std::shared_ptr<general_pose>(new general_pose());

			if (angles)
			{
				result = angle_pose(skeleton, body_parts);
			}
			else
			{
				result = vector_pose(skeleton, body_parts);
			}

			return result;
		}

		std::shared_ptr<mae::general_pose> fl_pose_detector::vector_pose(std::shared_ptr<fl_skeleton> skeleton,
				std::vector<bone> body_parts)
		{
			std::shared_ptr<general_pose> result = std::shared_ptr<general_pose>(new general_pose());

			//calculated distances for all bones
			for (unsigned int bone_index = 0; bone_index < body_parts.size(); bone_index++)
			{
				for (int dir = FLD_INVALID + 1; dir != FLD_SIZE; dir++)
				{
					if (dir == FLD_P_M)
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

							result->set_distance(body_parts.at(bone_index).get_id(), dir, angle);
						}
						else
						{
							//no joint bone therefore place middle does not exist for this body part
							//set distance to the maximum
							result->set_distance(body_parts.at(bone_index).get_id(), dir, 180);
						}
					}
					else
					{
						//set value for the direction
						cv::Vec3d set_dir = map_directions_.at(dir);

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

						result->set_distance(body_parts.at(bone_index).get_id(), dir, angle);
					}
				}

				//handle place middle different than the other directions
				if (result->get_distance(body_parts.at(bone_index).get_id(), FLD_P_M) < PM_ACCEPT_DIST)
				{
					//favor place mid since the distance is less than the defined PM_ACCEPT_DIST distance
					result->set_direction(body_parts.at(bone_index).get_id(), FLD_P_M);
				}
				else
				{
					//find minimum distance to set direction
					int min_dist_dir = FLD_INVALID;
					for (int dir = FLD_INVALID + 1; dir != FLD_SIZE; dir++)
					{
						if ((min_dist_dir == FLD_INVALID
								&& result->get_distance(body_parts.at(bone_index).get_id(), dir) >= 0)
								|| (result->get_distance(body_parts.at(bone_index).get_id(), dir)
										< result->get_distance(body_parts.at(bone_index).get_id(), min_dist_dir)
										&& result->get_distance(body_parts.at(bone_index).get_id(), dir) >= 0))
						{
							min_dist_dir = dir;
						}
					}
					result->set_direction(body_parts.at(bone_index).get_id(), min_dist_dir);
				}
			}

			return result;
		}

		std::shared_ptr<general_pose> fl_pose_detector::angle_pose(std::shared_ptr<fl_skeleton> skeleton,
				std::vector<bone> body_parts)
		{
			std::vector<std::vector<int> > dir_circ;
			std::vector<int> flj_ext_bones;
			std::vector<int> flj_ext_whole;

			std::vector<int> dir_circ_l;
			dir_circ_l.push_back(FLD_D_F_L_M);
			dir_circ_l.push_back(FLD_D_F_L_L);
			dir_circ_l.push_back(FLD_L_L);
			dir_circ_l.push_back(FLD_D_B_L_L);
			dir_circ_l.push_back(FLD_D_B_L_M);
			dir_circ_l.push_back(FLD_D_B_L_H);
			dir_circ_l.push_back(FLD_L_H);
			dir_circ_l.push_back(FLD_D_F_L_H);
			dir_circ.push_back(dir_circ_l);

			std::vector<int> dir_circ_m;
			dir_circ_m.push_back(FLD_F_L_M);
			dir_circ_m.push_back(FLD_F_L_L);
			dir_circ_m.push_back(FLD_P_L);
			dir_circ_m.push_back(FLD_B_L_L);
			dir_circ_m.push_back(FLD_B_L_M);
			dir_circ_m.push_back(FLD_B_L_H);
			dir_circ_m.push_back(FLD_P_H);
			dir_circ_m.push_back(FLD_F_L_H);
			dir_circ.push_back(dir_circ_m);

			std::vector<int> dir_circ_r;
			dir_circ_r.push_back(FLD_D_F_R_M);
			dir_circ_r.push_back(FLD_D_F_R_L);
			dir_circ_r.push_back(FLD_R_L);
			dir_circ_r.push_back(FLD_D_B_R_L);
			dir_circ_r.push_back(FLD_D_B_R_M);
			dir_circ_r.push_back(FLD_D_B_R_H);
			dir_circ_r.push_back(FLD_R_H);
			dir_circ_r.push_back(FLD_D_F_R_H);
			dir_circ.push_back(dir_circ_r);

			//extremities
			flj_ext_bones.push_back(FLJ_LEFT_WHOLE_ARM);
			flj_ext_bones.push_back(FLJ_LEFT_UPPER_ARM);
			flj_ext_bones.push_back(FLJ_LEFT_FOREARM);
			flj_ext_bones.push_back(FLJ_RIGHT_WHOLE_ARM);
			flj_ext_bones.push_back(FLJ_RIGHT_UPPER_ARM);
			flj_ext_bones.push_back(FLJ_RIGHT_FOREARM);
			flj_ext_bones.push_back(FLJ_LEFT_WHOLE_LEG);
			flj_ext_bones.push_back(FLJ_LEFT_THIGH);
			flj_ext_bones.push_back(FLJ_LEFT_SHANK);
			flj_ext_bones.push_back(FLJ_RIGHT_WHOLE_LEG);
			flj_ext_bones.push_back(FLJ_RIGHT_THIGH);
			flj_ext_bones.push_back(FLJ_RIGHT_SHANK);

			std::shared_ptr<general_pose> result = std::shared_ptr<general_pose>(new general_pose());

			//use distance measure
			//select the dir+lvl with least distance

			//iterate bones

			for (unsigned int k = 0; k < flj_ext_bones.size(); k++)
			{

				int joint_id = flj_ext_bones[k];

				//iterate dir+lvl's
				for (int dir = FLD_INVALID + 1; dir != FLD_SIZE; dir++)
				{

					if (dir == FLD_P_M)
					{
						if (k % 3 == 0)
						{
							//estimate place middle for whole arm (only dependent on extremity bone (forearm, shank))
							result->set_distance(joint_id, dir,
									180 - skeleton->get_joint((int) flj_ext_bones[k + 2])->get_phi());
						}
						else
						{
							//place does not exist for bones
							continue;
						}
					}
					else if (dir == FLD_L_M)
					{
						result->set_distance(joint_id, dir, skeleton->get_joint(joint_id)->get_phi());
					}
					else if (dir == FLD_R_M)
					{
						result->set_distance(joint_id, dir, 180 - skeleton->get_joint(joint_id)->get_phi());
					}
					else
					{
						//other 24=3x8 directions (8 per layer from left to right)
						for (int i = 0; i < 3; i++)
						{
							for (int j = 0; j < 8; j++)
							{
								double dist = std::sqrt(
										std::pow(((i + 1) * 45) - skeleton->get_joint(joint_id)->get_phi(), 2)
												+ std::pow((j * 45) - skeleton->get_joint(joint_id)->get_theta(), 2));
								result->set_distance(joint_id, dir, dist);
							}
						}

					}
				}

				//find minimum distance to set direction
				int min_dist_dir = FLD_INVALID;
				for (int dir = FLD_INVALID + 1; dir != FLD_SIZE; dir++)
				{
					if ((min_dist_dir == FLD_INVALID && result->get_distance(joint_id, dir) >= 0)
							|| (result->get_distance(joint_id, dir) < result->get_distance(joint_id, min_dist_dir)
									&& result->get_distance(joint_id, dir) >= 0))
					{
						min_dist_dir = dir;
					}
				}
				result->set_direction(joint_id, min_dist_dir);
			}

			if (result->get_direction(FLJ_LEFT_WHOLE_ARM) >= FLD_INVALID
					&& result->get_direction(FLJ_LEFT_WHOLE_ARM) < FLD_SIZE)
			{
				const char * dir_str = fld_str[result->get_direction(FLJ_LEFT_WHOLE_ARM)];

				std::cout << " DIR: " << dir_str << " "
						<< result->get_distance(FLJ_LEFT_WHOLE_ARM, result->get_direction(FLJ_LEFT_WHOLE_ARM))
						<< " # LWA: " << skeleton->get_joint(FLJ_LEFT_WHOLE_ARM) << " # LUA: "
						<< skeleton->get_joint(FLJ_LEFT_UPPER_ARM) << " # LFA: "
						<< skeleton->get_joint(FLJ_LEFT_FOREARM) << std::endl;
			}
			else
			{
				std::cout << " DIR: " << result->get_direction(FLJ_LEFT_WHOLE_ARM) << " # LUA: "
						<< skeleton->get_joint(FLJ_LEFT_UPPER_ARM) << " # LFA: "
						<< skeleton->get_joint(FLJ_LEFT_FOREARM) << std::endl;
			}

			return result;
		}

	} // namespace fl
} // namespace mae
