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
				device_info(std::string device_name, std::string device_serial);
				virtual ~device_info();

				virtual std::string get_device_name();
				virtual std::string get_device_serial();

			private:
				std::string device_name_;
				std::string device_serial_;
		};

	} // namespace nite
} // namespace mae

#endif // DEVICE_INFO_HPP_
