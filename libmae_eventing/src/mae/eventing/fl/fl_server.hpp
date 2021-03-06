/*
 * fl_server.hpp
 *
 *  Created on: 03.09.2014
 *      Author: keks
 */

#ifndef FL_SERVER_HPP_
#define FL_SERVER_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "laban_serializer.hpp"

#include "../server.hpp"

//global includes
#include <mae/fl/laban/laban_sequence.hpp>
#include <mae/fl/fl_skeleton.hpp>
#include <mae/fl/fl_movement_controller.hpp>

namespace mae
{
	namespace eventing
	{
		namespace fl
		{

			class fl_server: public server<mae::fl::fl_skeleton, mae::fl::laban::laban_sequence>
			{
				public:
					/**
					 * Creates a new server which works with laban sequences and fl skeletons.
					 *
					 * @param mov_controller The movement controller to which sequences are registered if any received from a client.
					 * @param port The port to be worked on.
					 * @param password The server password.
					 * @param debug True for debug output.
					 */
					fl_server(mae::fl::fl_movement_controller* mov_controller = nullptr, uint16_t port = cs_base::get_default_port(), std::string password = "", bool debug = false);
					virtual ~fl_server();

			};

		} // namespace fl
	} // namespace eventing
} // namespace mae

#endif // FL_SERVER_HPP_
