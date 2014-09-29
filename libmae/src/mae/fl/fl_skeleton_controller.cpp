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

		fl_skeleton_controller::fl_skeleton_controller(bool debug)
		{
			debug_ = debug;
		}

		fl_skeleton_controller::~fl_skeleton_controller()
		{
		}

		std::shared_ptr<fl_skeleton> fl_skeleton_controller::specified_skeleton(
				std::shared_ptr<general_skeleton> skeleton)
		{
			if (debug_)
			{
				std::cout << "fl_skeleton_controller: specified skeleton" << std::endl;
			}

			//get elements from the hierarchy
			std::vector<std::shared_ptr<hierarchy_element>> elements =
					skeleton->get_hierarchy()->get_element_sequence();

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
			cv::Vec3d t;

			//align vectors top-down/right-left
			std::shared_ptr<bone> top_down = skeleton->get_top_down();
			std::shared_ptr<bone> right_left = skeleton->get_right_left();

			if (!top_down || !skeleton->get_joint(top_down->get_from())->is_valid()
					|| !skeleton->get_joint(top_down->get_to())->is_valid())
			{
				throw std::invalid_argument("skeleton has either not top-down definition or the joints are invalid.");
			}

			cv::Vec3d joint_top = math::joint_to_vec(skeleton->get_joint(top_down->get_from()));
			cv::Vec3d joint_down = math::joint_to_vec(skeleton->get_joint(top_down->get_to()));

			if (cv::norm(joint_top - (joint_down + u)) < cv::norm(joint_top - joint_down))
			{
				u = -u;
			}

			//fix right-left direction

			if (!right_left || !skeleton->get_joint(right_left->get_from())->is_valid()
					|| !skeleton->get_joint(right_left->get_to())->is_valid())
			{
				throw std::invalid_argument("skeleton has either not right-left definition or the joints are invalid.");
			}

			cv::Vec3d joint_right = math::joint_to_vec(skeleton->get_joint(right_left->get_from()));
			cv::Vec3d joint_left = math::joint_to_vec(skeleton->get_joint(right_left->get_to()));

			if (cv::norm(joint_left - (joint_right + r)) > cv::norm(joint_left - joint_right))
			{
				r = -r;
			}

			//get last component
			t = cv::normalize(u.cross(r));

			if (skeleton->get_weight() != nullptr)
			{
				//if weight is defined, manipulate the torso basis in order to represent the weight direction instead of top-down

				cv::Vec3d w = math::maevec_to_vec3d(skeleton->get_weight());

				if (!math::are_collinear(w, r))
				{
					if (!math::are_collinear(w, t))
					{
						if (math::calc_angle_half(w, u) < M_PI_2)
						{
							//standing normally
							u = w;
							t = cv::normalize(u.cross(r));
							r = cv::normalize(t.cross(u));
						}
						else
						{
							//standing on head
							u = w;
							t = cv::normalize(r.cross(u));
							r = cv::normalize(u.cross(t));
						}
					}
					else
					{
						if (math::calc_angle_half(w, t) < M_PI_2)
						{
							//lying on stomach
							u = w;
							t = cv::normalize(r.cross(u));
							r = cv::normalize(t.cross(u));
						}
						else
						{
							//lying on back
							u = w;
							t = cv::normalize(u.cross(r));
							r = cv::normalize(u.cross(t));
						}
					}
				}
				else
				{
					if (math::calc_angle_half(w, r) < M_PI_2)
					{
						//w and r point in the same direction
						//lying on left side
						t = u.cross(w);
						r = t.cross(w);
						u = w;
					}
					else
					{
						//w and r point in different directions
						//lying on right side
						t = w.cross(u);
						r = t.cross(w);
						u = w;
					}
				}
			}

			//-----
			//calculate angular representation (if wanted)
			//-----
			std::shared_ptr<fl_skeleton> result = std::shared_ptr<mae::fl::fl_skeleton>(new fl_skeleton());

			//set hierarchy
			result->set_hierarchy(skeleton->get_hierarchy());

			//----------
			//calculate the offset skeleton
			//----------

			//origin of the coordinate system is the torso (is displayed in x,y,z coordinates)
			result->set_joint(elements.at(0)->get_id(), skeleton->get_joint(elements.at(0)->get_id()));

			for (unsigned int i = 1; i < elements.size(); i++)
			{
				//calculate offset of each joint (is displayed in u,r,t coordinates)
				result->set_joint(elements.at(i)->get_id(),
						math::vec_to_joint(
								math::project_to_basis(
										math::joint_to_vec(skeleton->get_joint(elements.at(i)->get_id())),
										math::joint_to_vec(skeleton->get_joint(elements.at(i)->get_parent()->get_id())),
										u, r, t)));
			}

			//set the original skeleton
			result->set_orig_skeleton(skeleton);

			//set coordinate system to skeleton
			std::shared_ptr<vec3d> vec_u = math::vec3d_to_maevec(u);
			std::shared_ptr<vec3d> vec_r = math::vec3d_to_maevec(r);
			std::shared_ptr<vec3d> vec_t = math::vec3d_to_maevec(t);

			result->set_coord_sys(vec_u, vec_r, vec_t);

			return result;
		}

	} // namespace fl
} // namespace mae
