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
		}

		FLPoseDetector::~FLPoseDetector()
		{
		}

		std::shared_ptr<mae::model::GeneralPose> FLPoseDetector::detectPose(std::shared_ptr<FLSkeleton> skeleton,
				std::vector<int> bodyParts)
		{

			//todo remove (is here just to show this method is invoked)
//			std::cout << "detecting pose for skeleton" << std::endl;

			std::shared_ptr<mae::model::GeneralPose> result = std::shared_ptr<mae::model::GeneralPose>(
					new mae::model::GeneralPose());

			//todo distances

			//left whole arm first

			//check for "place"
			if (skeleton->getJoint(FLSkeleton::ANGLE_LEFT_FOREARM)->getPhi() > 157.5)
			{
				result->setDirection(FLSkeleton::ANGLE_LEFT_WHOLE_ARM, FLLabanSequence::PLACE_MID);

				//TODO forearm and upper arm directions
			}
			else
			{
				//not "place"

				//check whether the arm is bent
				if (skeleton->getJoint(FLSkeleton::ANGLE_LEFT_FOREARM)->getPhi() < 22.5)
				{

					//TODO
					if (skeleton->getJoint(FLSkeleton::ANGLE_LEFT_UPPER_ARM)->getPhi() < 22.5)
					{
						result->setDirection(FLSkeleton::ANGLE_LEFT_WHOLE_ARM, FLLabanSequence::LEFT_MID);
					}
					else if (skeleton->getJoint(FLSkeleton::ANGLE_LEFT_UPPER_ARM)->getPhi() > 157.5)
					{
						result->setDirection(FLSkeleton::ANGLE_LEFT_WHOLE_ARM, FLLabanSequence::RIGHT_MID);
					}
					else
					{

						std::vector<std::vector<int> > dir_circ;
						std::vector<int> dir_circ_l;
						dir_circ_l.push_back(FLLabanSequence::DIAGONAL_FORWARD_LEFT_MID);
						dir_circ_l.push_back(FLLabanSequence::DIAGONAL_FORWARD_LEFT_HIGH);
						dir_circ_l.push_back(FLLabanSequence::LEFT_HIGH);
						dir_circ_l.push_back(FLLabanSequence::DIAGONAL_BACK_LEFT_HIGH);
						dir_circ_l.push_back(FLLabanSequence::DIAGONAL_BACK_LEFT_MID);
						dir_circ_l.push_back(FLLabanSequence::DIAGONAL_BACK_LEFT_LOW);
						dir_circ_l.push_back(FLLabanSequence::LEFT_LOW);
						dir_circ_l.push_back(FLLabanSequence::DIAGONAL_FORWARD_LEFT_LOW);
						dir_circ.push_back(dir_circ_l);

						std::vector<int> dir_circ_m;
						dir_circ_m.push_back(FLLabanSequence::FORWARD_LEFT_MID);
						dir_circ_m.push_back(FLLabanSequence::FORWARD_LEFT_HIGH);
						dir_circ_m.push_back(FLLabanSequence::PLACE_HIGH);
						dir_circ_m.push_back(FLLabanSequence::BACK_LEFT_HIGH);
						dir_circ_m.push_back(FLLabanSequence::BACK_LEFT_MID);
						dir_circ_m.push_back(FLLabanSequence::BACK_LEFT_LOW);
						dir_circ_m.push_back(FLLabanSequence::PLACE_LOW);
						dir_circ_m.push_back(FLLabanSequence::FORWARD_LEFT_LOW);
						dir_circ.push_back(dir_circ_m);

						std::vector<int> dir_circ_r;
						dir_circ_r.push_back(FLLabanSequence::DIAGONAL_FORWARD_RIGHT_MID);
						dir_circ_r.push_back(FLLabanSequence::DIAGONAL_FORWARD_RIGHT_HIGH);
						dir_circ_r.push_back(FLLabanSequence::RIGHT_HIGH);
						dir_circ_r.push_back(FLLabanSequence::DIAGONAL_BACK_RIGHT_HIGH);
						dir_circ_r.push_back(FLLabanSequence::DIAGONAL_BACK_RIGHT_MID);
						dir_circ_r.push_back(FLLabanSequence::DIAGONAL_BACK_RIGHT_LOW);
						dir_circ_r.push_back(FLLabanSequence::RIGHT_LOW);
						dir_circ_r.push_back(FLLabanSequence::DIAGONAL_FORWARD_RIGHT_LOW);
						dir_circ.push_back(dir_circ_r);

						for (int i = 0; i < 3; i++)
						{
							for (int j = 0; j < 8; j++)
							{
								if (skeleton->getJoint(FLSkeleton::ANGLE_LEFT_UPPER_ARM)->getPhi()
										> ((i + 1) * 45 - 22.5)
										&& skeleton->getJoint(FLSkeleton::ANGLE_LEFT_UPPER_ARM)->getPhi()
												<= ((i + 1) * 45 + 22.5))
								{
									if (skeleton->getJoint(FLSkeleton::ANGLE_LEFT_UPPER_ARM)->getTheta()
											> (FLMath::fmod_pos(j * 45 - 22.5, 360) - 180)
											&& skeleton->getJoint(FLSkeleton::ANGLE_LEFT_UPPER_ARM)->getTheta()
													<= (FLMath::fmod_pos(j * 45 + 22.5, 360) - 180))
									{
										result->setDirection(FLSkeleton::ANGLE_LEFT_WHOLE_ARM, (int) dir_circ[i][j]);
										break;
									}
								}
							}

						}

						//8 directions
						//diag_f - hml
						//diag_b - hml
						//left - hl
					}

					//
				}
				else
				{
					//arm is bent therefore forearm and upper arm must be regarded separately
				}
			}

			std::cout << " DIR: " << result->getDirection(FLSkeleton::ANGLE_LEFT_WHOLE_ARM) << " # LFA: "
					<< *skeleton->getJoint(mae::fl::FLSkeleton::ANGLE_LEFT_FOREARM) << " # LUA: "
					<< *skeleton->getJoint(mae::fl::FLSkeleton::ANGLE_LEFT_UPPER_ARM) << std::endl;

			//todo do stuff in here

			return result;
		}

	} // namespace fl
} // namespace mae
