/*
 * client.hpp
 *
 *  Created on: 03.09.2014
 *      Author: keks
 */

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "i_sequence_serializer.hpp"
#include "cs_base.hpp"
#include "../mxml.hpp"

//global includes
#include <mae/mae.hpp>

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
		template <typename U>
		class client : public cs_base
		{
			public:
				/**
				 * Creates a new client that connects to the server.
				 *
				 * @param serializer The serializer used to parse and serialze sequences.
				 * @param uri The server's address (IP).
				 * @param port The port on which the server operates.
				 * @param password The password for the server.
				 * @param short_sequences True for short sequences (e.g. only titles).
				 * @param debug True for debug output.
				 */
				client(std::shared_ptr<i_sequence_serializer<U> > serializer, std::string uri, uint16_t port = cs_base::get_default_port(), std::string password = "", bool short_sequences = false, bool debug = false);
				virtual ~client();

				/**
				 * Registers another sequence to the server side.
				 *
				 * @param sequence The sequence to be registered.
				 */
				virtual void register_sequence(std::shared_ptr<U> sequence);

				/**
				 * Adds a listener to the client which is invoked whenever a recognition event is distributed.
				 *
				 * @param recognition_listener The listener.
				 */
				virtual void add_listener(std::shared_ptr<i_recognition_listener<U> > recognition_listener);

				/**
				 * Removes the listener from the client.
				 *
				 * @param recognition_listener The listener.
				 * @return True on success.
				 */
				virtual bool remove_listener(std::shared_ptr<i_recognition_listener<U> > recognition_listener);

				/**
				 * Returns all registered listeners.
				 *
				 * @return The listeners.
				 */
				virtual std::list<std::shared_ptr<i_recognition_listener<U> > > get_listeners();

				/**
				 * Notifies the listeners on a recognized sequence.
				 *
				 * @param timestamp The timestamp.
				 * @param sequences The sequences.
				 */
				virtual void notify_listeners(uint64_t timestamp, std::vector<std::shared_ptr<U> > sequences);

				/**
				 * Notifies the listeners on a recognized sequence. Only the sequence titles are provided.
				 *
				 * @param timestamp The timestamp.
				 * @param sequences_titles The sequence titles.
				 */
				virtual void notify_listeners(uint64_t timestamp, std::vector<std::string> sequences_titles);

			protected:

				/**
				 * Handles the message which contains information on recognized sequences.
				 * Is invoked whenever a message was completely read from the stream.
				 * From this method the specific notify_listeners-method is invoked.
				 *
				 * @param message The message to be parsed
				 */
				virtual void handle_recognition_message(std::string message, bool short_type);

				/**
				 * Generates the initial message which is sent to the server in order to establish a
				 * connection.
				 *
				 * @param short_type The message type to be received. True for short.
				 * @return The message string.
				 */
				virtual std::string create_initial_message(bool short_type, std::string client_password);

				/**
				 * Generates the registration message which is sent to the server in order to register another
				 * sequence to the movement controller. This message contains always the whole sequence
				 * representation in order to be constructed at the server.
				 *
				 * @param sequence The sequence.
				 * @return The message string.
				 */
				virtual std::string create_registration_message(std::shared_ptr<U> sequence);

				/**
				 * Closes the connection to the server.
				 *
				 * @param connection The connection.
				 */
				virtual void remove_connection(std::shared_ptr<boost::asio::ip::tcp::socket> connection);

			private:
				bool debug_;

				std::string uri_;
				uint16_t port_;
				std::string password_;

				bool short_sequences_;
				std::shared_ptr<i_sequence_serializer<U> > serializer_;

				std::list<std::shared_ptr<i_recognition_listener<U> > > recognition_listeners_;

				std::shared_ptr<std::thread> thread_;
				std::string buffer_;

				//socket members
				boost::asio::io_service io_;
				std::shared_ptr<boost::asio::ip::tcp::socket> socket_;
				std::shared_ptr<boost::asio::ip::tcp::resolver> resolver_;


				/**
				 * Initializes the client.
				 *
				 */
				virtual void initialize();

				/**
				 * Begins to write the message to the server.
				 *
				 * @param connection The server.
				 * @param message The message.
				 * @param state The state.
				 */
				virtual void begin_write(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::string message, int state);

				/**
				 * Async callback for a write event.
				 *
				 * @param connection The server.
				 * @param state The state.
				 * @param error The error.
				 */
				virtual void on_write(std::shared_ptr<boost::asio::ip::tcp::socket> connection, int state, const boost::system::error_code& error);

				/**
				 * Begins to read a message from the server.
				 *
				 * @param connection The server.
				 */
				virtual void begin_read(std::shared_ptr<boost::asio::ip::tcp::socket> connection);

				/**
				 * Async callback for read events. Checks whether the message is complete or another read is necessary.
				 *
				 * @param connection The server.
				 * @param buffer The read buffer.
				 * @param error The error.
				 * @param bytes_transferred The number of transferred bytes.
				 */
				virtual void on_read(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::shared_ptr<char> buffer, const boost::system::error_code& error, const std::size_t bytes_transferred);

				/**
				 * Is invoked whenever a message is completely read.
				 *
				 * @param connection The server.
				 * @param message The message.
				 * @param error The error.
				 */
				virtual void on_read_complete(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::string message, const boost::system::error_code& error);


				/**
				 * Thread routine for the client's io.
				 */
				virtual void client_run();

		};

	} // namespace eventing
} // namespace mae




