/*
 * FLMath.cpp
 *
 *  Created on: 28.05.2014
 *      Author: keks
 */

#include "math.hpp"

//internal includes
#include "internal_math.hh"

namespace mae
{
	namespace math
	{

		std::shared_ptr<vec3d> math::project_to_basis(std::shared_ptr<vec3d> point, std::shared_ptr<basis> basis, std::shared_ptr<vec3d> position_vector)
		{
			return mae::math::internal_math::project_to_basis_maevec(point, basis, position_vector);
		}

		std::shared_ptr<vec3d> math::project_back_to_default(std::shared_ptr<vec3d> point, std::shared_ptr<basis> basis, std::shared_ptr<vec3d> position_vector )
		{
			return internal_math::project_back_to_default_maevec(point, basis, position_vector);
		}

		bool math::are_collinear(std::shared_ptr<vec3d> a, std::shared_ptr<vec3d> b)
		{
			// assumption: angle between both is 0 or 180 degree
			double angle = math::calc_angle_half(a, b);

			//fix round-off errors
			return (angle > -0.01 && angle < 0.01) || (angle > (M_PI - 0.01) && angle < (M_PI + 0.01))
					|| (angle > (-M_PI - 0.01) && angle < (-M_PI + 0.01));
		}

		double math::calc_angle_plane(std::shared_ptr<vec3d> a, std::shared_ptr<vec3d> b, std::shared_ptr<vec3d> normal)
		{
			return internal_math::calc_angle_plane(internal_math::maevec_to_vec3d(a), internal_math::maevec_to_vec3d(b), internal_math::maevec_to_vec3d(normal));
		}

		double math::calc_angle_plane_deg(std::shared_ptr<vec3d> a, std::shared_ptr<vec3d> b, std::shared_ptr<vec3d> normal)
		{
			return math::rad_to_deg(math::calc_angle_plane(a, b, normal));
		}

		double math::calc_angle_half(std::shared_ptr<vec3d> a, std::shared_ptr<vec3d> b)
		{
			return internal_math::calc_angle_half(internal_math::maevec_to_vec3d(a), internal_math::maevec_to_vec3d(b));
		}

		double math::calc_angle_half_deg(std::shared_ptr<vec3d> a, std::shared_ptr<vec3d> b)
		{
			return math::rad_to_deg(math::calc_angle_half(a, b));
		}

		double math::rad_to_deg(double val)
		{
			return val * 180 / M_PI;
		}

		double math::deg_to_rad(double val)
		{
			return val * M_PI / 180;
		}

		double math::fmod_pos(double a, double b)
		{
			double tmp = std::fmod(a, b);

			if (tmp < 0)
			{
				tmp = b + tmp;
			}

			return tmp;
		}

		int math::sign(double x)
		{
			return (x > 0) - (x < 0);
		}

	} // namespace math
} // namespace mae
