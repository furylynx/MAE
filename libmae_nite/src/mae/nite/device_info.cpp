/*
 * device_info.cpp
 *
 *  Created on: 30.09.2014
 *      Author: keks
 */

#include "device_info.hpp"

namespace mae
{
	namespace nite
	{

		device_info::device_info(std::string device_name, std::string device_serial)
		{
			device_name_ = device_name;
			device_serial_ = device_serial;
		}

		device_info::~device_info()
		{
		}

		std::string device_info::get_device_name()
		{
			return device_name_;
		}

		std::string device_info::get_device_serial()
		{
			return device_serial_;
		}

	} // namespace nite
} // namespace mae
