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

		device_info::device_info(std::string device_name, std::string device_serial, std::string vendor_name, std::string creation_info)
		{
			device_name_ = device_name;
			device_serial_ = device_serial;
			vendor_name_ = vendor_name;
			creation_info_ = creation_info;
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

		std::string device_info::get_vendor_name()
		{
			return vendor_name_;
		}

		std::string device_info::get_creation_info()
		{
			return creation_info_;
		}

	} // namespace nite
} // namespace mae
