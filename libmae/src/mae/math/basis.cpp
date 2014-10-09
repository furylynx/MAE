/*
 * basis.cpp
 *
 *  Created on: 01.10.2014
 *      Author: keks
 */

#include "basis.hpp"

namespace mae
{
	namespace math
	{

		basis::basis()
		{
			position_vector_ = nullptr;
			u_ = nullptr;
			r_ = nullptr;
			t_ = nullptr;
		}

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

		std::shared_ptr<vec3d> basis::get_u() const
		{
			return u_;
		}

		std::shared_ptr<vec3d> basis::get_r() const
		{
			return r_;
		}

		std::shared_ptr<vec3d> basis::get_t() const
		{
			return t_;
		}

		std::shared_ptr<vec3d> basis::get_position_vector() const
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

		std::string basis::str() const
		{
			std::stringstream sstr;

			sstr << "[" << u_->str() << "; " << r_->str() << "; " << t_->str() << "] - position vector "
					<< position_vector_->str();

			return sstr.str();
		}

	} // namespace math
} // namespace mae
