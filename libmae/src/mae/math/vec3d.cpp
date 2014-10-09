/*
 * vec3d.cpp
 *
 *  Created on: 29.09.2014
 *      Author: keks
 */

#include "vec3d.hpp"

namespace mae
{
	namespace math
	{

		vec3d::vec3d()
		{
			x_ = 0;
			y_ = 0;
			z_ = 0;
		}

		vec3d::vec3d(double x, double y, double z)
		{
			x_ = x;
			y_ = y;
			z_ = z;
		}

		vec3d::~vec3d()
		{
			// TODO Auto-generated destructor stub
		}

		void vec3d::set_x(double x)
		{
			x_ = x;
		}

		double vec3d::get_x() const
		{
			return x_;
		}

		void vec3d::set_y(double y)
		{
			y_ = y;
		}

		double vec3d::get_y() const
		{
			return y_;
		}

		void vec3d::set_z(double z)
		{
			z_ = z;
		}

		double vec3d::get_z() const
		{
			return z_;
		}

		std::string vec3d::str() const
		{
			std::stringstream sstr;

			sstr << "(" << x_ << ", " << y_ << ", " << z_ << ")";

			return sstr.str();
		}
	} // namespace math
} // namespace mae
