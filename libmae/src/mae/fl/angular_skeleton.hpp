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
				 * Sets the torso basis.
				 *
				 * The directions are:
				 * u The top-down or weight direction.
				 * r The right-left direction.
				 * t The direction standing on u and r (pointing from torso to the front).
				 *
				 * @param torso_basis The torso basis.
				 */
				virtual void set_torso_basis(std::shared_ptr<mae::math::basis> torso_basis);

				/**
				 * Returns the torso basis.
				 *
				 * The directions are:
				 * u The top-down or weight direction.
				 * r The right-left direction.
				 * t The direction standing on u and r (pointing from torso to the front).
				 *
				 * @return The torso basis.
				 */
				virtual std::shared_ptr<mae::math::basis> get_torso_basis() const;


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
				 * Sets the weight vector for this skeleton.
				 *
				 * @param weight The weight vector.
				 */
				virtual void set_weight(std::shared_ptr<mae::math::vec3d> weight);

				/**
				 * Returns the weight vector for this skeleton. If none is set, a null pointer will be returned.
				 *
				 * @return The weight or null.
				 */
				virtual std::shared_ptr<mae::math::vec3d> get_weight() const;

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

				std::shared_ptr<mae::math::vec3d> weight_;

				//central coordinate system
				std::shared_ptr<mae::math::basis> torso_basis_;
		};

	} // namespace fl
} // namespace mae

#endif // ANGULAR_SKELETON_HPP_
