/*
 * fl_client.hpp
 *
 *  Created on: 05.09.2014
 *      Author: furylynx
 */

#ifndef FL_CLIENT_HPP_
#define FL_CLIENT_HPP_

//custom includes
#include "laban_serializer.hpp"
#include "../client.hpp"

//global includes
#include <mae/fl/laban/laban_sequence.hpp>

namespace mae
{
	namespace eventing
	{
		namespace fl
		{

			class fl_client: public client<mae::fl::laban::laban_sequence>
			{
				public:
					/**
					 * Creates a new client which works with laban sequences.
					 *
					 * @param uri The uri of the server to connect to (IP address)
					 * @param port The port to be connected to.
					 * @param password The server password.
					 * @param short_sequences True if sequences shall be of short format (only sequence titles).
					 * @param debug True for debug output.
					 */
					fl_client(std::string uri, uint16_t port = cs_base::get_default_port(), std::string password = "", bool short_sequences = false, bool debug = false);
					virtual ~fl_client();
			};

		} // namespace eventing
	} // namespace eventing
} // namespace mae

#endif // FL_CLIENT_HPP_
