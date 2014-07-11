/*
 * FLSkeletonController.cpp
 *
 *  Created on: 21.05.2014
 *      Author: keks
 */

#include "fl_skeleton_controller.hpp"

namespace mae
{
	namespace fl
	{

		fl_skeleton_controller::fl_skeleton_controller()
		{

			//initialize extremities

			//use temp vector
			std::vector<int> joints;

			//left arm
			joints.push_back(e_joint_c::to_int(e_joint::LEFT_SHOULDER));
			joints.push_back(e_joint_c::to_int(e_joint::LEFT_ELBOW));
			joints.push_back(e_joint_c::to_int(e_joint::LEFT_HAND));

			joints.push_back(e_fl_joint_c::to_int(e_fl_joint::LEFT_UPPER_ARM));
			joints.push_back(e_fl_joint_c::to_int(e_fl_joint::LEFT_FOREARM));
			joints.push_back(e_fl_joint_c::to_int(e_fl_joint::LEFT_WHOLE_ARM));

			skel_extremities.push_back(joints);
			//skel_main_directions.push_back(r);
			joints.clear();

			//right arm
			joints.push_back(e_joint_c::to_int(e_joint::RIGHT_SHOULDER));
			joints.push_back(e_joint_c::to_int(e_joint::RIGHT_ELBOW));
			joints.push_back(e_joint_c::to_int(e_joint::RIGHT_HAND));

			joints.push_back(e_fl_joint_c::to_int(e_fl_joint::RIGHT_UPPER_ARM));
			joints.push_back(e_fl_joint_c::to_int(e_fl_joint::RIGHT_FOREARM));
			joints.push_back(e_fl_joint_c::to_int(e_fl_joint::RIGHT_WHOLE_ARM));

			skel_extremities.push_back(joints);
			//						md.push_back(r);
			joints.clear();

			//left leg
			joints.push_back(e_joint_c::to_int(e_joint::LEFT_HIP));
			joints.push_back(e_joint_c::to_int(e_joint::LEFT_KNEE));
			joints.push_back(e_joint_c::to_int(e_joint::LEFT_FOOT));

			joints.push_back(e_fl_joint_c::to_int(e_fl_joint::LEFT_THIGH));
			joints.push_back(e_fl_joint_c::to_int(e_fl_joint::LEFT_SHANK));			//unterschenkel
			joints.push_back(e_fl_joint_c::to_int(e_fl_joint::LEFT_WHOLE_LEG));

			skel_extremities.push_back(joints);
			//						md.push_back(u);
			joints.clear();

			//left leg
			joints.push_back(e_joint_c::to_int(e_joint::RIGHT_HIP));
			joints.push_back(e_joint_c::to_int(e_joint::RIGHT_KNEE));
			joints.push_back(e_joint_c::to_int(e_joint::RIGHT_FOOT));

			joints.push_back(e_fl_joint_c::to_int(e_fl_joint::RIGHT_THIGH));
			joints.push_back(e_fl_joint_c::to_int(e_fl_joint::RIGHT_SHANK));			//unterschenkel
			joints.push_back(e_fl_joint_c::to_int(e_fl_joint::RIGHT_WHOLE_LEG));

			skel_extremities.push_back(joints);
			//						md.push_back(u);
			joints.clear();
		}

		fl_skeleton_controller::~fl_skeleton_controller()
		{
		}

