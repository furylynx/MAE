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
#include "../vec3d.hpp"

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
				 * Sets the torso basis. All three vectors must be 3d giving values by [x,y,z].
				 *
				 * @param u The top-down or weight direction.
				 * @param r The right-left direction.
				 * @param t The direction standing on u and r (pointing from torso to the front).
				 */
				virtual void set_coord_sys(std::shared_ptr<vec3d> u, std::shared_ptr<mae::vec3d> r, std::shared_ptr<vec3d> t);

				/**
				 * Returns the torso basis consisting of three vectors. The vector containing the
				 * basis contains the three vectors in the [u,r,t] form. Each vector is a 3d vector.
				 * Typically u is the top-down or weight direction, r is the right-left direction
				 * and t points from the torso to the front.
				 *
				 * @return The torso basis.
				 */
				virtual std::vector<std::shared_ptr<mae::vec3d> > get_coord_sys() const;

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
				std::shared_ptr<mae::vec3d> u_;
				std::shared_ptr<mae::vec3d> r_;
				std::shared_ptr<mae::vec3d> t_;

		};

	} // namespace fl
} // namespace mae

#endif // FLSKELETON_HPP_
