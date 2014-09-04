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
#include <thread>
#include <unordered_map>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

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


				//socket stuff
				boost::asio::ip::tcp::acceptor acceptor_;
				boost::asio::io_service io_;

				std::shared_ptr<std::thread> thread_;

				std::vector<std::shared_ptr<boost::asio::ip::tcp::socket> > connections_;
				std::unordered_map<std::shared_ptr<boost::asio::ip::tcp::socket>, std::shared_ptr<std::string> > msgs_;


				//private methods
				virtual void initialize();

				virtual void accept(std::shared_ptr<boost::asio::ip::tcp::socket> connection, const boost::system::error_code& error);

				virtual void begin_write(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::string message);

				virtual void on_write(std::shared_ptr<boost::asio::ip::tcp::socket> connection, const boost::system::error_code& error);

				virtual void begin_read(std::shared_ptr<boost::asio::ip::tcp::socket> connection, int state, long timeout = 0);

				virtual void on_read(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::shared_ptr<char> buffer, int state, const boost::system::error_code& error, const std::size_t bytes_transferred);

				virtual void on_read_complete(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::string message, int state, const boost::system::error_code& error);

				virtual void server_run();


				virtual void handle_initial_message(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::string message);

				virtual void handle_further_message(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::string message);

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

			acceptor_ = boost::asio::ip::tcp::acceptor(io_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port_));
		}

		template <typename U>
		server<U>::~server()
		{
			//stop io and reset
			io_.stop();
			io_.reset();
		}



		template <typename U>
		void server<U>::initialize()
		{
			//create new socket to accept a connection
			std::shared_ptr<boost::asio::ip::tcp::socket> nsocket(new boost::asio::ip::tcp::socket(io_) );
			acceptor_.async_accept(*nsocket, boost::bind(&server::accept, this, nsocket, boost::asio::placeholders::error));

			//run thread in order to invoke io_.run()
			thread_ = std::shared_ptr<std::thread>(new std::thread(&server::server_run));
		}

		template <typename U>
		void server<U>::accept(std::shared_ptr<boost::asio::ip::tcp::socket> connection, const boost::system::error_code& error)
		{
			if (!error)
			{
				//TODO check password?, dont push back here but after initial dialog is complete?
				connections_.push_back(connection);

				//TODO do stuff n stuff - read initial message etc
				//TODO timeout ?!
				begin_read(connection, 0, 30);
			}
			else
			{
				std::cerr << "Error while accepting sockets. Continue accepting." << std::endl;
			}

			//create new socket to accept another connection
			std::shared_ptr<boost::asio::ip::tcp::socket> nsocket(new boost::asio::ip::tcp::socket(io_) );
			acceptor_.async_accept(*nsocket, boost::bind(&server::accept, this, nsocket, boost::asio::placeholders::error));
		}

		template <typename U>
		void server<U>::begin_write(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::string message)
		{
			connection->async_send(boost::asio::buffer(message.c_str(), message.size()), boost::bind(&server::on_write, this, connection, boost::asio::placeholders::error));
		}

		template <typename U>
		void server<U>::on_write(std::shared_ptr<boost::asio::ip::tcp::socket> connection, const boost::system::error_code& error)
		{
			if (error)
			{
				std::cerr << "An error has occured during the write." << std::endl;
			}

			//TODO more?!
		}

		template <typename U>
		void server<U>::begin_read(std::shared_ptr<boost::asio::ip::tcp::socket> connection, int state, long timeout)
		{
			//reset previously buffered messages
			if (msgs_.find(connection) != msgs_.end())
			{
				msgs_[connection] = std::shared_ptr<std::string>(new std::string());
			}
			else
			{
				msgs_.insert(std::make_pair(connection, std::shared_ptr<std::string>(new std::string())));
			}

			//initialize new buffer
			unsigned long int max_length = 1024;
			std::shared_ptr<char> nbuffer = std::shared_ptr<char>(new char[max_length]);
			connection->async_read_some(boost::asio::buffer(nbuffer.get(), max_length), boost::bind(&server::accept, this, connection, nbuffer, state, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		}

		template <typename U>
		void server<U>::on_read(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::shared_ptr<char> buffer, int state, const boost::system::error_code& error, const std::size_t bytes_transferred)
		{
			//TODO handle the transferred bytes
			if (error)
			{
				std::cerr << "An error occured while reading!" << std::endl;

				//notify on read complete but an error (and thus most likely an incomplete message)
				on_read_complete(connection, "", state, error);
			}
			else
			{
				std::shared_ptr<std::string> tmp_str = msgs_.at(connection);
				tmp_str->append(std::string(*buffer, bytes_transferred));

				//TODO check for a complete message
				bool message_complete = true;

				if (message_complete)
				{
					std::string result = *(msgs_.at(connection));
					on_read_complete(connection, result, state, error);
				}
				else
				{
					unsigned long int max_length = 1024;
					std::shared_ptr<char> nbuffer = std::shared_ptr<char>(new char[max_length]);
					connection->async_read_some(boost::asio::buffer(nbuffer.get(), max_length), boost::bind(&server::accept, this, connection, nbuffer, state, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
				}
			}

		}

		template <typename U>
		void server<U>::on_read_complete(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::string message, int state, const boost::system::error_code& error)
		{
			if (error)
			{
				std::cerr << "The message could not be read, cause an error occurred." << std::endl;
			}
			else
			{
				//TODO remove
				std::cout << "read message from client: " << message << std::endl;

				if (state == 0)
				{
					handle_initial_message(connection, message);
				}
				else
				{
					handle_further_message(connection, message);
				}
			}
		}

		template <typename U>
		void server<U>::server_run()
		{
			io_.run();
		}


		template <typename U>
		void server<U>::handle_initial_message(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::string message)
		{
			bool accepted = false;

			//TODO parse the initial message and decide what to do

			if (accepted)
			{
				connections_.push_back(connection);

				//TODO more?
				begin_read(connection, 1, 0);
			}
		}

		template <typename U>
		void server<U>::handle_further_message(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::string message)
		{
			//TODO parse the initial message and decide what to do
			bool accepted = false;

			//TODO parse the initial message and decide what to do

			if (accepted)
			{
				//notify
			}
		}

		template <typename U>
		void server<U>::notify_clients(long timestamp, std::vector<std::shared_ptr<U> > sequences)
		{
			//iterate all registered clients and notify them
			for (unsigned int i = 0; i < connections_.size(); i++)
			{
				std::string msg = "";

				//TODO generate message to be sent
				//serializer_->serialize(sequences.at(i));

    	    	begin_write(connections_.at(i), "");
			}

			//TODO more? e.g. check whether message was sent successfully?!
		}



		template <typename U>
		void server<U>::on_recognition(long timestamp, std::vector<std::shared_ptr<U> > sequences)
		{
			notify_clients(timestamp, sequences);
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
