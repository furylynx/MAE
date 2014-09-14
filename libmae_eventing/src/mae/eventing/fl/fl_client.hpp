/*
 * fl_client.hpp
 *
 *  Created on: 05.09.2014
 *      Author: keks
 */

#ifndef FL_CLIENT_HPP_
#define FL_CLIENT_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

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
					fl_client(std::string uri, uint16_t port = server_base::get_default_port(), std::string password = "", bool short_sequences = false);
					virtual ~fl_client();
			};

		} // namespace fl
	} // namespace eventing
} // namespace mae

#endif // FL_CLIENT_HPP_
