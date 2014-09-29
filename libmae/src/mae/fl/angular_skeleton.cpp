/*
 * angular_skeleton.cpp
 *
 *  Created on: 29.09.2014
 *      Author: keks
 */

#include "angular_skeleton.hpp"

namespace mae
{
	namespace fl
	{

		angular_skeleton::angular_skeleton()
		{
			// TODO Auto-generated constructor stub

		}

		angular_skeleton::~angular_skeleton()
		{
			// TODO Auto-generated destructor stub
		}

		void angular_skeleton::set_joint(int body_part, std::shared_ptr<angular_joint> joint)
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

		std::shared_ptr<angular_joint> angular_skeleton::get_joint(int body_part) const
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

		void angular_skeleton::set_hierarchy(std::shared_ptr<hierarchy> h)
		{
			this->hierarchy_ = h;
		}

		std::shared_ptr<hierarchy> angular_skeleton::get_hierarchy() const
		{
			return hierarchy_;
		}

		void angular_skeleton::set_coord_sys(std::shared_ptr<vec3d> u, std::shared_ptr<vec3d> r, std::shared_ptr<vec3d> t)
		{

			if (u != nullptr && r != nullptr && t != nullptr)
			{
				u_ = u;
				r_ = r;
				t_ = t;
			}
			else
			{
				throw std::invalid_argument("At least one parameter is a null pointer.");
			}
		}

		std::vector<std::shared_ptr<vec3d> > angular_skeleton::get_coord_sys() const
		{
			std::vector<std::shared_ptr<vec3d> > coord_sys;
			coord_sys.push_back(u_);
			coord_sys.push_back(r_);
			coord_sys.push_back(t_);

			return coord_sys;
		}

		void angular_skeleton::set_top_down(std::shared_ptr<bone> top_down)
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

		std::shared_ptr<bone> angular_skeleton::get_top_down() const
		{
			return this->top_down;
		}

		void angular_skeleton::set_right_left(std::shared_ptr<bone> right_left)
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

		std::shared_ptr<bone> angular_skeleton::get_right_left() const
		{
			return this->right_left;
		}


		std::string angular_skeleton::str() const
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
	} // namespace fl
} // namespace mae
