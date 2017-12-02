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

		std::shared_ptr<vec3d> vec3d::add(std::shared_ptr<vec3d> vec) const
		{
			return std::make_shared<vec3d>(x_ + vec->get_x(), y_ + vec->get_y(), z_ + vec->get_z());
		}

		std::shared_ptr<vec3d> vec3d::subtract(std::shared_ptr<vec3d> vec) const
		{
			return std::make_shared<vec3d>(x_ - vec->get_x(), y_ - vec->get_y(), z_ - vec->get_z());
		}

		std::shared_ptr<vec3d> vec3d::multiply(double scalar) const
		{
			return std::make_shared<vec3d>(x_ * scalar, y_ * scalar, z_ * scalar);
		}

		std::shared_ptr<vec3d> vec3d::normalize() const
		{
			double norm = l2_norm();

			if (norm == 0)
			{
				return std::make_shared<vec3d>(0,0,0);
			}
			else
			{
				return std::make_shared<vec3d>(x_/norm, y_/norm, z_/norm);
			}
		}

		double vec3d::l2_norm() const
		{
			return std::sqrt(std::pow(x_, 2) + std::pow(y_, 2) + std::pow(z_, 2));
		}

		double vec3d::dot(std::shared_ptr<vec3d> vec) const
		{
			return (x_ * vec->get_x()) + (y_ * vec->get_y()) + (z_ * vec->get_z());
		}

		std::shared_ptr<vec3d> vec3d::cross(std::shared_ptr<vec3d> vec) const
		{
			return std::make_shared<vec3d>((y_*vec->get_z()) - (z_*vec->get_y()), (z_*vec->get_x()) - (x_*vec->get_z()), (x_*vec->get_y()) - (y_*vec->get_x()));
		}

		std::string vec3d::str() const
		{
			std::stringstream sstr;

			sstr << "(" << x_ << ", " << y_ << ", " << z_ << ")";

			return sstr.str();
		}
	} // namespace math
} // namespace mae
