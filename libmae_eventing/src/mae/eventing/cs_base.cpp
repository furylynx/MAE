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
			//check for a complete message (message ends with "</pfx:message>" where pfx can be the shortcut for any defined namespace)
			bool found_nsp = false;
			std::string::size_type pos = 0;

			std::string message_closer = "</message>";
			std::string nsp = "=\"http://www.example.org/maeeventing\"";

			while (!found_nsp && pos < message.length())
			{
				pos = message.find("xmlns:", pos);

				if (pos != std::string::npos)
				{
					for (std::string::size_type i = pos + 6; i < message.length(); i++)
					{
						if (message.substr(i, nsp.length()) == nsp)
						{
							found_nsp = true;
							std::stringstream sstr;
							sstr << "</" << message.substr(pos + 6, i - pos + 6) << ":message>";
							message_closer = sstr.str();
							break;
						}

						if (!std::isalnum(message.at(i)))
						{
							pos = i;
							break;
						}
					}
				}
			}

			return (message.rfind(message_closer) != std::string::npos);
		}

		uint16_t cs_base::get_default_port()
		{
			return 49337;
		}

	} // namespace eventing
} // namespace mae
