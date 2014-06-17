/*
 * GeneralSkeleton.cpp
 *
 * Created on: 15.05.2014
 * Author: keks
 */

#include "GeneralSkeleton.hpp"

namespace mae
{
	namespace model
	{

		GeneralSkeleton::GeneralSkeleton()
		{
			this->hashmap_joints = std::unordered_map<int, std::shared_ptr<mae::model::GeneralJoint> >();

			this->hierarchy = Hierarchy::default_hierarchy();
		}

		GeneralSkeleton::GeneralSkeleton(std::shared_ptr<Hierarchy> hierarchy)
		{
			this->hierarchy = hierarchy;
			this->hashmap_joints = std::unordered_map<int, std::shared_ptr<mae::model::GeneralJoint> >();
		}

		GeneralSkeleton::~GeneralSkeleton()
		{
			this->hashmap_joints.clear();
		}

		void GeneralSkeleton::set_joint(int bodyPart, std::shared_ptr<mae::model::GeneralJoint> joint)
		{

			if (hashmap_joints.find(bodyPart) == hashmap_joints.end())
			{
				//key is not in map
				hashmap_joints.insert(std::make_pair(bodyPart, joint));

			}
			else
			{
				//key already exists and will therefore be overwritten
				hashmap_joints[bodyPart] = joint;
			}
		}

		std::shared_ptr<mae::model::GeneralJoint> GeneralSkeleton::get_joint(int bodyPart) const
		{

			if (hashmap_joints.find(bodyPart) == hashmap_joints.end())
			{
				// returns an invalid joint which means that the joint is
				// not existing
				return std::shared_ptr<mae::model::GeneralJoint>(new mae::model::GeneralJoint());
			}
			else
			{
				// returns the joint
				return hashmap_joints.at(bodyPart);
			}

		}

		std::shared_ptr<Hierarchy> GeneralSkeleton::get_hierarchy() const
		{
			return hierarchy;
		}

		void GeneralSkeleton::set_hierarchy(std::shared_ptr<Hierarchy> hierarchy)
		{
			this->hierarchy = hierarchy;
		}

		std::string GeneralSkeleton::ply_str() const
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

			std::vector<std::shared_ptr<GeneralJoint> > joints;
			for (int joint_id = MAEJ_INVALID + 1; joint_id != MAEJ_SIZE; joint_id++)
			{
				joints.push_back(
						std::shared_ptr<GeneralJoint>(
								new GeneralJoint(get_joint(joint_id)->getX() - get_joint(MAEJ_TORSO)->getX(),
										get_joint(joint_id)->getY() - get_joint(MAEJ_TORSO)->getY(),
										get_joint(joint_id)->getZ() - get_joint(MAEJ_TORSO)->getZ())));

				if (((std::shared_ptr<GeneralJoint>) joints[joint_id - 1])->getX() > max_x)
				{
					max_x = ((std::shared_ptr<GeneralJoint>) joints[joint_id - 1])->getX();
				}
				if (((std::shared_ptr<GeneralJoint>) joints[joint_id - 1])->getY() > max_y)
				{
					max_y = ((std::shared_ptr<GeneralJoint>) joints[joint_id - 1])->getY();
				}
				if (((std::shared_ptr<GeneralJoint>) joints[joint_id - 1])->getZ() > max_z)
				{
					max_z = ((std::shared_ptr<GeneralJoint>) joints[joint_id - 1])->getZ();
				}
			}

			//move to center

			//Print points for data
			for (int joint_id = MAEJ_INVALID + 1; joint_id != MAEJ_SIZE; joint_id++)
			{
				sstr << ((std::shared_ptr<GeneralJoint>) joints[joint_id - 1])->getX() / max_x << " "
						<< ((std::shared_ptr<GeneralJoint>) joints[joint_id - 1])->getY() / max_y << " "
						<< ((std::shared_ptr<GeneralJoint>) joints[joint_id - 1])->getZ() / max_z << " " << std::endl; //"\n";
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

		void GeneralSkeleton::ply_file(std::string filename) const
		{
			std::ofstream out_file(filename);
			out_file << ply_str();
			out_file.close();
		}

		std::string GeneralSkeleton::str() const
		{
			std::stringstream sstr;
			sstr << "GeneralSkeleton:" << std::endl;
			for (int joint_id = MAEJ_INVALID + 1; joint_id != MAEJ_SIZE; joint_id++)
			{
				sstr << maej_str[joint_id] << " " << get_joint(joint_id) << std::endl;
			}

			return sstr.str();
		}

	} // namespace model
} // namespace mae
