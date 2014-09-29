/*
 * angular_skeleton.hpp
 *
 *  Created on: 29.09.2014
 *      Author: keks
 */

#ifndef ANGULAR_SKELETON_HPP_
#define ANGULAR_SKELETON_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "angular_joint.hpp"
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

		class angular_skeleton
		{
			public:
				/**
				 * Creates a new angular skeleton with the joints represented by two angles THETA and PHI.
				 */
				angular_skeleton();
				virtual ~angular_skeleton();

				/**
				 * Sets an angular joint.
				 *
				 * @param body_part The addresses body part.
				 * @param joint A shared pointer to the joint.
				 */
				virtual void set_joint(int body_part, std::shared_ptr<angular_joint> joint);

				/**
				 * Returns an angular joint.
				 *
				 * @param body_part The addressed body part.
				 * @return A shared pointer to the joint.
				 */
				virtual std::shared_ptr<angular_joint> get_joint(int body_part) const;

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
				 * Sets the torso basis. All three vectors must be 3d giving values by [x,y,z].
				 *
				 * @param u The top-down or weight direction.
				 * @param r The right-left direction.
				 * @param t The direction standing on u and r (pointing from torso to the front).
				 */
				virtual void set_coord_sys(std::shared_ptr<vec3d> u, std::shared_ptr<vec3d> r, std::shared_ptr<vec3d> t);

				/**
				 * Returns the torso basis consisting of three vectors. The vector containing the
				 * basis contains the three vectors in the [u,r,t] form. Each vector is a 3d vector.
				 * Typically u is the top-down or weight direction, r is the right-left direction
				 * and t points from the torso to the front.
				 *
				 * @return The torso basis.
				 */
				virtual std::vector<std::shared_ptr<vec3d> > get_coord_sys() const;


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
				friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<angular_skeleton>& obj)
				{
					os << obj->str();

					return os;
				}

			private:
				std::unordered_map<int, std::shared_ptr<angular_joint> > hashmap_joints;

				std::shared_ptr<hierarchy> hierarchy_;

				std::shared_ptr<bone> top_down;
				std::shared_ptr<bone> right_left;

				//central coordinate system
				std::shared_ptr<vec3d> u_;
				std::shared_ptr<vec3d> r_;
				std::shared_ptr<vec3d> t_;
		};

	} // namespace fl
} // namespace mae

#endif // ANGULAR_SKELETON_HPP_
