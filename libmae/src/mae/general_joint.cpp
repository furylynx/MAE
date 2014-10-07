/*
 * GeneralJoint.cpp
 *
 *  Created on: 20.05.2014
 *      Author: keks
 */

#include "general_joint.hpp"

namespace mae
{

	general_joint::~general_joint()
	{
		this->valid_ = false;
	}

	general_joint::general_joint()
	{
		x_ = 0;
		y_ = 0;
		z_ = 0;

		rotation_ = 0;
		confidence_ = 0;
		valid_ = false;
	}

	general_joint::general_joint(double x, double y, double z, double rotation ,double confidence)
	{
		x_ = x;
		y_ = y;
		z_ = z;

		rotation_ = rotation;
		confidence_ = confidence;
		valid_ = true;
	}

	general_joint::general_joint(std::shared_ptr<vec3d> pos, double rotation, double confidence) : general_joint(pos->get_x(), pos->get_y(), pos->get_z(), rotation, confidence)
	{

	}

	void general_joint::set_x(double x)
	{
		this->x_ = x;
	}

	double general_joint::get_x() const
	{
		return x_;
	}

	void general_joint::set_y(double y)
	{
		this->y_ = y;
	}

	double general_joint::get_y() const
	{
		return y_;
	}

	void general_joint::set_z(double z)
	{
		this->z_ = z;
	}

	double general_joint::get_z() const
	{
		return z_;
	}

	void general_joint::set_valid(bool isValid)
	{
		this->valid_ = isValid;
	}

	bool general_joint::is_valid() const
	{
		return valid_;
	}

	void general_joint::set_confidence(double confidence)
	{
		confidence_ = confidence;
	}

	double general_joint::get_confidence()
	{
		return confidence_;
	}

	void general_joint::set_rotation(double rotation)
	{
		rotation_ = rotation;
	}

	double general_joint::get_rotation()
	{
		return rotation_;
	}

	std::shared_ptr<vec3d> general_joint::vec()
	{
		return std::shared_ptr<vec3d>(new vec3d(x_, y_, z_));
	}

	bool general_joint::equals_val(general_joint joint) const
	{
		return x_ == joint.get_x() && y_ == joint.get_y() && z_ == joint.get_z() && valid_ == joint.is_valid() && confidence_ == joint.get_confidence();
	}

	bool general_joint::equals(std::shared_ptr<general_joint> joint) const
	{
		return equals_val(*joint);
	}

	std::string general_joint::str() const
	{
		std::stringstream sstr;
		if (!is_valid())
		{
			sstr << "(invalid joint)";
		}
		else
		{
			sstr << "(" << get_x() << ", " << get_y() << ", " << get_z() << ")";
		}

		return sstr.str();
	}

} // namespace mae
