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

			//-----
			//calculate the torso basis
			//-----
			std::shared_ptr<mae::math::basis> torso_basis = create_torso_basis(skeleton);

			//-----
			//set up the result
			//-----
			std::shared_ptr<fl_skeleton> result = std::shared_ptr<mae::fl::fl_skeleton>(new fl_skeleton());

			//set hierarchy
			result->set_hierarchy(skeleton->get_hierarchy());

			//----------
			//calculate the offset skeleton
			//----------

			//get elements from the hierarchy
			std::vector<std::shared_ptr<hierarchy_element>> elements =
					skeleton->get_hierarchy()->get_element_sequence();

			//origin of the coordinate system is the torso (is displayed in x,y,z coordinates)
			result->set_joint(elements.at(0)->get_id(), skeleton->get_joint(elements.at(0)->get_id()));

			for (unsigned int i = 1; i < elements.size(); i++)
			{
				//calculate offset of each joint (is displayed in u,r,t coordinates)
				result->set_joint(elements.at(i)->get_id(),
						mae::math::math::vec_to_joint(
								mae::math::math::project_to_basis(skeleton->get_joint(elements.at(i)->get_id())->vec(),
										torso_basis, skeleton->get_joint(elements.at(i)->get_parent()->get_id())->vec() )));

				//set confidence and rotation
				result->get_joint(elements.at(i)->get_id())->set_rotation(
						skeleton->get_joint(elements.at(i)->get_id())->get_rotation());
				result->get_joint(elements.at(i)->get_id())->set_confidence(
						skeleton->get_joint(elements.at(i)->get_id())->get_confidence());
			}

			//set the original skeleton
			result->set_orig_skeleton(skeleton);

			//set coordinate system to skeleton
			result->set_torso_basis(torso_basis);

			return result;
		}

		std::shared_ptr<mae::math::basis> fl_skeleton_controller::create_torso_basis(std::shared_ptr<general_skeleton> skeleton)
		{
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

			cv::Vec3d joint_top = mae::math::math::joint_to_vec(skeleton->get_joint(top_down->get_from()));
			cv::Vec3d joint_down = mae::math::math::joint_to_vec(skeleton->get_joint(top_down->get_to()));

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

			cv::Vec3d joint_right = mae::math::math::joint_to_vec(skeleton->get_joint(right_left->get_from()));
			cv::Vec3d joint_left = mae::math::math::joint_to_vec(skeleton->get_joint(right_left->get_to()));

			if (cv::norm(joint_left - (joint_right + r)) > cv::norm(joint_left - joint_right))
			{
				r = -r;
			}

			//get last component
			t = cv::normalize(u.cross(r));

			if (skeleton->get_weight() != nullptr)
			{
				//if weight is defined, manipulate the torso basis in order to represent the weight direction instead of top-down

				cv::Vec3d w = mae::math::math::maevec_to_vec3d(skeleton->get_weight());

				if (!mae::math::math::are_collinear(w, r))
				{
					if (!mae::math::math::are_collinear(w, t))
					{
						if (mae::math::math::calc_angle_half(w, u) < M_PI_2)
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
						if (mae::math::math::calc_angle_half(w, t) < M_PI_2)
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
					if (mae::math::math::calc_angle_half(w, r) < M_PI_2)
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

			cv::Vec3d position_vector = mae::math::math::joint_to_vec(skeleton->get_joint(elements.at(0)->get_id()));

			return std::shared_ptr<mae::math::basis>(
					new mae::math::basis(mae::math::math::vec3d_to_maevec(position_vector), mae::math::math::vec3d_to_maevec(u),
							mae::math::math::vec3d_to_maevec(r), mae::math::math::vec3d_to_maevec(t)));
		}

	} // namespace fl
} // namespace mae
