/*
 * FLSkeleton.hpp
 *
 *  Created on: 20.05.2014
 *      Author: keks
 */

#ifndef FLSKELETON_HPP_
#define FLSKELETON_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "FLJoint.hpp"
#include "FLJ.hpp"
#include "../model/GeneralSkeleton.hpp"

//global includes
#include <unordered_map>
#include <vector>
#include <stdexcept>

namespace mae
{
	namespace fl
	{

		class FLSkeleton
		{
			public:
				FLSkeleton();
				virtual ~FLSkeleton();

				//todo joints are angular - but central coordinate system necessary?

				//angular joint
				virtual void setJoint(int bodyPart, std::shared_ptr<mae::fl::FLJoint> joint);
				virtual std::shared_ptr<mae::fl::FLJoint> getJoint(int bodyPart);

				//get central coordinate system
				virtual void setCoordSys(std::vector<double> u, std::vector<double> r, std::vector<double> t);
				virtual std::vector<std::vector<double> > getCoordSys();

				//todo get vectors by themselves

				// Torso joint is center of coordinate system; therefore torso joint has coordinates (0,0,0).
				// Stored torso joint is therefore used for the offset of the world coordinate system given
				// by the depth sensor. The central coordinate system of this FLSkeleton is used for the
				// representation by translating it into the torso joint.

				virtual void set_offset_skeleton(std::shared_ptr<mae::model::GeneralSkeleton> offset_skeleton);

				virtual std::shared_ptr<mae::model::GeneralSkeleton> get_offset_skeleton();

				friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<FLSkeleton>& obj)
				{
					os << "FLSkeleton:" << std::endl;
					for ( int joint_id = FLJ_INVALID+1; joint_id != FLJ_SIZE; joint_id++ )
					{
					   os << flj_str[joint_id] << " " << obj->getJoint(joint_id) << std::endl;
					}

					return os;
				}

			private:
				std::unordered_map<int, std::shared_ptr<mae::fl::FLJoint> > hashmap_joints;
				std::shared_ptr<mae::model::GeneralSkeleton> offset_skeleton;

				//central coordinate system
				std::vector<double> u;
				std::vector<double> r;
				std::vector<double> t;
		};

	} // namespace fl
} // namespace mae

#endif // FLSKELETON_HPP_
