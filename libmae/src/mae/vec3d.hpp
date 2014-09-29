/*
 * vec3d.hpp
 *
 *  Created on: 29.09.2014
 *      Author: keks
 */

#ifndef VEC3D_HPP_
#define VEC3D_HPP_

//eclipse indexer fix
#include "indexer_fix.hpp"

//custom includes
//...

//global includes
//...

namespace mae
{

	class vec3d
	{
		public:
			/**
			 * Creates a new three dimensional vector.
			 *
			 * @param x The x value.
			 * @param y The y value.
			 * @param z The z value.
			 */
			vec3d(double x, double y, double z);
			virtual ~vec3d();


			/**
			 * Sets the x value of this vector.
			 *
			 * @param x The x value.
			 */
			virtual void set_x(double x);

			/**
			 * Returns the x value of this vector.
			 *
			 * @return x
			 */
			virtual double get_x();

			/**
			 * Sets the y value of this vector.
			 *
			 * @param y The y value.
			 */
			virtual void set_y(double y);

			/**
			 * Returns the y value of this vector.
			 *
			 * @return y
			 */
			virtual double get_y();

			/**
			 * Sets the z value of this vector.
			 *
			 * @param z The z value.
			 */
			virtual void set_z(double z);

			/**
			 * Returns the z value of this vector.
			 *
			 * @return z
			 */
			virtual double get_z();

		private:
			double x_;
			double y_;
			double z_;
	};

} // namespace mae

#endif // VEC3D_HPP_
