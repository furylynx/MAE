/*
 * bone.cpp
 *
 *  Created on: 18.06.2014
 *      Author: keks
 */

#include "bone.hpp"

namespace mae
{

	bone::bone(int id, std::string name, int from, int to)
	{
		this->id = id;
		this->name = name;
		this->from = from;
		this->to = to;
	}

	bone::~bone()
	{
	}

	int bone::get_id() const
	{
		return id;
	}

	std::string bone::get_name() const
	{
		return name;
	}

	int bone::get_from() const
	{
		return from;
	}

	int bone::get_to() const
	{
		return to;
	}

} // namespace mae
