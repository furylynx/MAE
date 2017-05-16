#ifndef MAE_MATH_VEC3D_HPP_
#define MAE_MATH_VEC3D_HPP_

//custom includes
//...

//global includes
#include <memory>
#include <string>
#include <sstream>
#include <cmath>

namespace mae
{
	namespace math
	{

		class vec3d
		{
			public:
				/**
				 * Creates a new three dimensional vector with zeros as default values.
				 */
				vec3d();

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
				 * Adds the given vector's value to this vector's values and returns the result.
				 *
				 * This vector is not changed.
				 *
				 * @param vec The vector to be added.
				 * @return The resulting vector.
				 */
				virtual std::shared_ptr<vec3d> add(std::shared_ptr<vec3d> vec) const;

				/**
				 * Subtracts the given vector's value from this vector's values and returns the result.
				 *
				 * This vector is not changed.
				 *
				 * @param vec The vector to be added.
				 * @return The resulting vector.
				 */
				virtual std::shared_ptr<vec3d> subtract(std::shared_ptr<vec3d> vec) const;


				/**
				 * Returns the the normalized vector.
				 *
				 * This vector is not changed.
				 *
				 * @param vec The vector to be added.
				 * @return The resulting vector.
				 */
				virtual std::shared_ptr<vec3d> normalize() const;

				/**
				 * Returns the value of the L2 norm for this vector.
				 *
				 * @return The norm value.
				 */
				virtual double l2_norm() const;


				/**
				 * Returns the result of the dot product between the two vectors.
				 *
				 * @param vec The vector.
				 * @return The dot product.
				 */
				virtual double dot(std::shared_ptr<vec3d> vec) const;

				/**
				 * Returns the result of the cross product between the two vectors.
				 *
				 * @param vec The vector.
				 * @return The cross product.
				 */
				virtual std::shared_ptr<vec3d> cross(std::shared_ptr<vec3d> vec) const;


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

	} // namespace math
} // namespace mae

#endif // MAE_MATH_VEC3D_HPP_
