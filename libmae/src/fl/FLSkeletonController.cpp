/*
 * FLSkeletonController.cpp
 *
 *  Created on: 21.05.2014
 *      Author: keks
 */

#include "FLSkeletonController.hpp"

//using mae::controller::ISkeletonController<mae::fl::FLSkeleton>::~ISkeletonController;

namespace mae
{
	namespace fl
	{

		FLSkeletonController::FLSkeletonController()
		{

			//initialize extremities

			//use temp vector
			std::vector<int> joints;

			//left arm
			joints.push_back(MAEJ_LEFT_SHOULDER);
			joints.push_back(MAEJ_LEFT_ELBOW);
			joints.push_back(MAEJ_LEFT_HAND);

			joints.push_back(FLJ_LEFT_UPPER_ARM);
			joints.push_back(FLJ_LEFT_FOREARM);
			joints.push_back(FLJ_LEFT_WHOLE_ARM);

			skel_extremities.push_back(joints);
			//skel_main_directions.push_back(r);
			joints.clear();

			//right arm
			joints.push_back(MAEJ_RIGHT_SHOULDER);
			joints.push_back(MAEJ_RIGHT_ELBOW);
			joints.push_back(MAEJ_RIGHT_HAND);

			joints.push_back(FLJ_RIGHT_UPPER_ARM);
			joints.push_back(FLJ_RIGHT_FOREARM);
			joints.push_back(FLJ_RIGHT_WHOLE_ARM);

			skel_extremities.push_back(joints);
			//						md.push_back(r);
			joints.clear();

			//left leg
			joints.push_back(MAEJ_LEFT_HIP);
			joints.push_back(MAEJ_LEFT_KNEE);
			joints.push_back(MAEJ_LEFT_FOOT);

			joints.push_back(FLJ_LEFT_THIGH);
			joints.push_back(FLJ_LEFT_SHANK);			//unterschenkel
			joints.push_back(FLJ_LEFT_WHOLE_LEG);

			skel_extremities.push_back(joints);
			//						md.push_back(u);
			joints.clear();

			//left leg
			joints.push_back(MAEJ_RIGHT_HIP);
			joints.push_back(MAEJ_RIGHT_KNEE);
			joints.push_back(MAEJ_RIGHT_FOOT);

			joints.push_back(FLJ_RIGHT_THIGH);
			joints.push_back(FLJ_RIGHT_SHANK);			//unterschenkel
			joints.push_back(FLJ_RIGHT_WHOLE_LEG);

			skel_extremities.push_back(joints);
			//						md.push_back(u);
			joints.clear();
		}

		FLSkeletonController::~FLSkeletonController()
		{
		}

