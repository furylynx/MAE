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
#include <memory>
#include <string>
#include <sstream>

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
			virtual double get_x() const;

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
			virtual double get_y() const;

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
			virtual double get_z() const;

			/**
			 * Returns the string representation for this object.
			 *
			 * @return The string.
			 */
			virtual std::string str() const;

			/**
			 * Prints the object to the stream.
			 *
			 * @param os
			 * @param obj The object to be printed.
			 * @return
			 */
			friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<vec3d>& obj)
			{
				os << obj->str();

				return os;
			}

			/**
			 * Prints the object to the stream.
			 *
			 * @param os
			 * @param obj The object to be printed.
			 * @return
			 */
			friend std::ostream& operator<<(std::ostream& os, const vec3d& obj)
			{
				os << obj.str();

				return os;
			}

		private:
			double x_;
			double y_;
			double z_;
	};

} // namespace mae

#endif // VEC3D_HPP_
