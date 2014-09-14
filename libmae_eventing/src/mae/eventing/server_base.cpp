/*
 * server_base.cpp
 *
 *  Created on: 15.09.2014
 *      Author: keks
 */

#include "server_base.hpp"

namespace mae
{
	namespace eventing
	{

		server_base::~server_base()
		{
		}

		server_base::server_base()
		{
		}

		uint16_t server_base::get_default_port()
		{
			return 49337;
		}

	} // namespace eventing
} // namespace mae
