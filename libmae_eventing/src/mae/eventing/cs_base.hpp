/*
 * server_base.hpp
 *
 *  Created on: 15.09.2014
 *      Author: keks
 */

#ifndef SERVER_BASE_HPP_
#define SERVER_BASE_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
//...

//global includes
#include <string>
#include <iostream>


namespace mae
{
	namespace eventing
	{

		class cs_base
		{
			public:
				/**
				 * Creates a server base from which the server inherits.
				 */
				cs_base();

				virtual ~cs_base();

				/**
				 * Checks whether the sent message is complete. Returns true if that is the case. Returns false otherwise.
				 *
				 * @param message The message to be checked for completeness.
				 * @return True if complete.
				 */
				virtual bool is_message_complete(const std::string& message) const;

				/**
				 * Returns the default port used by the server if no other is specified.
				 *
				 * @return The default port.
				 */
				static uint16_t get_default_port();
		};

	} // namespace eventing
} // namespace mae

#endif // SERVER_BASE_HPP_
