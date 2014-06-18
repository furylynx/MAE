/*
 * FLPoseDetector.cpp
 *
 *  Created on: 29.05.2014
 *      Author: keks
 */

#include "FLPoseDetector.hpp"

namespace mae
{
	namespace fl
	{

		FLPoseDetector::FLPoseDetector()
		{
			//initialize directions on circle

			//TODO change according to actual angle sequence
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
		}

		FLPoseDetector::~FLPoseDetector()
		{
		}

		std::shared_ptr<general_pose> FLPoseDetector::pose(std::shared_ptr<FLSkeleton> skeleton,
				std::vector<int> body_parts)
		{
			const bool angles = false;

			std::shared_ptr<general_pose> result = std::shared_ptr<general_pose>(
					new general_pose());

			if (angles)
			{
				result = angle_pose(skeleton, body_parts);
			}

			//TODO do stuff in here (angles between vectors)

			return result;
		}

		std::shared_ptr<general_pose> FLPoseDetector::angle_pose(std::shared_ptr<FLSkeleton> skeleton,
				std::vector<int> body_parts)
		{

			//todo remove (is here just to show this method is invoked)
//			std::cout << "detecting pose for skeleton" << std::endl;

			std::shared_ptr<general_pose> result = std::shared_ptr<general_pose>(new general_pose());

			//todo distances

			//use distance measure
			//select the dir+lvl with least distance

			//iterate bones

			for (unsigned int k = 0; k < (signed int) flj_ext_bones.size(); k++)
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
									180 - skeleton->get_joint((int) flj_ext_bones[k + 2])->getPhi());
						}
						else
						{
							//place does not exist for bones
							continue;
						}
					}
					else if (dir == FLD_L_M)
					{
						result->set_distance(joint_id, dir, skeleton->get_joint(joint_id)->getPhi());
					}
					else if (dir == FLD_R_M)
					{
						result->set_distance(joint_id, dir, 180 - skeleton->get_joint(joint_id)->getPhi());
					}
					else
					{
						//other 24=3x8 directions (8 per layer from left to right)
						for (int i = 0; i < 3; i++)
						{
							for (int j = 0; j < 8; j++)
							{
								double dist = std::sqrt(
										std::pow(((i + 1) * 45) - skeleton->get_joint(joint_id)->getPhi(), 2)
												+ std::pow((j * 45) - skeleton->get_joint(joint_id)->getTheta(), 2));
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

//			//left whole arm first
//
//			//check for "place"
//			if (skeleton->getJoint(FLJ_LEFT_FOREARM)->getPhi() > 157.5)
//			{
//				result->setDirection(FLJ_LEFT_WHOLE_ARM, FLD_P_M);
//
//				//TODO forearm and upper arm directions ?
//			}
//			else
//			{
//				//not "place"
//
//				//check whether the arm is bent
//				if (skeleton->getJoint(FLJ_LEFT_FOREARM)->getPhi() < 22.5)
//				{
//					//get direction and level for non-bent arm
//					if (skeleton->getJoint(FLJ_LEFT_UPPER_ARM)->getPhi() < 22.5)
//					{
//						//left mid
//						result->setDirection(FLJ_LEFT_WHOLE_ARM, FLD_L_M);
//					}
//					else if (skeleton->getJoint(FLJ_LEFT_UPPER_ARM)->getPhi() > 157.5)
//					{
//						//right mid
//						result->setDirection(FLJ_LEFT_WHOLE_ARM, FLD_R_M);
//					}
//					else
//					{
//						//other 24=3x8 directions (8 per layer from left to right)
//						for (int i = 0; i < 3; i++)
//						{
//							for (int j = 0; j < 8; j++)
//							{
//								//get direction left/left diagonal, mid, right/right diagonal
//								if (skeleton->getJoint(FLJ_LEFT_UPPER_ARM)->getPhi() > ((i + 1) * 45 - 22.5)
//										&& skeleton->getJoint(FLJ_LEFT_UPPER_ARM)->getPhi() <= ((i + 1) * 45 + 22.5))
//								{
//									//check for first case (front)
//									if (j == 0)
//									{
//										//front has other condition (_OR_)
//										if (skeleton->getJoint(FLJ_LEFT_UPPER_ARM)->getTheta()
//												> (FLMath::fmod_pos(j * 45 - 22.5, 360) - 180)
//												|| skeleton->getJoint(FLJ_LEFT_UPPER_ARM)->getTheta()
//														<= (FLMath::fmod_pos(j * 45 + 22.5, 360) - 180))
//										{
//											result->setDirection(FLJ_LEFT_WHOLE_ARM, (int) dir_circ[i][j]);
//											break;
//										}
//									}
//									else
//									{
//										//all other cases
//										if (skeleton->getJoint(FLJ_LEFT_UPPER_ARM)->getTheta()
//												> (FLMath::fmod_pos(j * 45 - 22.5, 360) - 180)
//												&& skeleton->getJoint(FLJ_LEFT_UPPER_ARM)->getTheta()
//														<= (FLMath::fmod_pos(j * 45 + 22.5, 360) - 180))
//										{
//											result->setDirection(FLJ_LEFT_WHOLE_ARM, (int) dir_circ[i][j]);
//											break;
//										}
//									}
//								}
//							}
//						}
//					}
//				}
//				else
//				{
//					//arm is bent therefore forearm and upper arm must be regarded separately
//					//TODO
//
//					std::cout << " :: ARM IS BENT" << std::endl;
//				}
//			}

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

			//todo do stuff in here

			return result;
		}

	} // namespace fl
} // namespace mae
