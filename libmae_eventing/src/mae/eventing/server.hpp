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
#include "i_registration_manager.hpp"
#include "cs_base.hpp"


//global includes
#include <mae/i_recognition_listener.hpp>
#include <mae/fl/laban/laban_sequence.hpp>
#include <mae/mxml.hpp>
#include <mae/movement_controller.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cstdint>
#include <cinttypes>
#include <thread>
#include <unordered_map>
#include <list>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <libxml++/libxml++.h>


namespace mae
{
	namespace eventing
	{
		template <typename T, typename U>
		class server : public cs_base, public i_recognition_listener<U>
		{
			public:
				server(std::shared_ptr<i_sequence_serializer<U> > serializer, movement_controller<T,U>* mov_controller = nullptr, uint16_t port = cs_base::get_default_port(), std::string password = "");
				virtual ~server();

				virtual void notify_clients(long timestamp, std::vector<std::shared_ptr<U> > sequences);

				virtual std::list<std::shared_ptr<i_registration_manager<U> > > get_registration_managers();

				virtual void add_registration_manager(std::shared_ptr<i_registration_manager<U> > manager);

				virtual bool remove_registration_manager(std::shared_ptr<i_registration_manager<U> > manager);


			private:
				uint16_t port_;
				std::string password_;

				std::shared_ptr<i_sequence_serializer<U> > serializer_;


				//socket stuff
				std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor_;
				std::shared_ptr<boost::asio::io_service> io_;

				std::shared_ptr<std::thread> thread_;

				std::vector<std::shared_ptr<boost::asio::ip::tcp::socket> > connections_;
				std::unordered_map<std::shared_ptr<boost::asio::ip::tcp::socket>, std::shared_ptr<std::string> > msgs_;
				std::unordered_map<std::shared_ptr<boost::asio::ip::tcp::socket>, bool> msg_types_;

				std::list<std::shared_ptr<i_registration_manager<U> > > registration_managers_;

				movement_controller<T,U>* movement_controller_;


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

				virtual void notify_registered_sequence(std::shared_ptr<U> sequence);

				/**
				 * Is invoked each time sequences were recognized.
				 *
				 * @param timestamp The associated timestamp.
				 * @param sequences The recognized sequences.
				 */
				virtual void on_recognition(long timestamp, std::vector<std::shared_ptr<U> > sequences);

				/**
				 * Is invoked each time sequences were recognized and only titles of the sequences are present.
				 *
				 * @param timestamp The associated timestamp.
				 * @param sequences The recognized sequences.
				 */
				virtual void on_recognition(long timestamp, std::vector<std::string> title);
		};

	} // namespace eventing
} // namespace mae









namespace mae
{
	namespace eventing
	{

		template <typename T, typename U>
		server<T, U>::server(std::shared_ptr<i_sequence_serializer<U> > serializer, movement_controller<T,U>* mov_controller, uint16_t port, std::string password)
		{
			std::cout << "server invoked." << std::endl;

			port_ = port;
			password_ = password;
			serializer_ = serializer;
			movement_controller_ = mov_controller;

			io_ = std::shared_ptr<boost::asio::io_service>(new boost::asio::io_service());
			acceptor_ = std::shared_ptr<boost::asio::ip::tcp::acceptor>(new boost::asio::ip::tcp::acceptor(*io_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port_)));

			initialize();
		}

		template <typename T, typename U>
		server<T, U>::~server()
		{
			//stop io and reset
			io_->stop();
			io_->reset();
		}

		template <typename T, typename U>
		void server<T, U>::initialize()
		{
			std::cout << "initializing the socket server..." << std::endl;

			//create new socket to accept a connection
			std::shared_ptr<boost::asio::ip::tcp::socket> nsocket(new boost::asio::ip::tcp::socket(*io_) );
			acceptor_->async_accept(*nsocket, boost::bind(&server::accept, this, nsocket, boost::asio::placeholders::error));

			//run thread in order to invoke io_.run()
			thread_ = std::shared_ptr<std::thread>(new std::thread(&server::server_run, this));
		}

