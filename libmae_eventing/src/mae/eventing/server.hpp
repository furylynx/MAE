/*
 * server.hpp
 *
 *  Created on: 03.09.2014
 *      Author: keks
 */

#ifndef SERVER_HPP_
#define SERVER_HPP_

//eclipse indexer fix
#include "indexer_fix.hpp"

//custom includes
#include "i_sequence_serializer.hpp"
#include "i_registration_manager.hpp"
#include "cs_base.hpp"

#include "mxml.hpp"


//global includes
#include <mae/mae.hpp>

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
				/**
				 * Creates a new server based on boost sockets.
				 *
				 * @param serializer The serializer which is used to parse received sequences and serialize outgoing ones.
				 * @param mov_controller The movement controller to which sequences are registered if any received from a client.
				 * @param port The port to be worked on.
				 * @param password The server password.
				 * @param debug True for debug output.
				 */
				server(std::shared_ptr<i_sequence_serializer<U> > serializer, movement_controller<T,U>* mov_controller = nullptr, uint16_t port = cs_base::get_default_port(), std::string password = "", bool debug = false);
				virtual ~server();

				/**
				 * Notifies all connected clients on recognized sequences.
				 *
				 * @param timestamp The timestamp.
				 * @param sequences The recognized sequences.
				 */
				virtual void notify_clients(uint64_t timestamp, std::vector<std::shared_ptr<U> > sequences);

				/**
				 * Returns all registered registration managers.
				 *
				 * @return The managers.
				 */
				virtual std::list<std::shared_ptr<i_registration_manager<U> > > get_registration_managers();

				/**
				 * Adds another registration manager to the server. The registered managers handle received sequences
				 * that are intended to be added to a movement controller.
				 *
				 * @param manager The manager.
				 */
				virtual void add_registration_manager(std::shared_ptr<i_registration_manager<U> > manager);

				/**
				 * Removes a registration manager from the controller.
				 *
				 * @param manager The manager.
				 * @return True if successful.
				 */
				virtual bool remove_registration_manager(std::shared_ptr<i_registration_manager<U> > manager);

				/**
				 * Registers a sequence to the connected controller if any.
				 *
				 * @param sequence The sequence to be registered.
				 */
				virtual void register_sequence(std::shared_ptr<U> sequence);

				/**
				 * Is invoked each time sequences were recognized.
				 *
				 * @param timestamp The associated timestamp.
				 * @param sequences The recognized sequences.
				 */
				virtual void on_recognition(uint64_t timestamp, std::vector<std::shared_ptr<U> > sequences);

				/**
				 * Is invoked each time sequences were recognized and only titles of the sequences are present.
				 *
				 * @param timestamp The associated timestamp.
				 * @param sequences The recognized sequences.
				 */
				virtual void on_recognition(uint64_t timestamp, std::vector<std::string> title);

			protected:

				/**
				 * Handles the initial message received from a newly connected client.
				 * If password is fine, the client is accepted and the accept_client method is invoked.
				 *
				 * @param client The newly connected client.
				 * @param message The received message.
				 * @param server_password The password for the server.
				 */
				virtual void handle_initial_message(std::shared_ptr<boost::asio::ip::tcp::socket> client, std::string message, std::string server_password);

				/**
				 * Handles any further message received from the client. This message is the sequence registration message and if the sequence is parsed
				 * the register_sequence method is invoked.
				 *
				 * @param client The client.
				 * @param message The received message.
				 */
				virtual void handle_further_message(std::shared_ptr<boost::asio::ip::tcp::socket> client, std::string message);

				/**
				 * Creates a recognition message which informs the client on recognized sequences. This method is invoked for each client.
				 *
				 * @param timestamp The timestamp of the recognition event.
				 * @param sequences The recognized sequences.
				 * @param short_message True if the message is intended to be short.
				 * @return The message string.
				 */
				virtual std::string create_recognition_message(uint64_t timestamp, std::vector<std::shared_ptr<U> > sequences, bool short_message);

				/**
				 * Accepts a client and registers the requested message format.
				 *
				 * @param connection The client.
				 * @param short_message The message format. True for short messages.
				 */
				virtual void accept_client(std::shared_ptr<boost::asio::ip::tcp::socket> connection, bool short_message);

				/**
				 * Removes the client from the connection list and closes the connection to the client.
				 *
				 * @param connection The client.
				 */
				virtual void remove_client(std::shared_ptr<boost::asio::ip::tcp::socket> connection);

			private:
				bool debug_;

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


				/**
				 * Initializes the server.
				 */
				virtual void initialize();

				/**
				 * Accepts a new client and begins the read the initial message.
				 *
				 * @param connection The client.
				 * @param error The error.
				 */
				virtual void accept(std::shared_ptr<boost::asio::ip::tcp::socket> connection, const boost::system::error_code& error);

				/**
				 * Begins to write a message to the client.
				 *
				 * @param connection The client.
				 * @param message The message.
				 */
				virtual void begin_write(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::string message);

				/**
				 * Async callback for a completely sent message.
				 *
				 * @param connection The client.
				 * @param error The error.
				 */
				virtual void on_write(std::shared_ptr<boost::asio::ip::tcp::socket> connection, const boost::system::error_code& error);

				/**
				 * Begins reading a message from the client.
				 *
				 * @param connection The connection.
				 * @param state The state.
				 */
				virtual void begin_read(std::shared_ptr<boost::asio::ip::tcp::socket> connection, int state);

				/**
				 * Async callback for a read event. Checks whether the message is complete or reading must be continued.
				 *
				 * @param connection The client.
				 * @param buffer The read buffer.
				 * @param state The state
				 * @param error The error.
				 * @param bytes_transferred The number of transferred bytes.
				 */
				virtual void on_read(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::shared_ptr<char> buffer, int state, const boost::system::error_code& error, const std::size_t bytes_transferred);

				/**
				 * Is invoked whenever a message was read completely. Performs further steps based on the state and the parsed messages.
				 *
				 * @param connection The client.
				 * @param message The message.
				 * @param state The state.
				 * @param error The error.
				 */
				virtual void on_read_complete(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::string message, int state, const boost::system::error_code& error);

				/**
				 * Thread routine for the server's io.
				 */
				virtual void server_run();

				/**
				 * Notifies the movement controller on a newly registered sequence. Checks the registration managers before.
				 *
				 * @param sequence The sequence.
				 */
				virtual void notify_registered_sequence(std::shared_ptr<U> sequence);

		};

	} // namespace eventing
} // namespace mae









