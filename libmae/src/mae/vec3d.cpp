/*
 * vec3d.cpp
 *
 *  Created on: 29.09.2014
 *      Author: keks
 */

#include "vec3d.hpp"

namespace mae
{

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

	double vec3d::get_x()
	{
		return x_;
	}

	void vec3d::set_y(double y)
	{
		y_ = y;
	}

	double vec3d::get_y()
	{
		return y_;
	}

	void vec3d::set_z(double z)
	{
		z_ = z;
	}

	double vec3d::get_z()
	{
		return z_;
	}

} // namespace mae
