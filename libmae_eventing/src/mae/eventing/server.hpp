/*
 * server.hpp
 *
 *  Created on: 03.09.2014
 *      Author: keks
 */

#ifndef SERVER_HPP_
#define SERVER_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "i_sequence_serializer.hpp"

//global includes
#include <mae/i_recognition_listener.hpp>
#include <mae/fl/laban/laban_sequence.hpp>

#include <vector>
#include <string>
#include <memory>
#include <cstdint>
#include <cinttypes>

#include <boost/asio.hpp>

namespace mae
{
	namespace eventing
	{
		template <typename U>
		class server : public i_recognition_listener<U>
		{
			public:
				server(std::shared_ptr<i_sequence_serializer<U> > serializer, uint16_t port = server::get_default_port(), std::string password = "");
				virtual ~server();

				virtual void notify_clients(long timestamp, std::vector<std::shared_ptr<U> > sequences);

				//TODO other methods

				//TODO restrict server to be only local, etc?!

				//TODO broadcast, for servers


				/**
				 * Returns the default port used by the server if no other is specified.
				 *
				 * @return The default port.
				 */
				static uint16_t get_default_port();

			private:
				uint16_t port_;
				std::string password_;

				std::shared_ptr<i_sequence_serializer<U> > serializer_;


				//private methods

				/**
				 * Is invoked each time sequences were recognized.
				 *
				 * @param timestamp The associated timestamp.
				 * @param sequences The recognized sequences.
				 */
				virtual void on_recognition(long timestamp, std::vector<std::shared_ptr<U> > sequences);

		};

	} // namespace eventing
} // namespace mae









namespace mae
{
	namespace eventing
	{

		template <typename U>
		server<U>::server(std::shared_ptr<i_sequence_serializer<U> > serializer, uint16_t port, std::string password)
		{
			port_ = port;
			password_ = password;
		}

		template <typename U>
		server<U>::~server()
		{
		}


		//**********************
		// STATIC METHODS
		//**********************

		template <typename U>
		uint16_t server<U>::get_default_port()
		{
			return 49337;
		}

	} // namespace eventing
} // namespace mae


#endif // SERVER_HPP_