		template <typename T, typename U>
		void server<T, U>::accept(std::shared_ptr<boost::asio::ip::tcp::socket> connection, const boost::system::error_code& error)
		{
			if (!error)
			{
				begin_read(connection, 0, 30);

				//TODO remove
				std::cout << "Accepted another socket." << std::endl;
			}
			else
			{
				std::cerr << "Error while accepting sockets. Continue accepting." << std::endl;
			}

			//create new socket to accept another connection
			std::shared_ptr<boost::asio::ip::tcp::socket> nsocket(new boost::asio::ip::tcp::socket(*io_) );
			acceptor_->async_accept(*nsocket, boost::bind(&server::accept, this, nsocket, boost::asio::placeholders::error));
		}

		template <typename T, typename U>
		void server<T, U>::begin_write(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::string message)
		{
			connection->async_send(boost::asio::buffer(message.c_str(), message.size()), boost::bind(&server::on_write, this, connection, boost::asio::placeholders::error));
		}

		template <typename T, typename U>
		void server<T, U>::on_write(std::shared_ptr<boost::asio::ip::tcp::socket> connection, const boost::system::error_code& error)
		{
			if (error)
			{
				std::cerr << "An error has occured during the write." << std::endl;
			}
			else
			{
				//TODO remove
				std::cout << "Sequence written to client!" << std::endl;
			}
		}

