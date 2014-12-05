/*
 * fl_client.cpp
 *
 *  Created on: 05.09.2014
 *      Author: keks
 */

#include "fl_client.hpp"

namespace mae
{
	namespace eventing
	{
		namespace fl
		{

			fl_client::fl_client(std::string uri, uint16_t port, std::string password, bool short_sequences, bool debug)
			: client(std::shared_ptr<i_sequence_serializer<mae::fl::laban::laban_sequence> >(
					new laban_serializer()), uri, port, password, short_sequences, debug)
			{
			}

			fl_client::~fl_client()
			{
			}

		} // namespace fl
	} // namespace eventing
} // namespace mae