		std::shared_ptr<mae::fl::FLSkeleton> FLSkeletonController::specified_skeleton(
				std::shared_ptr<mae::model::GeneralSkeleton> skeleton)
		{
			const bool calculate_angular = false;

			//get elements from the hierarchy
			std::vector<std::shared_ptr<HierarchyElement>> elements = skeleton->get_hierarchy()->get_element_sequence();

			// ---
			// calculate the torso frame
			// ---

			// fill all joints of torso into matrix in order to
			// reduce it to three vectors that are used for the coordinate system
			int torso_specified_joints = 0;
			std::vector<int> torso_parts;
			for (unsigned int i = 0; i < elements.size(); i++)
			{
				if (elements.at(i)->is_torso_joint())
				{
					if (skeleton->get_joint(elements.at(i)->get_id())->isValid())
					{
						torso_parts.push_back(elements.at(i)->get_id());
					}

					torso_specified_joints++;
				}
			}

			//check for enough specified torso joints to generate the basis
			if (torso_specified_joints < 3)
			{
				throw new std::invalid_argument(
						"Cannot generate torso basis from the skeleton for there are not enough "
								"torso joints specified in the hierarchy. Check your hierarchy and define "
								"at least three torso joints.");
			}

			//check for enough valid torso joints to generate the basis
			if (torso_parts.size() < 3)
			{
				throw new std::invalid_argument(
						"Cannot generate torso basis from the skeleton for there are not enough "
								"valid torso joints. Check the given skeleton for invalid joints (at "
								"least three valid joints are required).");
			}

			// fill torso matrix in order to apply a pca to it
			cv::Mat torso = cv::Mat::zeros(3, torso_parts.size(), CV_64F);

			for (unsigned int i = 0; i < torso_parts.size(); i++)
			{
				torso.at<double>(0, i) = skeleton->get_joint(torso_parts.at(i))->getX();
				torso.at<double>(1, i) = skeleton->get_joint(torso_parts.at(i))->getY();
				torso.at<double>(2, i) = skeleton->get_joint(torso_parts.at(i))->getZ();
			}

			// apply PCA to get 2 principal components
			cv::Mat torso_coord;
			cv::PCA torso_pca = cv::PCA(torso, cv::Mat(), CV_PCA_DATA_AS_COL, 2);

			// get first two components
			cv::Vec3d u = torso_pca.eigenvectors.row(0).clone();
			cv::Vec3d r = torso_pca.eigenvectors.row(1).clone();

			// normalize in order to receive an orthonormal basis
			u = cv::normalize(u);
			r = cv::normalize(r);

			//TODO top-down and left-right direction?? how to know?

			//align vectors top-down/right-left
			cv::Vec3d joint_torso = FLMath::jointToVec(skeleton->get_joint(MAEJ_TORSO));
			cv::Vec3d joint_neck = FLMath::jointToVec(skeleton->get_joint(MAEJ_NECK));

			cv::Vec3d joint_ls = FLMath::jointToVec(skeleton->get_joint(MAEJ_LEFT_SHOULDER));
			cv::Vec3d joint_rs = FLMath::jointToVec(skeleton->get_joint(MAEJ_RIGHT_SHOULDER));

			if (cv::norm(joint_neck - (joint_torso + u)) < cv::norm(joint_neck - joint_torso))
			{
				u = -u;
			}

			if (cv::norm(joint_ls - (joint_rs + r)) > cv::norm(joint_ls - joint_rs))
			{
				r = -r;
			}

			//get last component
			cv::Vec3d t = u.cross(r);
			t = cv::normalize(t);

			//-----
			//calculate angular representation (if wanted)
			//-----
			std::shared_ptr<FLSkeleton> result = std::shared_ptr<mae::fl::FLSkeleton>(new FLSkeleton());
			if (calculate_angular)
			{
				result = calculate_angular_skeleton(skeleton, u, r, t);
			}

			//----------
			//calculate the offset skeleton
			//----------

			std::shared_ptr<mae::model::GeneralSkeleton> offset_skeleton = std::shared_ptr<mae::model::GeneralSkeleton>(
					new mae::model::GeneralSkeleton());

			//origin of the coordinate system is the torso (is displayed in x,y,z coordinates)
			offset_skeleton->set_joint(elements.at(0)->get_id(), skeleton->get_joint(elements.at(0)->get_id()));

			for (unsigned int i = 1; i < elements.size(); i++)
			{
				//calculate offset of each joint (is displayed in u,r,t coordinates)
				offset_skeleton->set_joint(elements.at(i)->get_id(),
						FLMath::vecToJoint(
								FLMath::projectToBasis(
										FLMath::jointToVec(skeleton->get_joint(elements.at(i)->get_id())),
										FLMath::jointToVec(skeleton->get_joint(elements.at(i)->get_parent()->get_id())),
										u, r, t)));
			}

			result->set_offset_skeleton(offset_skeleton);

			//set coordinate system to skeleton
			std::vector<double> vec_u;
			vec_u.push_back(u[0]);
			vec_u.push_back(u[1]);
			vec_u.push_back(u[2]);

			std::vector<double> vec_r;
			vec_r.push_back(r[0]);
			vec_r.push_back(r[1]);
			vec_r.push_back(r[2]);

			std::vector<double> vec_t;
			vec_t.push_back(t[0]);
			vec_t.push_back(t[1]);
			vec_t.push_back(t[2]);

			result->set_coord_sys(vec_u, vec_r, vec_t);

			return result;
		}

