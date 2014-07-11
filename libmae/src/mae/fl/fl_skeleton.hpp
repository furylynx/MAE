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
#include "../general_skeleton.hpp"
#include "../bone.hpp"

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
				 * Sets the original general skeleton.
				 *
				 * @param offset_skeleton A shared pointer to the general skeleton.
				 */
				virtual void set_orig_skeleton(std::shared_ptr<general_skeleton> offset_skeleton);

				/**
				 * Returns the original general skeleton.
				 *
				 * @return A shared pointer to the general skeleton.
				 */
				virtual std::shared_ptr<general_skeleton> get_orig_skeleton() const;

				/**
				 * Returns a shared pointer to the used hierarchy. If not hierarchy is set, a default hierarchy is assumed.
				 * @return A shared pointer to the hierarchy.
				 */
				virtual std::shared_ptr<hierarchy> get_hierarchy() const;

				/**
				 * Sets the hierarchy
				 * @param hierarchy  A smart pointer to the hierarchy.
				 */
				virtual void set_hierarchy(std::shared_ptr<hierarchy> hierarchy);

				/**
				 * Sets the top-down direction of this skeleton by defining a bone. The bone must
				 * range from one torso joint to another and need not to follow the hierarchy (but
				 * the id's must be defined).
				 *
				 * @param top_down A shared pointer to the bone.
				 */
				virtual void set_top_down(std::shared_ptr<bone> top_down);

				/**
				 * Returns the top-down direction of this skeleton by giving a bone. The bone ranges
				 * from one torso joint to another.
				 *
				 * @param top_down A shared pointer to the bone.
				 */
				virtual std::shared_ptr<bone> get_top_down() const;

				/**
				 * Sets the right-left direction of this skeleton by defining a bone. The bone must
				 * range from one torso joint to another and need not to follow the hierarchy (but
				 * the id's must be defined).
				 *
				 * @param top_down A shared pointer to the bone.
				 */
				virtual void set_right_left(std::shared_ptr<bone> right_left);

				/**
				 * Returns the right-left direction of this skeleton by giving a bone. The bone ranges
				 * from one torso joint to another.
				 *
				 * @param top_down A shared pointer to the bone.
				 */
				virtual std::shared_ptr<bone> get_right_left() const;

				/**
				 * Converts this object to a string.
				 *
				 * @return This object as a string.
				 */
				virtual std::string str() const;

				/**
				 * Prints this object tot the stream.
				 *
				 * @param os
				 * @param obj
				 * @return
				 */
				friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<fl_skeleton>& obj)
				{
					os << obj->str();

					return os;
				}

			private:
				std::unordered_map<int, std::shared_ptr<fl_joint> > hashmap_joints;
				std::shared_ptr<general_skeleton> offset_skeleton;
				std::shared_ptr<general_skeleton> orig_skeleton_;

				std::shared_ptr<hierarchy> hierarchy_;

				std::shared_ptr<bone> top_down;
				std::shared_ptr<bone> right_left;

				//central coordinate system
				std::vector<double> u;
				std::vector<double> r;
				std::vector<double> t;
		};

	} // namespace fl
} // namespace mae

#endif // FLSKELETON_HPP_
