/*
 * basis.cpp
 *
 *  Created on: 01.10.2014
 *      Author: keks
 */

#include "basis.hpp"

namespace mae
{

	basis::basis(std::shared_ptr<vec3d> position_vector, std::shared_ptr<vec3d> u, std::shared_ptr<vec3d> r,
			std::shared_ptr<vec3d> t)
	{
		position_vector_ = position_vector;
		u_ = u;
		r_ = r;
		t_ = t;
	}

	basis::~basis()
	{
	}

	std::shared_ptr<vec3d> basis::get_u()
	{
		return u_;
	}

	std::shared_ptr<vec3d> basis::get_r()
	{
		return r_;
	}

	std::shared_ptr<vec3d> basis::get_t()
	{
		return t_;
	}

	std::shared_ptr<vec3d> basis::get_position_vector()
	{
		return position_vector_;
	}

	void basis::set_u(std::shared_ptr<vec3d> u)
	{
		u_ = u;
	}

	void basis::set_r(std::shared_ptr<vec3d> r)
	{
		r_ = r;
	}

	void basis::set_t(std::shared_ptr<vec3d> t)
	{
		t_ = t;
	}

	void basis::set_position_vector(std::shared_ptr<vec3d> position_vector)
	{
		position_vector_ = position_vector;
	}

} // namespace mae