namespace mae
{
	namespace eventing
	{

		template <typename T, typename U>
		server<T, U>::server(std::shared_ptr<i_sequence_serializer<U> > serializer, movement_controller<T,U>* mov_controller, uint16_t port, std::string password, bool debug)
		{
			debug_ = debug;

			port_ = port;
			password_ = password;
			serializer_ = serializer;
			movement_controller_ = mov_controller;

			if (serializer_ == nullptr)
			{
				throw std::invalid_argument("Serializer must not be null!");
			}

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
				begin_read(connection, 0);
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
			if (debug_)
			{
				std::cout << "server: sending a message to a client." << std::endl;
			}

			connection->async_send(boost::asio::buffer(message.c_str(), message.size()), boost::bind(&server::on_write, this, connection, boost::asio::placeholders::error));
		}

		template <typename T, typename U>
		void server<T, U>::on_write(std::shared_ptr<boost::asio::ip::tcp::socket> connection, const boost::system::error_code& error)
		{
			if (error)
			{
				if (error == boost::asio::error::broken_pipe)
				{
					remove_client(connection);
					return;
				}

				std::cerr << "An error has occurred during the write: " << error.message() << std::endl;
			}
		}

		template <typename T, typename U>
		void server<T, U>::begin_read(std::shared_ptr<boost::asio::ip::tcp::socket> connection, int state)
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
			connection->async_read_some(boost::asio::buffer(nbuffer.get(), max_length), boost::bind(&server::on_read, this, connection, nbuffer, state, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		}

		template <typename T, typename U>
		void server<T, U>::on_read(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::shared_ptr<char> buffer, int state, const boost::system::error_code& error, const std::size_t bytes_transferred)
		{
			//handle the transferred bytes
			if (error)
			{
				//notify on read complete but an error (and thus most likely an incomplete message)
				on_read_complete(connection, *msgs_.at(connection), state, error);
			}
			else
			{
				std::shared_ptr<std::string> tmp_str = msgs_.at(connection);
				tmp_str->append(std::string(buffer.get(), bytes_transferred));

				if (is_message_complete(*tmp_str))
				{
					std::string result = *(msgs_.at(connection));
					on_read_complete(connection, result, state, error);
				}
				else
				{
					unsigned long int max_length = 1024;
					std::shared_ptr<char> nbuffer = std::shared_ptr<char>(new char[max_length]);

					connection->async_read_some(boost::asio::buffer(nbuffer.get(), max_length), boost::bind(&server::on_read, this, connection, nbuffer, state, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
				}
			}

		}

		template <typename T, typename U>
		void server<T, U>::on_read_complete(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::string message, int state, const boost::system::error_code& error)
		{
			if (error)
			{
				if (error == boost::asio::error::eof)
				{
					remove_client(connection);
					return;
				}

				if (error == boost::asio::error::timed_out)
				{
					begin_read(connection, state);
					return;
				}

				std::cerr << "The whole message could not be read since an error occurred: " << error.message() << std::endl;
			}
			else
			{
				if (debug_)
				{
					std::cout << "server: a message was read completely. Try to parse now." << std::endl;
				}

				if (state == 0)
				{
					handle_initial_message(connection, message, password_);

					if (msg_types_.find(connection) == msg_types_.end())
					{
						//client was not accepted, therefore the connection is closed
						boost::system::error_code code(boost::asio::error::no_permission);
						connection->close(code);
					}
				}
				else
				{
					handle_further_message(connection, message);
					begin_read(connection, state);
				}
			}
		}

		template <typename T, typename U>
		void server<T, U>::server_run()
		{
			io_->run();
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
		void server<T, U>::handle_initial_message(std::shared_ptr<boost::asio::ip::tcp::socket> client, std::string message, std::string server_password)
		{
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

			if (password == server_password)
			{
				accepted = true;
			}

			if (accepted)
			{
				accept_client(client, type_short);
			}
			else
			{
				if (debug_)
				{
					std::cout << "server: the client is declined since the password was incorrect." << std::endl;
				}
			}
		}

		template <typename T, typename U>
		void server<T, U>::handle_further_message(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::string message)
		{
			if (debug_)
			{
				std::cout << "server: handling a sequence to be registered." << std::endl;
			}

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

			//trimming and unescaping
			sequence_str = mae::mstr::trim(mae::mstr::replace_unesc(mae::mstr::replace_unesc(sequence_str, "&lt;", "<"), "&gt;", ">"));

			std::shared_ptr<U> sequence = serializer_->deserialize(sequence_str);

			if (sequence != nullptr)
			{
				if (debug_)
				{
					std::cout << "server: registering the sequence." << std::endl;
				}

				register_sequence(sequence);
			}
		}

		template <typename T, typename U>
		void server<T, U>::accept_client(std::shared_ptr<boost::asio::ip::tcp::socket> connection, bool short_message)
		{
			if (debug_)
			{
				std::cout << "server: the client is accepted." << std::endl;
			}

			msg_types_.insert(std::make_pair(connection, short_message));
			connections_.push_back(connection);

			begin_read(connection, 1);
		}

		template <typename T, typename U>
		void server<T, U>::remove_client(std::shared_ptr<boost::asio::ip::tcp::socket> connection)
		{
			if (debug_)
			{
				std::cout << "server: a client is removed." << std::endl;
			}

			connection->close();

			for (std::vector<std::shared_ptr<boost::asio::ip::tcp::socket> >::iterator it = connections_.begin(); it != connections_.end(); it++)
			{
				if (connection == *it)
				{
					connections_.erase(it);
				}
			}

			msg_types_.erase(connection);
		}

		template <typename T, typename U>
		void server<T, U>::register_sequence(std::shared_ptr<U> sequence)
		{
			if (debug_)
			{
				std::cout << "server: registering a sequence to the movement controller." << std::endl;
			}

			if (movement_controller_ != nullptr)
			{
				movement_controller_->register_sequence(sequence);
			}
		}

		template <typename T, typename U>
		std::string server<T, U>::create_recognition_message(uint64_t timestamp, std::vector<std::shared_ptr<U> > sequences, bool short_message)
		{
			std::stringstream sstr;

			//print header
			sstr << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>" << std::endl;

			sstr << "<maee:message xmlns:maee=\"http://www.example.org/maeeventing\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://www.example.org/maeeventing maeeventing.xsd \">" << std::endl;
			sstr << "\t<maee:timestamp>" << timestamp << "</maee:timestamp>" << std::endl;

			for (unsigned int i = 0; i < sequences.size(); i++)
			{
				if (!short_message)
				{
					sstr << "\t<maee:sequence>" << std::endl;
					sstr << mae::mstr::replace_esc(mae::mstr::replace_esc(serializer_->serialize(sequences.at(i), short_message, false, 2), "<", "&lt;"), ">","&gt;");
					sstr << "\t</maee:sequence>" << std::endl;
				}
				else
				{
					sstr << "\t<maee:title>";
					sstr << mae::mstr::replace_esc(mae::mstr::replace_esc(serializer_->serialize(sequences.at(i), short_message, true, 2), "<", "&lt;"), ">","&gt;");
					sstr << "</maee:title>" << std::endl;
				}
			}

			sstr << "</maee:message>" << std::endl;

			return sstr.str();
		}

		template <typename T, typename U>
		void server<T, U>::notify_clients(uint64_t timestamp, std::vector<std::shared_ptr<U> > sequences)
		{
			if (debug_)
			{
				std::cout << "server: notify clients about a recognized sequence." << std::endl;
			}

			//iterate all registered clients and notify them
			for (unsigned int i = 0; i < connections_.size(); i++)
			{
				std::string msg = "";

				// generate message to be sent
				std::string message = create_recognition_message(timestamp, sequences, msg_types_.at(connections_.at(i)));

    	    	begin_write(connections_.at(i), message);
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
		void server<T, U>::on_recognition(uint64_t timestamp, std::vector<std::shared_ptr<U> > sequences)
		{
			notify_clients(timestamp, sequences);
		}

		template <typename T, typename U>
		void server<T, U>::on_recognition(uint64_t timestamp, std::vector<std::string> title)
		{
			//do nothing since the other method is doing all the work
		}

	} // namespace eventing
} // namespace mae


#endif // SERVER_HPP_