//implementation

namespace mae
{
	namespace eventing
	{
		template <typename U>
		client<U>::client(std::shared_ptr<i_sequence_serializer<U> > serializer, std::string uri, uint16_t port, std::string password, bool short_sequences, bool debug)
		{
			debug_ = debug;

			uri = uri_;
			port_ = port;
			password_ = password;

			short_sequences_ = short_sequences;
			serializer_ = serializer;

			socket_ = std::shared_ptr<boost::asio::ip::tcp::socket>(new boost::asio::ip::tcp::socket(io_));
			resolver_ = std::shared_ptr<boost::asio::ip::tcp::resolver>(new boost::asio::ip::tcp::resolver(io_));

			initialize();

		}

		template <typename U>
		client<U>::~client()
		{
		}

		template <typename U>
		void client<U>::initialize()
		{
			//start connection
			boost::asio::ip::tcp::resolver::query query(uri_, std::to_string(port_));
			boost::asio::connect(*socket_, resolver_->resolve(query));

			//send initiation message
			std::string registration_message = create_initial_message(short_sequences_, password_);

			begin_write(socket_, registration_message, 0);

			//run thread in order to invoke io_.run()
			thread_ = std::shared_ptr<std::thread>(new std::thread(&client::client_run, this));
		}

		template <typename U>
		void client<U>::begin_write(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::string message, int state)
		{
			if (debug_)
			{
				std::cout << "client: sending message to the server." << std::endl;
			}

			connection->async_send(boost::asio::buffer(message.c_str(), message.size()), boost::bind(&client::on_write, this, connection, state, boost::asio::placeholders::error));
		}

		template <typename U>
		void client<U>::on_write(std::shared_ptr<boost::asio::ip::tcp::socket> connection, int state, const boost::system::error_code& error)
		{
			if (error)
			{
				std::cerr << "An error has occured during the write." << std::endl;
			}
			else
			{
				if (state == 0)
				{
					//initial sequence written to server, now listen
					begin_read(socket_);
				}
				else
				{
					//do nothing?
				}
			}
		}

