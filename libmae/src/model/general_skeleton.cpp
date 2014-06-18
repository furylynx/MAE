/*
 * general_skeleton.cpp
 *
 * Created on: 15.05.2014
 * Author: keks
 */

#include "general_skeleton.hpp"

namespace mae
{

	general_skeleton::general_skeleton()
	{
		this->hashmap_joints = std::unordered_map<int, std::shared_ptr<general_joint> >();

		this->hierarchy_ = hierarchy::default_hierarchy();

		//set top-down and right-left direction
		this->top_down = std::shared_ptr<bone>(new bone(99, "TOP_DOWN", MAEJ_NECK, MAEJ_TORSO));
		this->right_left = std::shared_ptr<bone>(new bone(100, "RIGHT_LEFT", MAEJ_RIGHT_SHOULDER, MAEJ_LEFT_SHOULDER));

	}

	general_skeleton::general_skeleton(std::shared_ptr<hierarchy> hierarchy)
	{
		this->hierarchy_ = hierarchy;
		this->hashmap_joints = std::unordered_map<int, std::shared_ptr<general_joint> >();
	}

	general_skeleton::~general_skeleton()
	{
		this->hashmap_joints.clear();
	}

	void general_skeleton::set_joint(int body_part, std::shared_ptr<general_joint> joint)
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

	std::shared_ptr<general_joint> general_skeleton::get_joint(int body_part) const
	{

		if (hashmap_joints.find(body_part) == hashmap_joints.end())
		{
			// returns an invalid joint which means that the joint is
			// not existing
			return std::shared_ptr<general_joint>(new general_joint());
		}
		else
		{
			// returns the joint
			return hashmap_joints.at(body_part);
		}

	}

	std::shared_ptr<hierarchy> general_skeleton::get_hierarchy() const
	{
		return hierarchy_;
	}

	void general_skeleton::set_hierarchy(std::shared_ptr<hierarchy> hierarchy)
	{
		this->hierarchy_ = hierarchy;
	}

	void general_skeleton::set_top_down(std::shared_ptr<bone> top_down)
	{
		//check bone
		if (!hierarchy_)
		{
			throw std::invalid_argument("Invoked set_top_down for a general_skeleton, but no hierarchy was defined.");
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

	std::shared_ptr<bone> general_skeleton::get_top_down() const
	{
		return this->top_down;
	}

	void general_skeleton::set_right_left(std::shared_ptr<bone> right_left)
	{
		//check bone
		if (!hierarchy_)
		{
			throw std::invalid_argument("Invoked set_right_left for a general_skeleton, but no hierarchy was defined.");
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

	std::shared_ptr<bone> general_skeleton::get_right_left() const
	{
		return this->right_left;
	}

	std::string general_skeleton::str() const
	{
		std::stringstream sstr;
		sstr << "general_skeleton:" << std::endl;

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

	std::string general_skeleton::ply_str() const
	{
		std::stringstream sstr;

		std::vector<std::shared_ptr<hierarchy_element> > all_elements = hierarchy_->get_element_sequence();

		//print header
		sstr << "ply" << std::endl;
		sstr << "format ascii 1.0" << std::endl;
		sstr << "element vertex " << all_elements.size() << std::endl;
		sstr << "property double x" << std::endl;
		sstr << "property double y" << std::endl;
		sstr << "property double z" << std::endl;
		sstr << "element face " << 0 << std::endl;
		sstr << "property list uchar uint vertex_indices" << std::endl;
		sstr << "element edge " << all_elements.size() - 1 << std::endl;
		sstr << "property int vertex1" << std::endl;
		sstr << "property int vertex2" << std::endl;
		sstr << "end_header" << std::endl;

		//print data
		for (int i = 0; i < all_elements.size(); i++)
		{
			int element_id = all_elements.at(i)->get_id();

			while (hierarchy_ && hierarchy_->at(element_id) && hierarchy_->at(element_id)->is_dummy()
					&& hierarchy_->at(element_id)->get_parent())
			{
				element_id = hierarchy_->at(element_id)->get_parent()->get_id();
			}

			sstr << get_joint(element_id)->get_x() << " " << get_joint(element_id)->get_y() << " "
					<< get_joint(element_id)->get_z() << std::endl;
		}

		//Print edges for data
		for (int i = 1; i < all_elements.size(); i++)
		{
			if (all_elements.at(i)->get_parent()->get_id() == all_elements.at(i - 1)->get_id())
			{
				sstr << i - 1 << " " << i << std::endl;
			}
			else
			{
				for (int j = 0; j < all_elements.size(); j++)
				{
					if (all_elements.at(i)->get_parent()->get_id() == all_elements.at(j)->get_id())
					{
						sstr << j << " " << i << std::endl;
					}
				}
			}
		}

		return sstr.str();
	}

	void general_skeleton::ply_file(std::string filename) const
	{
		std::ofstream out_file(filename);
		out_file << ply_str();
		out_file.close();
	}

} // namespace mae
