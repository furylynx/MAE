//
// Created on 13/02/2017.
//

#include "sensor_info.hpp"


namespace mae
{
    namespace sensor
    {

        sensor_info::sensor_info(std::string device_name, std::string device_serial, std::string vendor_name, std::string uri)
        {
            device_name_ = device_name;
            device_serial_ = device_serial;
            vendor_name_ = vendor_name;
            uri_ = uri;
        }

        sensor_info::~sensor_info()
        {
        }

        std::string sensor_info::get_device_name() const
        {
            return device_name_;
        }

        std::string sensor_info::get_device_serial() const
        {
            return device_serial_;
        }

        std::string sensor_info::get_vendor_name() const
        {
            return vendor_name_;
        }

        std::string sensor_info::get_uri() const
        {
            return uri_;
        }

        std::string sensor_info::str() const
        {
            std::stringstream sstr;

            sstr << device_name_ << " (serial " << device_serial_ << ") by " << vendor_name_ << " - " << uri_ << std::endl;

            return sstr.str();
        }

    } // namespace nite2
} // namespace mae