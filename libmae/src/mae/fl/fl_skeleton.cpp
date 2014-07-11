/*
 * FLSkeleton.cpp
 *
 *  Created on: 20.05.2014
 *      Author: keks
 */

#include "fl_skeleton.hpp"

namespace mae
{
	namespace fl
	{

		fl_skeleton::fl_skeleton()
		{
			this->hashmap_joints = std::unordered_map<int, std::shared_ptr<fl_joint> >();
		}

		fl_skeleton::~fl_skeleton()
		{
			hashmap_joints.clear();
		}

		void fl_skeleton::set_joint(int body_part, std::shared_ptr<fl_joint> joint)
		{

			if (hashmap_joints.find(body_part) == hashmap_joints.end())
			{
				//key is not in map
				hashmap_joints.insert(std::make_pair(body_part, joint));

			}
			else
			{
				//key already exists and will therefore be overwritten
				hashmap_joints[body_part] = joint;
			}
		}

		std::shared_ptr<fl_joint> fl_skeleton::get_joint(int body_part) const
		{

			if (hashmap_joints.find(body_part) == hashmap_joints.end())
			{
				throw std::invalid_argument("Body part is not registered in the map.");
			}
			else
			{
				// returns the joint
				return hashmap_joints.at(body_part);
			}

		}

		//throws invalid_argument exception if sizes are incorrect
		void fl_skeleton::set_coord_sys(std::vector<double> u, std::vector<double> r, std::vector<double> t)
		{

			if (u.size() == 3 && r.size() == 3 && t.size() == 3)
			{
				this->u = u;
				this->r = r;
				this->t = t;
			}
			else
			{
				throw std::invalid_argument("At least one parameter does not match the expected 3 dimensional vector.");
			}
		}

		std::vector<std::vector<double> > fl_skeleton::get_coord_sys() const
		{
			std::vector<std::vector<double> > coord_sys = std::vector<std::vector<double> >();
			coord_sys.push_back(u);
			coord_sys.push_back(r);
			coord_sys.push_back(t);

			return coord_sys;
		}

		void fl_skeleton::set_offset_skeleton(std::shared_ptr<general_skeleton> offset_skeleton)
		{
			this->offset_skeleton = offset_skeleton;
		}

		std::shared_ptr<general_skeleton> fl_skeleton::get_offset_skeleton() const
		{
			return offset_skeleton;
		}

		void fl_skeleton::set_orig_skeleton(std::shared_ptr<general_skeleton> orig_skeleton)
		{
			this->orig_skeleton_ = orig_skeleton;
		}

		std::shared_ptr<general_skeleton> fl_skeleton::get_orig_skeleton() const
		{
			return orig_skeleton_;
		}

		void fl_skeleton::set_hierarchy(std::shared_ptr<hierarchy> h)
		{
			this->hierarchy_ = h;
		}

		std::shared_ptr<hierarchy> fl_skeleton::get_hierarchy() const
		{
			return hierarchy_;
		}

		void fl_skeleton::set_top_down(std::shared_ptr<bone> top_down)
		{
			//check bone
			if (!hierarchy_)
			{
				throw std::invalid_argument(
						"Invoked set_top_down for a general_skeleton, but no hierarchy was defined.");
			}
			else
			{
				if (!hierarchy_->at(top_down->get_from())->is_torso_joint()
						|| !hierarchy_->at(top_down->get_to())->is_torso_joint())
				{
					throw std::invalid_argument("At least one of the top-down joints is not defined as a torso joint.");
				}
			}

			this->top_down = top_down;
		}

		std::shared_ptr<bone> fl_skeleton::get_top_down() const
		{
			return this->top_down;
		}

		void fl_skeleton::set_right_left(std::shared_ptr<bone> right_left)
		{
			//check bone
			if (!hierarchy_)
			{
				throw std::invalid_argument(
						"Invoked set_right_left for a general_skeleton, but no hierarchy was defined.");
			}
			else
			{
				if (!hierarchy_->at(top_down->get_from())->is_torso_joint()
						|| !hierarchy_->at(top_down->get_to())->is_torso_joint())
				{
					throw std::invalid_argument("At least one of the top-down joints is not defined as a torso joint.");
				}
			}

			this->right_left = right_left;
		}

		std::shared_ptr<bone> fl_skeleton::get_right_left() const
		{
			return this->right_left;
		}

		std::string fl_skeleton::str() const
		{
			std::stringstream sstr;
			sstr << "fl skeleton:" << std::endl;

			if (hierarchy_)
			{
				std::vector<std::shared_ptr<hierarchy_element> > elements = hierarchy_->get_element_sequence();

				for (unsigned int i = 0; i < elements.size(); i++)
				{
					sstr << elements.at(i)->get_name() << " " << get_joint(elements.at(i)->get_id()) << std::endl;
				}
			}
			else
			{
				sstr << "--no hierarchy defined--" << std::endl;
			}

			return sstr.str();
		}

	}				// namespace fl
} // namespace mae
