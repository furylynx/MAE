#include "fl_skeleton_controller.hpp"

//internal includes
#include "../math/internal_math.hh"

#include <opencv2/opencv.hpp>

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
				std::shared_ptr<general_skeleton> skeleton, std::shared_ptr<mae::math::basis> basis)
		{
			if (debug_)
			{
				std::cout << "fl_skeleton_controller: specified skeleton" << std::endl;
			}

			//-----
			//calculate the torso basis
			//-----
			if (basis == nullptr)
			{
				//std::shared_ptr<mae::math::basis>
				basis = create_basis(skeleton);
			}

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
						mae::math::internal_math::vec_to_joint(
								mae::math::internal_math::project_to_basis(skeleton->get_joint(elements.at(i)->get_id())->vec(),
										basis, skeleton->get_joint(elements.at(i)->get_parent()->get_id())->vec() )));

				//set confidence and rotation
				result->get_joint(elements.at(i)->get_id())->set_rotation(
						skeleton->get_joint(elements.at(i)->get_id())->get_rotation());
				result->get_joint(elements.at(i)->get_id())->set_confidence(
						skeleton->get_joint(elements.at(i)->get_id())->get_confidence());
			}

			//set the original skeleton
			result->set_orig_skeleton(skeleton);

			//set coordinate system to skeleton as a system of reference
			result->set_basis(basis);

			return result;
		}

		std::shared_ptr<mae::math::basis> fl_skeleton_controller::create_torso_basis(std::shared_ptr<general_skeleton> skeleton)
		{
			return create_basis(skeleton);
		}

		std::shared_ptr<mae::math::basis> fl_skeleton_controller::create_basis(std::shared_ptr<general_skeleton> skeleton)
		{
			//get elements from the hierarchy
			std::vector<std::shared_ptr<hierarchy_element>> elements =
					skeleton->get_hierarchy()->get_element_sequence();

			// ---
			// calculate the torso frame
			// ---

			// fill all joints of base system (system of reference, e.g. the torso) into matrix in order to
			// reduce it to three vectors that are used for the coordinate system
			int base_specified_joints = 0;
			std::vector<int> base_parts;
			for (unsigned int i = 0; i < elements.size(); i++)
			{
				if (elements.at(i)->is_base_joint())
				{
					if (skeleton->get_joint(elements.at(i)->get_id())->is_valid())
					{
						base_parts.push_back(elements.at(i)->get_id());
					}

					base_specified_joints++;
				}
			}

			//check for enough specified torso joints to generate the basis
			if (base_specified_joints < 3)
			{
				throw new std::invalid_argument(
						"Cannot generate basis from the skeleton since there are not enough "
								"base joints specified in the hierarchy. Check your hierarchy and define "
								"at least three (correlated) base joints.");
			}

			//check for enough valid torso joints to generate the basis
			if (base_parts.size() < 3)
			{
				throw new std::invalid_argument(
						"Cannot generate basis from the skeleton since there are not enough "
								"valid base joints. Check the given skeleton for invalid joints (at "
								"least three valid (correlated) joints are required).");
			}

			// fill base matrix in order to apply a pca (principal components analysis) to it
			cv::Mat base_matrix = cv::Mat::zeros(3, base_parts.size(), CV_64F);

			for (unsigned int i = 0; i < base_parts.size(); i++)
			{
				base_matrix.at<double>(0, i) = skeleton->get_joint(base_parts.at(i))->get_x();
				base_matrix.at<double>(1, i) = skeleton->get_joint(base_parts.at(i))->get_y();
				base_matrix.at<double>(2, i) = skeleton->get_joint(base_parts.at(i))->get_z();
			}

			// apply PCA to get 2 principal components
			cv::Mat base_coord;
#ifndef CV_PCA_DATA_AS_COL
            cv::PCA base_pca = cv::PCA(base_matrix, cv::Mat(), cv::PCA::DATA_AS_COL, 2);
#else
            cv::PCA base_pca = cv::PCA(base_matrix, cv::Mat(), CV_PCA_DATA_AS_COL, 2);
#endif
			

			// get first two components
			cv::Vec3d u = base_pca.eigenvectors.row(0).clone();
			cv::Vec3d r = base_pca.eigenvectors.row(1).clone();

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

			cv::Vec3d joint_top = mae::math::internal_math::joint_to_vec(skeleton->get_joint(top_down->get_from()));
			cv::Vec3d joint_down = mae::math::internal_math::joint_to_vec(skeleton->get_joint(top_down->get_to()));

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

			cv::Vec3d joint_right = mae::math::internal_math::joint_to_vec(skeleton->get_joint(right_left->get_from()));
			cv::Vec3d joint_left = mae::math::internal_math::joint_to_vec(skeleton->get_joint(right_left->get_to()));

			if (cv::norm(joint_left - (joint_right + r)) > cv::norm(joint_left - joint_right))
			{
				r = -r;
			}

			//get last component
			t = cv::normalize(u.cross(r));

			if (skeleton->get_weight() != nullptr)
			{
				//if weight is defined, manipulate the torso basis in order to represent the weight direction instead of top-down

				cv::Vec3d w = mae::math::internal_math::maevec_to_vec3d(skeleton->get_weight());

				if (!mae::math::internal_math::are_collinear(w, r))
				{
					if (!mae::math::internal_math::are_collinear(w, t))
					{
						if (mae::math::internal_math::calc_angle_half(w, u) < M_PI_2)
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
						if (mae::math::internal_math::calc_angle_half(w, t) < M_PI_2)
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
					if (mae::math::internal_math::calc_angle_half(w, r) < M_PI_2)
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

			cv::Vec3d position_vector = mae::math::internal_math::joint_to_vec(skeleton->get_joint(elements.at(0)->get_id()));

			return std::shared_ptr<mae::math::basis>(
					new mae::math::basis(mae::math::internal_math::vec3d_to_maevec(position_vector), mae::math::internal_math::vec3d_to_maevec(u),
							mae::math::internal_math::vec3d_to_maevec(r), mae::math::internal_math::vec3d_to_maevec(t)));
		}

	} // namespace fl
} // namespace mae