		template <typename T, typename U>
		void server<T, U>::begin_read(std::shared_ptr<boost::asio::ip::tcp::socket> connection, int state, long timeout)
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
//			boost::asio::async_read(*connection, boost::asio::buffer(nbuffer.get(), max_length), boost::bind(&server::on_read, this, connection, nbuffer, state, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
			connection->async_read_some(boost::asio::buffer(nbuffer.get(), max_length), boost::bind(&server::on_read, this, connection, nbuffer, state, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		}

		template <typename T, typename U>
		void server<T, U>::on_read(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::shared_ptr<char> buffer, int state, const boost::system::error_code& error, const std::size_t bytes_transferred)
		{
			//handle the transferred bytes
			if (error)
			{
				std::cerr << "An error occured while reading!" << std::endl;

				//notify on read complete but an error (and thus most likely an incomplete message)
				on_read_complete(connection, "", state, error);
			}
			else
			{
				std::cout << "read some: '" << buffer.get() << "' | bytes transferred " << bytes_transferred << std::endl;


				std::shared_ptr<std::string> tmp_str = msgs_.at(connection);
				tmp_str->append(std::string(buffer.get(), bytes_transferred));

				if (is_message_complete(*tmp_str))
				{
					std::cout << "message is complete!" << std::endl;

					std::string result = *(msgs_.at(connection));
					on_read_complete(connection, result, state, error);
				}
				else
				{
					std::cout << "read some more." << std::endl;
					unsigned long int max_length = 1024;
					std::shared_ptr<char> nbuffer = std::shared_ptr<char>(new char[max_length]);

//					boost::asio::async_read(*connection, boost::asio::buffer(nbuffer.get(), max_length), boost::bind(&server::on_read, this, connection, nbuffer, state, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
					connection->async_read_some(boost::asio::buffer(nbuffer.get(), max_length), boost::bind(&server::on_read, this, connection, nbuffer, state, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
				}
			}

		}

		template <typename T, typename U>
		void server<T, U>::on_read_complete(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::string message, int state, const boost::system::error_code& error)
		{
			if (error)
			{
				std::cerr << "The whole message could not be read since an error occurred." << std::endl;
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

		template <typename T, typename U>
		void server<T, U>::server_run()
		{
			std::cout << "running io..." << std::endl;
			io_->run();
			std::cout << "stopped running io!" << std::endl;
		}

		template <typename T, typename U>
		std::list<std::shared_ptr<i_registration_manager<U> > > server<T, U>::get_registration_managers()
		{
			return registration_managers_;
		}

		template <typename T, typename U>
		void server<T, U>::add_registration_manager(std::shared_ptr<i_registration_manager<U> > manager)
		{
			registration_managers_.push_back(manager);
		}

		template <typename T, typename U>
		bool server<T, U>::remove_registration_manager(std::shared_ptr<i_registration_manager<U> > manager)
		{
			for (typename std::list<std::shared_ptr<i_registration_manager<U> > >::iterator it = registration_managers_.begin(); it != registration_managers_.end(); it++)
			{
				if (manager == *it)
				{
					registration_managers_.erase(it);
					return true;
				}
			}

			return false;
		}

		template <typename T, typename U>
		void server<T, U>::handle_initial_message(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::string message)
		{
			//TODO remove
			std::cout << "handle initial message" << std::endl;

			bool accepted = false;

			//parse the initial message and decide what to do
			std::stringstream sstr;
			sstr << message;

			xmlpp::DomParser parser;
			parser.parse_stream(sstr);

			xmlpp::Document* doc = parser.get_document();
			xmlpp::Node* root_node = doc->get_root_node();

			//setup namespace prefix
			std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map = std::shared_ptr<xmlpp::Node::PrefixNsMap>(new xmlpp::Node::PrefixNsMap());
			if (root_node->get_namespace_prefix().size() > 0)
			{
				namespace_map->insert(std::make_pair(root_node->get_namespace_prefix(), root_node->get_namespace_uri()));
			}

			std::string nsp = root_node->get_namespace_prefix();

			//---------------
			// main elements
			//---------------
			std::string type_str = mae::mxml::get_node_content(root_node, namespace_map, "type", nsp, "short");
			bool type_short = (type_str == "short");
			std::string password = mae::mxml::get_node_content(root_node, namespace_map, "password", nsp, "");

			if (password == password_)
			{
				accepted = true;
			}

			if (accepted)
			{
				std::cout << "accepted, short=" << type_short << std::endl;

				connections_.push_back(connection);
				msg_types_.insert(std::make_pair(connection, type_short));

				begin_read(connection, 1, 0);
			}
		}

		template <typename T, typename U>
		void server<T, U>::handle_further_message(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::string message)
		{
			std::stringstream sstr;
			sstr << message;

			xmlpp::DomParser parser;
			parser.parse_stream(sstr);

			xmlpp::Document* doc = parser.get_document();
			xmlpp::Node* root_node = doc->get_root_node();

			//setup namespace prefix
			std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map = std::shared_ptr<xmlpp::Node::PrefixNsMap>(new xmlpp::Node::PrefixNsMap());
			if (root_node->get_namespace_prefix().size() > 0)
			{
				namespace_map->insert(std::make_pair(root_node->get_namespace_prefix(), root_node->get_namespace_uri()));
			}

			std::string nsp = root_node->get_namespace_prefix();

			//---------------
			// main elements
			//---------------
			std::string sequence_str = mae::mxml::get_node_content(root_node, namespace_map, "sequence", nsp, "");

			std::shared_ptr<U> sequence = serializer_->deserialize(sequence_str);

			if (sequence != nullptr)
			{
				//TODO remove
				std::cout << "received a sequence!" << std::endl;

				//TODO register sequence to movement controller
			}
		}

		template <typename T, typename U>
		void server<T, U>::notify_clients(long timestamp, std::vector<std::shared_ptr<U> > sequences)
		{
			//iterate all registered clients and notify them
			for (unsigned int i = 0; i < connections_.size(); i++)
			{
				std::string msg = "";

				// generate message to be sent
				std::stringstream sstr;

				//print header
				sstr << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>" << std::endl;

				sstr << "<maee:message xmlns:maee=\"http://www.example.org/maeeventing\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://www.example.org/maeeventing maeeventing.xsd\">" << std::endl;
				sstr << "\t<maee:sequences>" << std::endl;

				for (unsigned int i = 0; i < sequences.size(); i++)
				{
					serializer_->serialize(sequences.at(i), msg_types_.at(connections_.at(i)), true, 2);
				}

				sstr << "\t</maee:sequences>" << std::endl;
				sstr << "</maee:message>";

    	    	begin_write(connections_.at(i), sstr.str());
			}
		}

		template <typename T, typename U>
		void server<T, U>::notify_registered_sequence(std::shared_ptr<U> sequence)
		{
			bool result = true;

			for (typename std::list<std::shared_ptr<i_registration_manager<U> > >::iterator it = registration_managers_.begin(); it != registration_managers_.end(); it++)
			{
				result &= (*it)->on_sequence_registered(sequence);
			}

			if (result && movement_controller_ != nullptr)
			{
				//register sequence to movement_controller
				movement_controller_->register_sequence(sequence);
			}

		}

		template <typename T, typename U>
		void server<T, U>::on_recognition(long timestamp, std::vector<std::shared_ptr<U> > sequences)
		{
			notify_clients(timestamp, sequences);
		}

		template <typename T, typename U>
		void server<T, U>::on_recognition(long timestamp, std::vector<std::string> title)
		{
			//do nothing
		}

	} // namespace eventing
} // namespace mae


#endif // SERVER_HPP_