		template <typename U>
		void client<U>::begin_read(std::shared_ptr<boost::asio::ip::tcp::socket> connection)
		{
			if (debug_)
			{
				std::cout << "client: waiting for messages fromt the server." << std::endl;
			}

			//reset previously buffered messages
			buffer_ = "";

			//initialize new buffer
			unsigned long int max_length = 1024;
			std::shared_ptr<char> nbuffer = std::shared_ptr<char>(new char[max_length]);
			connection->async_read_some(boost::asio::buffer(nbuffer.get(), max_length), boost::bind(&client::on_read, this, connection, nbuffer, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		}

		template <typename U>
		void client<U>::on_read(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::shared_ptr<char> buffer, const boost::system::error_code& error, const std::size_t bytes_transferred)
		{
			//handle the transferred bytes
			if (error)
			{
				//notify on read complete but an error (and thus most likely an incomplete message)
				on_read_complete(connection, buffer_, error);
			}
			else
			{
				//append read content to buffer
				buffer_.append(std::string(buffer.get(), bytes_transferred));

				if (is_message_complete(buffer_))
				{
					on_read_complete(connection, buffer_, error);
				}
				else
				{
					unsigned long int max_length = 1024;
					std::shared_ptr<char> nbuffer = std::shared_ptr<char>(new char[max_length]);
					connection->async_read_some(boost::asio::buffer(nbuffer.get(), max_length), boost::bind(&client::on_read, this, connection, nbuffer, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
				}
			}
		}

		template <typename U>
		void client<U>::on_read_complete(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::string message, const boost::system::error_code& error)
		{
			if (error)
			{
				if (error == boost::asio::error::eof)
				{
					remove_connection(connection);
					return;
				}

				if (debug_)
				{
					std::cerr << "client: a message could not be read. An error occurred: " << error.message() << std::endl;
				}

				begin_read(socket_);
			}
			else
			{
				if (debug_)
				{
					std::cout << "client: a message was read completely and will be parsed now." << std::endl;
				}

				handle_recognition_message(message, short_sequences_);

				//continue to read
				begin_read(socket_);
			}
		}

		template <typename U>
		void client<U>::handle_recognition_message(std::string message, bool short_type)
		{
			//parse received message

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

			uint64_t timestamp = std::stoull(mae::mxml::get_node_content(root_node, namespace_map, "timestamp", nsp, "0"));

			if (!short_type)
			{
				std::vector<std::shared_ptr<U> > sequences;
				std::vector<std::string> sequences_str = mae::mxml::get_node_contents(root_node, namespace_map, "sequence", nsp, "");

				for (unsigned int i = 0; i < sequences_str.size(); i++)
				{
					std::string sequence_str = mstr::trim(mstr::replace_unesc(mstr::replace_unesc(sequences_str.at(i), "&lt;", "<"), "&gt;", ">"));

					std::shared_ptr<U> sequence = serializer_->deserialize(sequence_str);
					if (sequence != nullptr)
					{
						sequences.push_back(sequence);
					}
				}

				//notify listeners
				notify_listeners(timestamp, sequences);
			}
			else
			{
				std::vector<std::string> sequences_str = mae::mxml::get_node_contents(root_node, namespace_map, "title", nsp, "");

				std::vector<std::string> titles;
				for (unsigned int i = 0; i < sequences_str.size(); i++)
				{
					std::string title = mstr::trim(mstr::replace_unesc(mstr::replace_unesc(sequences_str.at(i), "&lt;", "<"), "&gt;", ">"));

					titles.push_back(title);
				}

				//notify listeners
				notify_listeners(timestamp, titles);
			}
		}

		template <typename U>
		std::string client<U>::create_initial_message(bool short_type, std::string client_password)
		{
			std::stringstream sstr;
			sstr << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>" << std::endl;
			sstr << "<maee:message xmlns:maee=\"http://www.example.org/maeeventing\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://www.example.org/maeeventing maeeventing.xsd\">" << std::endl;
			sstr << "\t<maee:type>";
			if (short_type)
			{
				sstr << "short";
			}
			else
			{
				sstr << "normal";
			}
			sstr << "</maee:type>" << std::endl;
			sstr << "\t<maee:password>" << client_password<< "</maee:password>" << std::endl;
			sstr << "</maee:message>" << std::endl;

			return sstr.str();
		}

		template <typename U>
		std::string client<U>::create_registration_message(std::shared_ptr<U> sequence)
		{
			std::stringstream sstr;
			sstr << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>" << std::endl;
			sstr << "<maee:message xmlns:maee=\"http://www.example.org/maeeventing\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://www.example.org/maeeventing maeeventing.xsd\">" << std::endl;
			sstr << "\t<maee:sequence>";
			sstr << mstr::replace_esc(mstr::replace_esc(serializer_->serialize(sequence, short_sequences_, false, 2), "<", "&lt;"), ">","&gt;");
			sstr << "\t</maee:sequence>" << std::endl;
			sstr << "</maee:message>" << std::endl;

			return sstr.str();
		}

		template <typename U>
		void client<U>::remove_connection(std::shared_ptr<boost::asio::ip::tcp::socket> connection)
		{
			connection->close();
		}

		template <typename U>
		void client<U>::client_run()
		{
			io_.run();
		}

		template <typename U>
		void client<U>::register_sequence(std::shared_ptr<U> sequence)
		{
			//send initiation message
			std::string registration_message = create_registration_message(sequence);

			if (socket_->is_open())
			{
				begin_write(socket_, registration_message, 1);
			}
			else
			{
				throw std::runtime_error("Connection to server is closed. Cannot register any sequences.");
			}
		}

		template <typename U>
		void client<U>::add_listener(std::shared_ptr<i_recognition_listener<U> > recognition_listener)
		{
			recognition_listeners_.push_back(recognition_listener);
		}

		template <typename U>
		bool client<U>::remove_listener(std::shared_ptr<i_recognition_listener<U> > recognition_listener)
		{
			for (typename std::list<std::shared_ptr<i_recognition_listener<U> > >::iterator it = recognition_listeners_.begin(); it != recognition_listeners_.end(); it++)
			{
				if (recognition_listener == *it)
				{
					recognition_listeners_.erase(it);
					return true;
				}
			}

			return false;
		}

		template <typename U>
		std::list<std::shared_ptr<i_recognition_listener<U> > > client<U>::get_listeners()
		{
			return recognition_listeners_;
		}

		template <typename U>
		void client<U>::notify_listeners(uint64_t timestamp, std::vector<std::shared_ptr<U> > sequences)
		{
			if (debug_)
			{
				std::cout << "client: notify listeners about recognized sequences." << std::endl;
			}

			for (typename std::list<std::shared_ptr<i_recognition_listener<U> > >::iterator it = recognition_listeners_.begin(); it != recognition_listeners_.end(); it++)
			{
				(*it)->on_recognition(timestamp, sequences);
			}


			std::vector<std::string> sequence_titles;

			for (unsigned int i = 0; i < sequences.size(); i++)
			{
				sequence_titles.push_back(serializer_->get_title(sequences.at(i)));
			}

			notify_listeners(timestamp, sequence_titles);
		}

		template <typename U>
		void client<U>::notify_listeners(uint64_t timestamp, std::vector<std::string> sequences_titles)
		{
			if (debug_)
			{
				std::cout << "client: notify listeners about recognized sequence by providing the titles." << std::endl;
			}

			for (typename std::list<std::shared_ptr<i_recognition_listener<U> > >::iterator it = recognition_listeners_.begin(); it != recognition_listeners_.end(); it++)
			{
				(*it)->on_recognition(timestamp, sequences_titles);
			}
		}

	} // namespace eventing
} // namespace mae

#endif // CLIENT_HPP_
