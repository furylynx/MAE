/*
 * skeleton_merger.cpp
 *
 *  Created on: 20.09.2014
 *      Author: keks
 */

#include "skeleton_merger.hpp"

namespace mae
{

	namespace fl
	{

		skeleton_merger::skeleton_merger()
		{
			fl_ctrl = std::shared_ptr<fl::fl_skeleton_controller>(new fl::fl_skeleton_controller());
		}

		skeleton_merger::~skeleton_merger()
		{
		}

		std::shared_ptr<general_skeleton> skeleton_merger::merge(
				std::vector<std::shared_ptr<general_skeleton> > skeletons)
		{

			std::vector<std::shared_ptr<mae::math::basis> > bases;

			//cleanup the skeletons vector and create bases
			for (std::vector<std::shared_ptr<general_skeleton> >::iterator it = skeletons.begin();
					it != skeletons.end();)
			{
				if ((*it) == nullptr)
				{
					it = skeletons.erase(it);
				}
				else
				{
					bases.push_back(fl_ctrl->create_torso_basis(*it));

					it++;
				}
			}

			if (skeletons.size() == 0)
			{
				//no skeleton present, therefore return null
				return nullptr;
			}
			else if (skeletons.size() == 1)
			{
				return skeletons.at(0);
			}


			//first skeleton serves as start point and information is drawn from it
			std::shared_ptr<general_skeleton> first = skeletons.at(0);

			//create result skeleton to which results will be added
			std::shared_ptr<general_skeleton> result = std::shared_ptr<general_skeleton>(
					new general_skeleton(first->get_hierarchy()));
			result->set_right_left(first->get_right_left());
			result->set_top_down(first->get_top_down());
			result->set_weight(first->get_weight());

			//first skeleton is the one the be related to
			std::vector<std::shared_ptr<hierarchy_element> > elements = first->get_hierarchy()->get_element_sequence();

			//hierarchy root is fixed
			int root_id = elements.at(0)->get_id();
			result->set_joint(root_id, first->get_joint(root_id));

			//merge all other joints
			for (unsigned int i = 1; i < elements.size(); i++)
			{
				//the processed element's id
				int el_id = elements.at(i)->get_id();

				//initialize the result values
				double r_off_u = 0;
				double r_off_r = 0;
				double r_off_t = 0;
				double r_rot = 0;
				double r_conf = 0;
				double confidence_sum = 0;
				bool confidence_sum_zero = false;

				//calculate confidence sum
				for (unsigned int j = 0; j < skeletons.size(); j++)
				{
					confidence_sum += skeletons.at(j)->get_joint(el_id)->get_confidence();
				}

				//if sum is zero, set flag
				//the flag is necessary for the calculation in order to present zero as position for joints
				if (confidence_sum == 0)
				{
					confidence_sum_zero = true;
				}

				for (unsigned int j = 0; j < skeletons.size(); j++)
				{
					//currently processed joint
					std::shared_ptr<general_joint> joint = skeletons.at(j)->get_joint(el_id);

					//offset point which is the offset in urt coordinates to the root element of the hierarchy (e.g., torso)
					std::shared_ptr<mae::math::vec3d> off_p = mae::math::math::project_to_basis_maevec(joint->vec(), bases.at(j));
					double confidence = joint->get_confidence();

					if (!confidence_sum_zero)
					{
						//do normal calculation, if sum of confidences is not zero
						r_off_u += off_p->get_x() * confidence;
						r_off_r += off_p->get_y() * confidence;
						r_off_t += off_p->get_z() * confidence;
						r_rot += joint->get_rotation() * confidence;
					}
					else
					{
						//sum of confidences is zero, handle this in order to preserve the joint to become zero
						//equal weight for all values (=1)
						r_off_u += off_p->get_x();
						r_off_r += off_p->get_y();
						r_off_t += off_p->get_z();
						r_rot += joint->get_rotation();

						confidence_sum += 1;
					}

					if (confidence > r_conf)
					{
						r_conf = confidence;
					}
				}

				//divide to get actual position in urt and rotation
				r_off_u = r_off_u / confidence_sum;
				r_off_r = r_off_r / confidence_sum;
				r_off_t = r_off_t / confidence_sum;
				r_rot = r_rot / confidence_sum;

				//translate to x,y,z
				std::shared_ptr<mae::math::vec3d> ovec = std::shared_ptr<mae::math::vec3d>(new mae::math::vec3d(r_off_u, r_off_r, r_off_t));
				std::shared_ptr<mae::math::vec3d> nvec = mae::math::math::project_back_to_default_maevec(ovec, bases.at(0));

				result->set_joint(el_id, std::shared_ptr<general_joint>(new general_joint(nvec, r_rot, r_conf)));
			}

			return result;
		}

		std::vector<std::shared_ptr<general_skeleton> > skeleton_merger::merge(
				std::vector<std::vector<std::shared_ptr<general_skeleton> > > skeletons)
		{
			std::vector<std::shared_ptr<general_skeleton> > result;

			for (unsigned int i = 0; i < skeletons.size(); i++)
			{
				result.push_back(merge(skeletons.at(i)));
			}

			return result;
		}

		std::vector<std::shared_ptr<general_skeleton> > skeleton_merger::merge_find_mapping(
				std::vector<std::vector<std::shared_ptr<general_skeleton> > > skeletons)
		{
			std::vector<std::vector<std::shared_ptr<general_skeleton> > > mapped_skels;
			mapped_skels.reserve(skeletons.size());

			//TODO find mapping
			//TODO use correlation to find mappings


			//currently only first skeleton from each stream
			std::vector<std::shared_ptr<general_skeleton> > tmp;
			for (unsigned int i = 0; i < skeletons.size(); i++)
			{
				for (unsigned int j = 0; j < skeletons.at(i).size(); j++)
				{
					if (skeletons.at(i).at(j) != nullptr)
					{
						tmp.push_back(skeletons.at(i).at(j));
						break;
					}
				}
			}

			mapped_skels.push_back(tmp);


			return merge(mapped_skels);
		}

	} // namespace fl
} // namespace mae