		std::shared_ptr<FLSkeleton> FLSkeletonController::calculate_angular_skeleton(
				std::shared_ptr<mae::model::GeneralSkeleton> skeleton, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t)
		{
			// ---
			// Calculate spherical coordinates
			// for the resulting skeleton
			// ---

			//set up the resulting skeleton
			std::shared_ptr<FLSkeleton> result = std::shared_ptr<mae::fl::FLSkeleton>(new FLSkeleton());

			for (unsigned int i = 0; i < skel_extremities.size(); i++)
			{
				int joint_i = skel_extremities[i][0];
				int joint_o = skel_extremities[i][1];
				int joint_e = skel_extremities[i][2];

				int joint_fl_i = skel_extremities[i][3];
				int joint_fl_o = skel_extremities[i][4];
				int joint_fl_w = skel_extremities[i][5];

				if (skeleton->get_joint(joint_i)->isValid() && skeleton->get_joint(joint_o)->isValid())
				{
					cv::Vec2d angles;

					angles = FLSkeletonController::first_degree_r(skeleton, joint_i, joint_o, u, r, t);
					result->set_joint(joint_fl_i, std::shared_ptr<FLJoint>(new FLJoint(angles[0], angles[1])));

					if (skeleton->get_joint(joint_e)->isValid())
					{
						angles = FLSkeletonController::second_degree(skeleton, joint_i, joint_o, joint_e, u, r,
								t);
						result->set_joint(joint_fl_o, std::shared_ptr<FLJoint>(new FLJoint(angles[0], angles[1])));

						//whole extremity joint
						angles = FLSkeletonController::first_degree_r(skeleton, joint_i, joint_e, u, r, t);
						result->set_joint(joint_fl_w, std::shared_ptr<FLJoint>(new FLJoint(angles[0], angles[1])));
					}
					else
					{
						//outer parts of extremity are invalid
						// TODO this is not necessary ?!
						//						result->setJoint(joint_fl_o, std::shared_ptr<FLJoint>(new FLJoint()));
						//						result->setJoint(joint_fl_w, std::shared_ptr<FLJoint>(new FLJoint()));
					}
				}
				else
				{
					//whole extremity is invalid
					// TODO this is not necessary ?!
					//					result->setJoint(joint_fl_i, std::shared_ptr<FLJoint>(new FLJoint()));
					//					result->setJoint(joint_fl_o, std::shared_ptr<FLJoint>(new FLJoint()));
					//					result->setJoint(joint_fl_w, std::shared_ptr<FLJoint>(new FLJoint()));
				}
			}

			//spherical coordinates for the head
			int joint_head_i = MAEJ_NECK;
			int joint_head_o = MAEJ_HEAD;

			int joint_fl_head_i = FLJ_HEAD;

			if (skeleton->get_joint(joint_head_i)->isValid() && skeleton->get_joint(joint_head_o)->isValid())
			{
				cv::Vec2d angles = FLSkeletonController::first_degree(skeleton, joint_head_i, joint_head_o, r,
						t, u);
				result->set_joint(joint_fl_head_i, std::shared_ptr<FLJoint>(new FLJoint(angles[0], angles[1])));
			}

			return result;
		}

		cv::Vec2d FLSkeletonController::first_degree_md(std::shared_ptr<mae::model::GeneralSkeleton> skeleton,
				int adjacent_joint, int outer_joint, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t, cv::Vec3d md)
		{
			// ---
			// calculate angles for first degree joints
			// ---

			cv::Vec3d vec_i = FLMath::jointToVec(skeleton->get_joint(adjacent_joint));
			cv::Vec3d vec_o = FLMath::jointToVec(skeleton->get_joint(outer_joint));

			//set up new rotated basis
			double beta = FLMath::calcAngleHalf(md, r);

			cv::Vec3d u_r = u;
			cv::Vec3d r_r = r;
			cv::Vec3d t_r = t;

			if (beta != 0)
			{
				cv::Vec3d b = t;

				if (beta != M_PI)
				{
					//rotate around axis b = md x r ...
					b = cv::normalize(md.cross(r));
				}

				//todo dont calculate the rotation matrix several times : efficiency!!
				//apply to all
				u_r = FLMath::rotateAroundAxis(u, b, -beta);
				// r is not needed to be rotated since the projection will work with the plane spanned by u and t
				r_r = FLMath::rotateAroundAxis(r, b, -beta);
				t_r = FLMath::rotateAroundAxis(t, b, -beta);
			}

			// get first degree bone vector
			cv::Vec3d fdvec = cv::normalize(vec_o - vec_i);

			// inclination theta
			// calculates theta in radian
			double phi = FLMath::calcAngleHalfDeg(r_r, fdvec);

			// calculates phi in radian
			double theta;

			if (FLMath::areCollinear(r_r, fdvec))
			{
				theta = 0;
			}
			else
			{
				//get azimuth phi by projecting the joint on the r-t-plane
				cv::Vec3d vec_o_p = FLMath::projectOrthogonal(vec_o, vec_i, u_r, t_r);
				cv::Vec3d fdvec_p = cv::normalize(vec_i - vec_o_p);

//				theta = FLMath::calcAngleDeg(t_r, fdvec_p);
				theta = FLMath::calc_angle_plane_deg(t_r, fdvec_p, r_r);
			}

			cv::Vec2d angles;
			angles[0] = phi;
			angles[1] = theta;

			return angles;

		}

		cv::Vec2d FLSkeletonController::first_degree_r(std::shared_ptr<mae::model::GeneralSkeleton> skeleton,
				int adjacent_joint, int outer_joint, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t)
		{
			// ---
			// calculate angles for first degree joints
			// ---

			cv::Vec3d vec_i = FLMath::jointToVec(skeleton->get_joint(adjacent_joint));
			cv::Vec3d vec_o = FLMath::jointToVec(skeleton->get_joint(outer_joint));

			// get first degree bone vector
			cv::Vec3d fdvec = cv::normalize(vec_o - vec_i);

			// inclination theta
			// calculates theta in radian
			double phi = FLMath::calcAngleHalfDeg(r, fdvec);

			// calculates phi in radian
			double theta;

			if (FLMath::areCollinear(r, fdvec))
			{
				theta = 0;
			}
			else
			{
				//get azimuth phi by projecting the joint on the r-t-plane
				cv::Vec3d vec_o_p = FLMath::projectOrthogonal(vec_o, vec_i, u, t);
				cv::Vec3d fdvec_p = cv::normalize(vec_i - vec_o_p);

//				theta = FLMath::calcAngleDeg(t, fdvec_p);
				theta = FLMath::calc_angle_plane_deg(t, fdvec_p, r);

			}

			cv::Vec2d angles;
			angles[0] = phi;
			angles[1] = theta;

			return angles;

		}

