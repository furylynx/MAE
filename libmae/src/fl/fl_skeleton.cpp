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
				// returns an invalid joint which means that the joint is
				// not existing
				return std::shared_ptr<fl_joint>(new fl_joint());
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

	}// namespace fl
} // namespace mae
