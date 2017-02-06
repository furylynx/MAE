/*
 * device_info.hpp
 *
 *  Created on: 30.09.2014
 *      Author: keks
 */

#ifndef DEVICE_INFO_HPP_
#define DEVICE_INFO_HPP_

//eclipse indexer fix
#include "indexer_fix.hpp"

//custom includes
//...

//global includes
#include <string>
#include <sstream>
#include <memory>

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
				virtual std::string get_device_name() const;

				/**
				 * Returns the device serial number.
				 *
				 * @return The serial number.
				 */
				virtual std::string get_device_serial() const;

				/**
				 * Returns the vendor name.
				 *
				 * @return The vendor name.
				 */
				virtual std::string get_vendor_name() const;

				/**
				 * The creation info is a string holding information on the creation of the device node.
				 *
				 * The info is split by slashes. The elements are 'idVendor/idProduct@BusID/DeviceId'.
				 *
				 * @return The creation info.
				 */
				virtual std::string get_creation_info() const;

				/**
				 * Returns the string representation for this object.
				 *
				 * @return The string representation.
				 */
				virtual std::string str() const;

				/**
				 * Prints the object to the stream.
				 *
				 * @param os
				 * @param obj The object to be printed.
				 * @return
				 */
				friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<device_info>& obj)
				{
					os << obj->str();

					return os;
				}

				/**
				 * Prints the object to the stream.
				 *
				 * @param os
				 * @param obj The object to be printed.
				 * @return
				 */
				friend std::ostream& operator<<(std::ostream& os, const device_info& obj)
				{
					os << obj.str();

					return os;
				}

			private:
				std::string device_name_;
				std::string device_serial_;
				std::string vendor_name_;
				std::string creation_info_;
		};

	} // namespace nite
} // namespace mae

#endif // DEVICE_INFO_HPP_