		cv::Vec2d FLSkeletonController::first_degree(std::shared_ptr<mae::model::GeneralSkeleton> skeleton,
				int adjacent_joint, int outer_joint, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t)
		{
			// ---
			// calculate angles for first degree joints
			// ---

			cv::Vec3d vec_i = FLMath::jointToVec(skeleton->get_joint(adjacent_joint));
			cv::Vec3d vec_o = FLMath::jointToVec(skeleton->get_joint(outer_joint));

			// get first degree bone vector
			cv::Vec3d fdvec = cv::normalize(vec_o - vec_i);

			// inclination theta
			// calculates theta in radian
			double phi = FLMath::calcAngleHalfDeg(u, fdvec);

			// calculates phi in radian
			double theta;

			if (FLMath::areCollinear(u, fdvec))
			{
				theta = 0;
			}
			else
			{
				//get azimuth phi by projecting the joint on the r-t-plane
				cv::Vec3d vec_o_p = FLMath::projectOrthogonal(vec_o, vec_i, r, t);
				cv::Vec3d fdvec_p = cv::normalize(vec_i - vec_o_p);

//				theta = FLMath::calcAngleDeg(r, fdvec_p);
				theta = FLMath::calc_angle_plane_deg(r, fdvec_p, u);
			}

			cv::Vec2d angles;
			angles[0] = phi;
			angles[1] = theta;

			return angles;

		}

		cv::Vec2d FLSkeletonController::second_degree(std::shared_ptr<mae::model::GeneralSkeleton> skeleton,
				int adjacent_joint, int outer_joint, int extremity_joint, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t)
		{

			// ---
			// calculate angles for second degree joints
			// ---

			cv::Vec3d vec_i = FLMath::jointToVec(skeleton->get_joint(adjacent_joint));
			cv::Vec3d vec_o = FLMath::jointToVec(skeleton->get_joint(outer_joint));
			cv::Vec3d vec_e = FLMath::jointToVec(skeleton->get_joint(extremity_joint));

			// get first degree bone vector
			cv::Vec3d fdvec = cv::normalize(vec_o - vec_i);

			// get second degree bone vector
			cv::Vec3d sdvec = cv::normalize(vec_e - vec_o);

			// calc inclination phi
			// angle between fdvec and sdvec which is the angle between r_r and sdvec (angle ranges from 0 to 180 degree
			double phi = FLMath::calcAngleHalfDeg(fdvec, sdvec);

			// calc azimuth theta
			double theta;

			if (FLMath::areCollinear(fdvec, sdvec))
			{
				// both joint vectors fdvec and sdvec are collinear
				// therefore we can set phi to zero
				theta = 0;
			}
			else
			{

				// ... by rotation angle beta
				//double beta = std::acos(fdvec.dot(r));
				//double beta = FLMath::calcAngle(fdvec, r);
				double beta = FLMath::calcAngleHalf(fdvec, r);

				//rotate around axis b = v x r ...
				cv::Vec3d b = t;

				if (beta != 0 && beta != M_PI)
				{
					b = cv::normalize(fdvec.cross(r));
				}

				//todo dont calculate the rotation matrix several times : efficiency!!
				//apply to all
				cv::Vec3d u_r = FLMath::rotateAroundAxis(u, b, -beta);
				// r is not needed to be rotated since the projection will work with the plane spanned by u and t
				// cv::Vec3d r_r = FLMath::rotateAroundAxis(r, b, beta);
				cv::Vec3d t_r = FLMath::rotateAroundAxis(t, b, -beta);

				//plane othogonal to v is E(u,t)
				cv::Vec3d sdvec_p = FLMath::projectOrthogonal(vec_e, vec_o, u_r, t_r);
				sdvec_p = cv::normalize(vec_o - sdvec_p);

//				theta = FLMath::calcAngleDeg(t_r, sdvec_p);
				theta = FLMath::calc_angle_plane_deg(t_r, sdvec_p, fdvec);
			}

			//return the angles
			cv::Vec2d angles;
			angles[0] = phi;
			angles[1] = theta;

			return angles;

		}

	} // namespace fl
} // namespace mae
