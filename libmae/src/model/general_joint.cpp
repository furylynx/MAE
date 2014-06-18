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
		this->valid = false;
	}

	general_joint::general_joint()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;

		this->valid = false;
	}

	general_joint::general_joint(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;

		this->valid = true;
	}

	void general_joint::set_x(double x)
	{
		this->x = x;
	}

	double general_joint::get_x() const
	{
		return x;
	}

	void general_joint::set_y(double y)
	{
		this->y = y;
	}

	double general_joint::get_y() const
	{
		return y;
	}

	void general_joint::set_z(double z)
	{
		this->z = z;
	}

	double general_joint::get_z() const
	{
		return z;
	}

	void general_joint::set_valid(bool isValid)
	{
		this->valid = isValid;
	}

	bool general_joint::is_valid() const
	{
		return valid;
	}

	bool general_joint::equals(general_joint joint) const
	{
		return x == joint.get_x() && y == joint.get_y() && z == joint.get_z() && valid == joint.is_valid();
	}

	bool general_joint::equals(std::shared_ptr<general_joint> joint) const
	{
		return equals(*joint);
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
