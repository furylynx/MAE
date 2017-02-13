//
// Created on 13/02/2017.
//

#ifndef MAE_SENSOR_INFO_HPP
#define MAE_SENSOR_INFO_HPP

//custom includes
//...

//global includes
#include <string>
#include <sstream>
#include <memory>

namespace mae {
    namespace sensor {
        class sensor_info {
            public:
                /**
				 * Creates a new device info.
				 *
				 * @param device_name The device name.
				 * @param device_serial The device's serial number.
				 * @param vendor_name The vendor name.
				 * @param uri The sensor's URI. Default for OpenNI is 'idVendor/idProduct@BusID/DeviceId'. Other drivers may differ.
				 */
                sensor_info(std::string device_name, std::string device_serial, std::string vendor_name, std::string uri);
                virtual ~sensor_info();

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
                 * The URI is a unique identifier for the sensor. OpenNI default is 'idVendor/idProduct@BusID/DeviceId'. Other drivers may use different URIs.
                 *
                 *
                 * @return The URI.
                 */
                virtual std::string get_uri() const;

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
                friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<sensor_info>& obj)
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
                friend std::ostream& operator<<(std::ostream& os, const sensor_info& obj)
                {
                    os << obj.str();

                    return os;
                }

            private:
                std::string device_name_;
                std::string device_serial_;
                std::string vendor_name_;
                std::string uri_;
        };
    }
}


#endif //MAE_SENSOR_INFO_HPP