		std::shared_ptr<fl_skeleton> fl_skeleton_controller::specified_skeleton(
				std::shared_ptr<general_skeleton> skeleton)
		{
			const bool calculate_angular = false;

			//get elements from the hierarchy
			std::vector<std::shared_ptr<hierarchy_element>> elements = skeleton->get_hierarchy()->get_element_sequence();

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
					if (skeleton->get_joint(elements.at(i)->get_id())->is_valid())
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
				torso.at<double>(0, i) = skeleton->get_joint(torso_parts.at(i))->get_x();
				torso.at<double>(1, i) = skeleton->get_joint(torso_parts.at(i))->get_y();
				torso.at<double>(2, i) = skeleton->get_joint(torso_parts.at(i))->get_z();
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

			//align vectors top-down/right-left
			std::shared_ptr<bone> top_down = skeleton->get_top_down();
			std::shared_ptr<bone> right_left = skeleton->get_right_left();

			if (!top_down || !skeleton->get_joint(top_down->get_from())->is_valid() || !skeleton->get_joint(top_down->get_to())->is_valid())
			{
				throw std::invalid_argument("skeleton has either not top-down definition or the joints are invalid.");
			}

			if (!right_left || !skeleton->get_joint(right_left->get_from())->is_valid() || !skeleton->get_joint(right_left->get_to())->is_valid())
			{
				throw std::invalid_argument("skeleton has either not right-left definition or the joints are invalid.");
			}

			cv::Vec3d joint_top = math::jointToVec(skeleton->get_joint(top_down->get_from()));
			cv::Vec3d joint_down = math::jointToVec(skeleton->get_joint(top_down->get_to()));

			cv::Vec3d joint_right = math::jointToVec(skeleton->get_joint(right_left->get_from()));
			cv::Vec3d joint_left = math::jointToVec(skeleton->get_joint(right_left->get_to()));

			if (cv::norm(joint_top - (joint_down + u)) < cv::norm(joint_top - joint_down))
			{
				u = -u;
			}

			if (cv::norm(joint_left - (joint_right + r)) > cv::norm(joint_left - joint_right))
			{
				r = -r;
			}

			//get last component
			cv::Vec3d t = u.cross(r);
			t = cv::normalize(t);

			//-----
			//calculate angular representation (if wanted)
			//-----
			std::shared_ptr<fl_skeleton> result = std::shared_ptr<mae::fl::fl_skeleton>(new fl_skeleton());
			if (calculate_angular)
			{
				result = calculate_angular_skeleton(skeleton, u, r, t);
			}

			//set hierarchy
			result->set_hierarchy(skeleton->get_hierarchy());

			//----------
			//calculate the offset skeleton
			//----------

			std::shared_ptr<general_skeleton> offset_skeleton = std::shared_ptr<general_skeleton>(
					new general_skeleton());

			//origin of the coordinate system is the torso (is displayed in x,y,z coordinates)
			offset_skeleton->set_joint(elements.at(0)->get_id(), skeleton->get_joint(elements.at(0)->get_id()));

			for (unsigned int i = 1; i < elements.size(); i++)
			{
				//calculate offset of each joint (is displayed in u,r,t coordinates)
				offset_skeleton->set_joint(elements.at(i)->get_id(),
						math::vecToJoint(
								math::projectToBasis(
										math::jointToVec(skeleton->get_joint(elements.at(i)->get_id())),
										math::jointToVec(skeleton->get_joint(elements.at(i)->get_parent()->get_id())),
										u, r, t)));
			}

			result->set_offset_skeleton(offset_skeleton);

			//set the original skeleton
			result->set_orig_skeleton(skeleton);

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

		std::shared_ptr<fl_skeleton> fl_skeleton_controller::calculate_angular_skeleton(
				std::shared_ptr<general_skeleton> skeleton, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t)
		{
			// ---
			// Calculate spherical coordinates
			// for the resulting skeleton
			// ---

			//set up the resulting skeleton
			std::shared_ptr<fl_skeleton> result = std::shared_ptr<mae::fl::fl_skeleton>(new fl_skeleton());

			for (unsigned int i = 0; i < skel_extremities.size(); i++)
			{
				int joint_i = skel_extremities[i][0];
				int joint_o = skel_extremities[i][1];
				int joint_e = skel_extremities[i][2];

				int joint_fl_i = skel_extremities[i][3];
				int joint_fl_o = skel_extremities[i][4];
				int joint_fl_w = skel_extremities[i][5];

				if (skeleton->get_joint(joint_i)->is_valid() && skeleton->get_joint(joint_o)->is_valid())
				{
					cv::Vec2d angles;

					angles = fl_skeleton_controller::first_degree_r(skeleton, joint_i, joint_o, u, r, t);
					result->set_joint(joint_fl_i, std::shared_ptr<fl_joint>(new fl_joint(angles[0], angles[1])));

					if (skeleton->get_joint(joint_e)->is_valid())
					{
						angles = fl_skeleton_controller::second_degree(skeleton, joint_i, joint_o, joint_e, u, r,
								t);
						result->set_joint(joint_fl_o, std::shared_ptr<fl_joint>(new fl_joint(angles[0], angles[1])));

						//whole extremity joint
						angles = fl_skeleton_controller::first_degree_r(skeleton, joint_i, joint_e, u, r, t);
						result->set_joint(joint_fl_w, std::shared_ptr<fl_joint>(new fl_joint(angles[0], angles[1])));
					}
				}
			}

			//spherical coordinates for the head
			int joint_head_i = e_joint_c::to_int(e_joint::NECK);
			int joint_head_o = e_joint_c::to_int(e_joint::HEAD);

			int joint_fl_head_i = e_fl_joint_c::to_int(e_fl_joint::HEAD);

			if (skeleton->get_joint(joint_head_i)->is_valid() && skeleton->get_joint(joint_head_o)->is_valid())
			{
				cv::Vec2d angles = fl_skeleton_controller::first_degree(skeleton, joint_head_i, joint_head_o, r,
						t, u);
				result->set_joint(joint_fl_head_i, std::shared_ptr<fl_joint>(new fl_joint(angles[0], angles[1])));
			}

			return result;
		}

		cv::Vec2d fl_skeleton_controller::first_degree_md(std::shared_ptr<general_skeleton> skeleton,
				int adjacent_joint, int outer_joint, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t, cv::Vec3d md)
		{
			// ---
			// calculate angles for first degree joints
			// ---

			cv::Vec3d vec_i = math::jointToVec(skeleton->get_joint(adjacent_joint));
			cv::Vec3d vec_o = math::jointToVec(skeleton->get_joint(outer_joint));

			//set up new rotated basis
			double beta = math::calcAngleHalf(md, r);

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

				//TODO dont calculate the rotation matrix several times : efficiency!!
				//apply to all
				u_r = math::rotateAroundAxis(u, b, -beta);
				// r is not needed to be rotated since the projection will work with the plane spanned by u and t
				r_r = math::rotateAroundAxis(r, b, -beta);
				t_r = math::rotateAroundAxis(t, b, -beta);
			}

			// get first degree bone vector
			cv::Vec3d fdvec = cv::normalize(vec_o - vec_i);

			// inclination theta
			// calculates theta in radian
			double phi = math::calcAngleHalfDeg(r_r, fdvec);

			// calculates phi in radian
			double theta;

			if (math::areCollinear(r_r, fdvec))
			{
				theta = 0;
			}
			else
			{
				//get azimuth phi by projecting the joint on the r-t-plane
				cv::Vec3d vec_o_p = math::projectOrthogonal(vec_o, vec_i, u_r, t_r);
				cv::Vec3d fdvec_p = cv::normalize(vec_i - vec_o_p);

//				theta = FLMath::calcAngleDeg(t_r, fdvec_p);
				theta = math::calc_angle_plane_deg(t_r, fdvec_p, r_r);
			}

			cv::Vec2d angles;
			angles[0] = phi;
			angles[1] = theta;

			return angles;

		}

