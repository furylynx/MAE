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
#include "../general_skeleton.hpp"
#include "../bone.hpp"
#include "../math/vec3d.hpp"

//global includes
#include <unordered_map>
#include <vector>
#include <stdexcept>


namespace mae
{
	namespace fl
	{

		class fl_skeleton : public general_skeleton
		{
			public:
				/**
				 * Generates a fl_skeleton which is the offset skeleton.
				 *
				 * The root joint is used to define the offset of the
				 * whole skeleton in x,y,z world coordinates. All other joints are given by offset
				 * to their parent in the u,r,t object coordinates.
				 */
				fl_skeleton();

				virtual ~fl_skeleton();


				/**
				 * Sets the basis as a system of reference (formerly the torso basis).
				 *
				 * The directions are:
				 * u The top-down or weight direction.
				 * r The right-left direction.
				 * t The direction standing on u and r (pointing to the front, e.g. from the torso).
				 *
				 * @param torso_basis The basis.
				 */
				//[[deprecated("Replaced by set_basis(...)")]]
				virtual void set_torso_basis(std::shared_ptr<mae::math::basis> basis);

				/**
				 * Sets the basis as a system of reference (e.g. the torso basis or the palm basis).
				 *
				 * The directions are:
				 * u The top-down or weight direction.
				 * r The right-left direction.
				 * t The direction standing on u and r (pointing from torso to the front).
				 *
				 * @param basis The basis as a system of reference (e.g. the torso basis or the palm basis).
				 */
				virtual void set_basis(std::shared_ptr<mae::math::basis> basis);

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
				//[[deprecated("Replaced by get_basis()")]]
				virtual std::shared_ptr<mae::math::basis> get_torso_basis() const;

				/**
				 * Returns the basis as a system of reference (e.g. the torso basis or the palm basis).
				 *
				 * The directions are:
				 * u The top-down or weight direction.
				 * r The right-left direction.
				 * t The direction standing on u and r (pointing to the front).
				 *
				 * @return The basis a system of reference (e.g. the torso basis or the palm basis).
				 */
				virtual std::shared_ptr<mae::math::basis> get_basis() const;

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

				std::shared_ptr<general_skeleton> orig_skeleton_;

				//central coordinate system
				std::shared_ptr<mae::math::basis> basis_;

		};

	} // namespace fl
} // namespace mae

#endif // FLSKELETON_HPP_
