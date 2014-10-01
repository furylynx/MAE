/*
 * device_info.hpp
 *
 *  Created on: 30.09.2014
 *      Author: keks
 */

#ifndef DEVICE_INFO_HPP_
#define DEVICE_INFO_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
//...

//global includes
#include <string>

namespace mae
{
	namespace nite
	{

		class device_info
		{
			public:
				/**
				 * Creates a new device info.
				 *
				 * @param device_name The device name.
				 * @param device_serial The device's serial number.
				 * @param vendor_name The vendor name.
				 * @param creation_info The creation info.
				 */
				device_info(std::string device_name, std::string device_serial, std::string vendor_name, std::string creation_info);
				virtual ~device_info();

				/**
				 * Returns the device name.
				 *
				 * @return The device name.
				 */
				virtual std::string get_device_name();

				/**
				 * Returns the device serial number.
				 *
				 * @return The serial number.
				 */
				virtual std::string get_device_serial();

				/**
				 * Returns the vendor name.
				 *
				 * @return The vendor name.
				 */
				virtual std::string get_vendor_name();

				/**
				 * The creation info is a string holding information on the creation of the device node.
				 *
				 * The info is split by slashes. The elements are 'idVendor/idProduct@BusID/DeviceId'.
				 *
				 * @return The creation info.
				 */
				virtual std::string get_creation_info();

			private:
				std::string device_name_;
				std::string device_serial_;
				std::string vendor_name_;
				std::string creation_info_;
		};

	} // namespace nite
} // namespace mae

#endif // DEVICE_INFO_HPP_