		cv::Vec2d fl_skeleton_controller::first_degree_r(std::shared_ptr<general_skeleton> skeleton,
				int adjacent_joint, int outer_joint, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t)
		{
			// ---
			// calculate angles for first degree joints
			// ---

			cv::Vec3d vec_i = math::jointToVec(skeleton->get_joint(adjacent_joint));
			cv::Vec3d vec_o = math::jointToVec(skeleton->get_joint(outer_joint));

			// get first degree bone vector
			cv::Vec3d fdvec = cv::normalize(vec_o - vec_i);

			// inclination theta
			// calculates theta in radian
			double phi = math::calcAngleHalfDeg(r, fdvec);

			// calculates phi in radian
			double theta;

			if (math::areCollinear(r, fdvec))
			{
				theta = 0;
			}
			else
			{
				//get azimuth phi by projecting the joint on the r-t-plane
				cv::Vec3d vec_o_p = math::projectOrthogonal(vec_o, vec_i, u, t);
				cv::Vec3d fdvec_p = cv::normalize(vec_i - vec_o_p);

//				theta = FLMath::calcAngleDeg(t, fdvec_p);
				theta = math::calc_angle_plane_deg(t, fdvec_p, r);

			}

			cv::Vec2d angles;
			angles[0] = phi;
			angles[1] = theta;

			return angles;

		}

