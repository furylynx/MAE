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

		this->hierarchy = Hierarchy::default_hierarchy();
	}

	general_skeleton::general_skeleton(std::shared_ptr<Hierarchy> hierarchy)
	{
		this->hierarchy = hierarchy;
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

	std::shared_ptr<Hierarchy> general_skeleton::get_hierarchy() const
	{
		return hierarchy;
	}

	void general_skeleton::set_hierarchy(std::shared_ptr<Hierarchy> hierarchy)
	{
		this->hierarchy = hierarchy;
	}

	void general_skeleton::set_top_down(std::shared_ptr<bone> top_down)
	{
		//check bone
		if (!hierarchy)
		{
			throw std::invalid_argument("Invoked set_top_down for a general_skeleton, but no hierarchy was defined.");
		}
		else
		{
			if (!hierarchy->at(top_down->get_from())->is_torso_joint()
					|| !hierarchy->at(top_down->get_to())->is_torso_joint())
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
		if (!hierarchy)
		{
			throw std::invalid_argument("Invoked set_right_left for a general_skeleton, but no hierarchy was defined.");
		}
		else
		{
			if (!hierarchy->at(top_down->get_from())->is_torso_joint()
					|| !hierarchy->at(top_down->get_to())->is_torso_joint())
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
		for (int joint_id = MAEJ_INVALID + 1; joint_id != MAEJ_SIZE; joint_id++)
		{
			sstr << maej_str[joint_id] << " " << get_joint(joint_id) << std::endl;
		}

		return sstr.str();
	}

	std::string general_skeleton::ply_str() const
	{
		std::stringstream sstr;

		//print header
		sstr << "ply" << std::endl;				//"\n";
		sstr << "format ascii 1.0" << std::endl;				//"\n";
		sstr << "element vertex " << MAEJ_SIZE - 1 << std::endl;				//"\n";
		sstr << "property double x" << std::endl;				//"\n";
		sstr << "property double y" << std::endl;				//"\n";
		sstr << "property double z" << std::endl;				//"\n";
		sstr << "element face " << 0 << std::endl;				//"\n";
		sstr << "property list uchar uint vertex_indices" << std::endl; //"\n";
		sstr << "element edge " << MAEJ_SIZE - 1 << std::endl;
		sstr << "property int vertex1" << std::endl;
		sstr << "property int vertex2" << std::endl;
		sstr << "end_header" << std::endl; //"\n";

		//scale to 1
		double max_x = 1;
		double max_y = 1;
		double max_z = 1;

		std::vector<std::shared_ptr<general_joint> > joints;
		for (int joint_id = MAEJ_INVALID + 1; joint_id != MAEJ_SIZE; joint_id++)
		{
			joints.push_back(
					std::shared_ptr<general_joint>(
							new general_joint(get_joint(joint_id)->get_x() - get_joint(MAEJ_TORSO)->get_x(),
									get_joint(joint_id)->get_y() - get_joint(MAEJ_TORSO)->get_y(),
									get_joint(joint_id)->get_z() - get_joint(MAEJ_TORSO)->get_z())));

			if (((std::shared_ptr<general_joint>) joints[joint_id - 1])->get_x() > max_x)
			{
				max_x = ((std::shared_ptr<general_joint>) joints[joint_id - 1])->get_x();
			}
			if (((std::shared_ptr<general_joint>) joints[joint_id - 1])->get_y() > max_y)
			{
				max_y = ((std::shared_ptr<general_joint>) joints[joint_id - 1])->get_y();
			}
			if (((std::shared_ptr<general_joint>) joints[joint_id - 1])->get_z() > max_z)
			{
				max_z = ((std::shared_ptr<general_joint>) joints[joint_id - 1])->get_z();
			}
		}

		//move to center

		//Print points for data
		for (int joint_id = MAEJ_INVALID + 1; joint_id != MAEJ_SIZE; joint_id++)
		{
			sstr << ((std::shared_ptr<general_joint>) joints[joint_id - 1])->get_x() / max_x << " "
					<< ((std::shared_ptr<general_joint>) joints[joint_id - 1])->get_y() / max_y << " "
					<< ((std::shared_ptr<general_joint>) joints[joint_id - 1])->get_z() / max_z << " " << std::endl; //"\n";
		}

		//TODO do this according to the hiearchy

		//Print edges for data
		sstr << MAEJ_LEFT_HAND - 1 << " " << MAEJ_LEFT_ELBOW - 1 << std::endl;
		sstr << MAEJ_LEFT_ELBOW - 1 << " " << MAEJ_LEFT_SHOULDER - 1 << std::endl;
		sstr << MAEJ_LEFT_SHOULDER - 1 << " " << MAEJ_NECK - 1 << std::endl;
		sstr << MAEJ_NECK - 1 << " " << MAEJ_RIGHT_SHOULDER - 1 << std::endl;
		sstr << MAEJ_RIGHT_SHOULDER - 1 << " " << MAEJ_RIGHT_ELBOW - 1 << std::endl;
		sstr << MAEJ_RIGHT_ELBOW - 1 << " " << MAEJ_RIGHT_HAND - 1 << std::endl;
		sstr << MAEJ_NECK - 1 << " " << MAEJ_HEAD - 1 << std::endl;
		sstr << MAEJ_RIGHT_SHOULDER - 1 << " " << MAEJ_TORSO - 1 << std::endl;
		sstr << MAEJ_LEFT_SHOULDER - 1 << " " << MAEJ_TORSO - 1 << std::endl;
		sstr << MAEJ_TORSO - 1 << " " << MAEJ_LEFT_HIP - 1 << std::endl;
		sstr << MAEJ_TORSO - 1 << " " << MAEJ_RIGHT_HIP - 1 << std::endl;
		sstr << MAEJ_LEFT_HIP - 1 << " " << MAEJ_LEFT_KNEE - 1 << std::endl;
		sstr << MAEJ_LEFT_KNEE - 1 << " " << MAEJ_LEFT_FOOT - 1 << std::endl;
		sstr << MAEJ_RIGHT_HIP - 1 << " " << MAEJ_RIGHT_KNEE - 1 << std::endl;
		sstr << MAEJ_RIGHT_KNEE - 1 << " " << MAEJ_RIGHT_FOOT - 1 << std::endl;

		return sstr.str();
	}

	void general_skeleton::ply_file(std::string filename) const
	{
		std::ofstream out_file(filename);
		out_file << ply_str();
		out_file.close();
	}

} // namespace mae
