/*
 * server_base.cpp
 *
 *  Created on: 15.09.2014
 *      Author: keks
 */

#include "cs_base.hpp"

namespace mae
{
	namespace eventing
	{

		cs_base::~cs_base()
		{
		}

		cs_base::cs_base()
		{
		}

		bool cs_base::is_message_complete(const std::string& message) const
		{
			//check for a complete message (message ends with "</pfx:message>" where pfx can be any prefix)
			bool result = false;

			std::size_t msg_pos = message.rfind("message>");
			if (msg_pos != std::string::npos && msg_pos != 0)
			{

				for (unsigned int i = msg_pos - 1; i >= 1; i--)
				{
					if (message.at(i) == '/' && message.at(i-1) == '<')
					{
						result = true;
						break;
					}
					else if ((i == msg_pos -1 && message.at(i) != ':') || (i != msg_pos - 1 && !std::isalnum(message.at(i))))
					{
						result = false;
						break;
					}
				}
			}

			return result;
		}

		uint16_t cs_base::get_default_port()
		{
			return 49337;
		}

	} // namespace eventing
} // namespace mae
