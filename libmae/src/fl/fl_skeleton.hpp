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
#include "fl_joint.hpp"
#include "flj.hpp"
#include "../model/general_skeleton.hpp"

//global includes
#include <unordered_map>
#include <vector>
#include <stdexcept>

namespace mae
{
	namespace fl
	{

		class fl_skeleton
		{
			public:
				fl_skeleton();
				virtual ~fl_skeleton();

				//angular joint - not used currently
				/**
				 * Sets an angular joint.
				 *
				 * @param body_part The addresses body part.
				 * @param joint A shared pointer to the joint.
				 */
				virtual void set_joint(int body_part, std::shared_ptr<fl_joint> joint);

				/**
				 * Returns an angular joint.
				 *
				 * @param body_part The addressed body part.
				 * @return A shared pointer to the joint.
				 */
				virtual std::shared_ptr<fl_joint> get_joint(int body_part) const;

				/**
				 * Sets the torso basis. All three vectors must be 3d giving values by [x,y,z].
				 *
				 * @param u The top-down direction.
				 * @param r The right-left direction.
				 * @param t The direction standing on u and r.
				 */
				virtual void set_coord_sys(std::vector<double> u, std::vector<double> r, std::vector<double> t);

				/**
				 * Returns the torso basis consisting of three vectors. The vector containing the
				 * basis contains the three vectors in the [u,r,t] form. Each vector is a 3d vector
				 * containing information [x,y,z] beginning at index 0.
				 *
				 * @return The torso basis.
				 */
				virtual std::vector<std::vector<double> > get_coord_sys() const;

				/**
				 * Sets the offset skeleton. The root joint is used to define the offset of the
				 * whole skeleton in x,y,z world coordinates. All other joints are given by offset
				 * to their parent in the u,r,t object coordinates.
				 *
				 * @param offset_skeleton A shared pointer to the offset skeleton.
				 */
				virtual void set_offset_skeleton(std::shared_ptr<general_skeleton> offset_skeleton);

				/**
				 * Returns the offset skeleton. The root joint is used to define the offset of the
				 * whole skeleton in x,y,z world coordinates. All other joints are given by offset
				 * to their parent in the u,r,t object coordinates.
				 *
				 * @return A shared pointer to the offset skeleton.
				 */
				virtual std::shared_ptr<general_skeleton> get_offset_skeleton() const;

				/**
				 * Prints this object tot the stream.
				 *
				 * @param os
				 * @param obj
				 * @return
				 */
				friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<fl_skeleton>& obj)
				{
					os << "FLSkeleton:" << std::endl;
					for (int joint_id = FLJ_INVALID + 1; joint_id != FLJ_SIZE; joint_id++)
					{
						os << flj_str[joint_id] << " " << obj->get_joint(joint_id) << std::endl;
					}

					return os;
				}

			private:
				std::unordered_map<int, std::shared_ptr<fl_joint> > hashmap_joints;
				std::shared_ptr<general_skeleton> offset_skeleton;

				//central coordinate system
				std::vector<double> u;
				std::vector<double> r;
				std::vector<double> t;
		};

	} // namespace fl
} // namespace mae

#endif // FLSKELETON_HPP_