		cv::Vec2d fl_skeleton_controller::first_degree(std::shared_ptr<general_skeleton> skeleton,
				int adjacent_joint, int outer_joint, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t)
		{
			// ---
			// calculate angles for first degree joints
			// ---

			cv::Vec3d vec_i = math::jointToVec(skeleton->get_joint(adjacent_joint));
			cv::Vec3d vec_o = math::jointToVec(skeleton->get_joint(outer_joint));

			// get first degree bone vector
			cv::Vec3d fdvec = cv::normalize(vec_o - vec_i);

			// inclination theta
			// calculates theta in radian
			double phi = math::calcAngleHalfDeg(u, fdvec);

			// calculates phi in radian
			double theta;

			if (math::areCollinear(u, fdvec))
			{
				theta = 0;
			}
			else
			{
				//get azimuth phi by projecting the joint on the r-t-plane
				cv::Vec3d vec_o_p = math::projectOrthogonal(vec_o, vec_i, r, t);
				cv::Vec3d fdvec_p = cv::normalize(vec_i - vec_o_p);

//				theta = FLMath::calcAngleDeg(r, fdvec_p);
				theta = math::calc_angle_plane_deg(r, fdvec_p, u);
			}

			cv::Vec2d angles;
			angles[0] = phi;
			angles[1] = theta;

			return angles;

		}

		cv::Vec2d fl_skeleton_controller::second_degree(std::shared_ptr<general_skeleton> skeleton,
				int adjacent_joint, int outer_joint, int extremity_joint, cv::Vec3d u, cv::Vec3d r, cv::Vec3d t)
		{

			// ---
			// calculate angles for second degree joints
			// ---

			cv::Vec3d vec_i = math::jointToVec(skeleton->get_joint(adjacent_joint));
			cv::Vec3d vec_o = math::jointToVec(skeleton->get_joint(outer_joint));
			cv::Vec3d vec_e = math::jointToVec(skeleton->get_joint(extremity_joint));

			// get first degree bone vector
			cv::Vec3d fdvec = cv::normalize(vec_o - vec_i);

			// get second degree bone vector
			cv::Vec3d sdvec = cv::normalize(vec_e - vec_o);

			// calc inclination phi
			// angle between fdvec and sdvec which is the angle between r_r and sdvec (angle ranges from 0 to 180 degree
			double phi = math::calcAngleHalfDeg(fdvec, sdvec);

			// calc azimuth theta
			double theta;

			if (math::areCollinear(fdvec, sdvec))
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
				double beta = math::calcAngleHalf(fdvec, r);

				//rotate around axis b = v x r ...
				cv::Vec3d b = t;

				if (beta != 0 && beta != M_PI)
				{
					b = cv::normalize(fdvec.cross(r));
				}

				//TODO dont calculate the rotation matrix several times : efficiency!!
				//apply to all
				cv::Vec3d u_r = math::rotateAroundAxis(u, b, -beta);
				// r is not needed to be rotated since the projection will work with the plane spanned by u and t
				// cv::Vec3d r_r = FLMath::rotateAroundAxis(r, b, beta);
				cv::Vec3d t_r = math::rotateAroundAxis(t, b, -beta);

				//plane othogonal to v is E(u,t)
				cv::Vec3d sdvec_p = math::projectOrthogonal(vec_e, vec_o, u_r, t_r);
				sdvec_p = cv::normalize(vec_o - sdvec_p);

//				theta = FLMath::calcAngleDeg(t_r, sdvec_p);
				theta = math::calc_angle_plane_deg(t_r, sdvec_p, fdvec);
			}

			//return the angles
			cv::Vec2d angles;
			angles[0] = phi;
			angles[1] = theta;

			return angles;

		}

	} // namespace fl
} // namespace mae
