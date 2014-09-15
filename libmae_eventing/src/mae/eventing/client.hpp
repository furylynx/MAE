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

//global includes
#include <mae/i_recognition_listener.hpp>
#include <mae/fl/laban/laban_sequence.hpp>
#include <mae/mxml.hpp>

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
				client(std::shared_ptr<i_sequence_serializer<U> > serializer, std::string uri, uint16_t port = cs_base::get_default_port(), std::string password = "", bool short_sequences = false);
				virtual ~client();

				virtual void register_sequence(std::shared_ptr<U> sequence);

				virtual void add_listener(std::shared_ptr<i_recognition_listener<U> > recognition_listener);

				virtual bool remove_listener(std::shared_ptr<i_recognition_listener<U> > recognition_listener);

				virtual std::list<std::shared_ptr<i_recognition_listener<U> > > get_listeners();

			private:
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


				//methods

				virtual void initialize();

				virtual void begin_write(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::string message, int state);

				virtual void on_write(std::shared_ptr<boost::asio::ip::tcp::socket> connection, int state, const boost::system::error_code& error);

				virtual void begin_read(std::shared_ptr<boost::asio::ip::tcp::socket> connection, long timeout = 0);

				virtual void on_read(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::shared_ptr<char> buffer, const boost::system::error_code& error, const std::size_t bytes_transferred);

				virtual void on_read_complete(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::string message, const boost::system::error_code& error);

				virtual void client_run();

				virtual void notify_listeners(long timestamp, std::vector<std::shared_ptr<U> > sequences);

				virtual void notify_listeners(long timestamp, std::vector<std::string> sequences_titles);

		};

	} // namespace eventing
} // namespace mae




//implementation

namespace mae
{
	namespace eventing
	{
		template <typename U>
		client<U>::client(std::shared_ptr<i_sequence_serializer<U> > serializer, std::string uri, uint16_t port, std::string password, bool short_sequences)
		{
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
			std::stringstream sstr;
			sstr << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>" << std::endl;
			sstr << "<maee:message xmlns:maee=\"http://www.example.org/maeeventing\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://www.example.org/maeeventing maeeventing.xsd\">" << std::endl;
			sstr << "\t<maee:type>";
			if (short_sequences_)
			{
				sstr << "short";
			}
			else
			{
				sstr << "normal";
			}
			sstr << "</maee:type>" << std::endl;
			sstr << "</maee:message>" << std::endl;

			std::string registration_message = sstr.str();

			begin_write(socket_, registration_message, 0);

			//run thread in order to invoke io_.run()
			thread_ = std::shared_ptr<std::thread>(new std::thread(&client::client_run, this));
		}

		template <typename U>
		void client<U>::begin_write(std::shared_ptr<boost::asio::ip::tcp::socket> connection, std::string message, int state)
		{
			std::cout << "try to send message: " << std::endl;
			std::cout << message << std::endl;
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
					begin_read(socket_, 0);
				}
				else
				{
					//do nothing?
				}
			}
		}

		template <typename U>
		void client<U>::begin_read(std::shared_ptr<boost::asio::ip::tcp::socket> connection, long timeout)
		{
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
				std::cerr << "An error occured while reading!" << std::endl;

				//notify on read complete but an error (and thus most likely an incomplete message)
				on_read_complete(connection, "", error);
			}
			else
			{
				//append read content to buffer
				buffer_.append(std::string(*buffer, bytes_transferred));

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
				std::cerr << "The message could not be read, cause an error occurred." << std::endl;
			}
			else
			{
				//TODO remove
				std::cout << "read message from client: " << message << std::endl;

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

				long timestamp = std::stol(mae::mxml::get_node_content(root_node, namespace_map, "timestamp", nsp, "0"));



				if (!short_sequences_)
				{
					std::vector<std::shared_ptr<U> > sequences;
					std::vector<std::string> sequences_str = mae::mxml::get_node_contents(root_node, namespace_map, "sequences/score", nsp, "");

					for (unsigned int i = 0; i < sequences_str.size(); i++)
					{
						std::shared_ptr<U> sequence = serializer_->deserialize(sequences_str.at(i));
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
					std::vector<std::string> sequences_str = mae::mxml::get_node_contents(root_node, namespace_map, "sequences/title", nsp, "");

					//notify listeners
					notify_listeners(timestamp, sequences_str);
				}

				//continue to read
				begin_read(socket_, 0);
			}
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
			std::stringstream sstr;
			sstr << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>" << std::endl;
			sstr << "<maee:message xmlns:maee=\"http://www.example.org/maeeventing\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://www.example.org/maeeventing maeeventing.xsd\">" << std::endl;
			sstr << "\t<maee:sequence>";
			sstr << serializer_->serialize(sequence, short_sequences_, true, 2);
			sstr << "\t</maee:sequence>" << std::endl;
			sstr << "</maee:message>" << std::endl;

			std::string registration_message = sstr.str();

			begin_write(socket_, registration_message, 1);
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
		void client<U>::notify_listeners(long timestamp, std::vector<std::shared_ptr<U> > sequences)
		{
			for (typename std::list<std::shared_ptr<i_recognition_listener<U> > >::iterator it = recognition_listeners_.begin(); it != recognition_listeners_.end(); it++)
			{
				(*it)->on_recognition(timestamp, sequences);
			}
		}

		template <typename U>
		void client<U>::notify_listeners(long timestamp, std::vector<std::string> sequences_titles)
		{
			for (typename std::list<std::shared_ptr<i_recognition_listener<U> > >::iterator it = recognition_listeners_.begin(); it != recognition_listeners_.end(); it++)
			{
				(*it)->on_recognition(timestamp, sequences_titles);
			}
		}

	} // namespace eventing
} // namespace mae

#endif // CLIENT_HPP_
