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

		GeneralSkeleton::~GeneralSkeleton()
		{
			hashmap_joints.clear();
		}

		GeneralSkeleton::GeneralSkeleton()
		{
			hashmap_joints = std::unordered_map<int, std::shared_ptr<mae::model::GeneralJoint> >();
		}

		void GeneralSkeleton::setJoint(int bodyPart, std::shared_ptr<mae::model::GeneralJoint> joint)
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

		std::shared_ptr<mae::model::GeneralJoint> GeneralSkeleton::getJoint(int bodyPart)
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
				return hashmap_joints[bodyPart];
			}

		}

		std::string GeneralSkeleton::to_ply_str()
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
								new GeneralJoint(getJoint(joint_id)->getX() - getJoint(MAEJ_TORSO)->getX(),
										getJoint(joint_id)->getY() - getJoint(MAEJ_TORSO)->getY(),
										getJoint(joint_id)->getZ() - getJoint(MAEJ_TORSO)->getZ())));

				if (((std::shared_ptr<GeneralJoint>)joints[joint_id - 1])->getX() > max_x)
				{
					max_x = ((std::shared_ptr<GeneralJoint>)joints[joint_id - 1])->getX();
				}
				if (((std::shared_ptr<GeneralJoint>)joints[joint_id - 1])->getY() > max_y)
				{
					max_y = ((std::shared_ptr<GeneralJoint>)joints[joint_id - 1])->getY();
				}
				if (((std::shared_ptr<GeneralJoint>)joints[joint_id - 1])->getZ() > max_z)
				{
					max_z = ((std::shared_ptr<GeneralJoint>)joints[joint_id - 1])->getZ();
				}
			}

			//move to center

			//Print points for data
			for (int joint_id = MAEJ_INVALID + 1; joint_id != MAEJ_SIZE; joint_id++)
			{
				sstr << ((std::shared_ptr<GeneralJoint>)joints[joint_id - 1])->getX() / max_x << " " << ((std::shared_ptr<GeneralJoint>)joints[joint_id - 1])->getY() / max_y << " "
						<< ((std::shared_ptr<GeneralJoint>)joints[joint_id - 1])->getZ() / max_z << " " << std::endl; //"\n";
			}

			//Print edges for data
			sstr << MAEJ_LEFT_HAND-1 << " " <<  MAEJ_LEFT_ELBOW-1 << std::endl;
			sstr << MAEJ_LEFT_ELBOW-1 << " " <<  MAEJ_LEFT_SHOULDER-1 << std::endl;
			sstr << MAEJ_LEFT_SHOULDER-1 << " " <<  MAEJ_NECK-1 << std::endl;
			sstr << MAEJ_NECK-1 << " " <<  MAEJ_RIGHT_SHOULDER-1 << std::endl;
			sstr << MAEJ_RIGHT_SHOULDER-1 << " " <<  MAEJ_RIGHT_ELBOW-1 << std::endl;
			sstr << MAEJ_RIGHT_ELBOW-1 << " " <<  MAEJ_RIGHT_HAND-1 << std::endl;
			sstr << MAEJ_NECK-1 << " " <<  MAEJ_HEAD-1 << std::endl;
			sstr << MAEJ_RIGHT_SHOULDER-1 << " " <<  MAEJ_TORSO-1 << std::endl;
			sstr << MAEJ_LEFT_SHOULDER-1 << " " <<  MAEJ_TORSO-1 << std::endl;
			sstr << MAEJ_TORSO-1 << " " <<  MAEJ_LEFT_HIP-1 << std::endl;
			sstr << MAEJ_TORSO-1 << " " <<  MAEJ_RIGHT_HIP-1 << std::endl;
			sstr << MAEJ_LEFT_HIP-1 << " " <<  MAEJ_LEFT_KNEE-1 << std::endl;
			sstr << MAEJ_LEFT_KNEE-1 << " " <<  MAEJ_LEFT_FOOT-1 << std::endl;
			sstr << MAEJ_RIGHT_HIP-1 << " " <<  MAEJ_RIGHT_KNEE-1 << std::endl;
			sstr << MAEJ_RIGHT_KNEE-1 << " " <<  MAEJ_RIGHT_FOOT-1 << std::endl;

			return sstr.str();
		}

	} // namespace model
} // namespace mae
