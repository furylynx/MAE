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
//...

namespace mae
{
	namespace eventing
	{

		class server_base
		{
			public:
				/**
				 * Creates a server base from which the server inherits.
				 */
				server_base();

				virtual ~server_base();


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
