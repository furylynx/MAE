/*
 * fl_server.cpp
 *
 *  Created on: 03.09.2014
 *      Author: keks
 */

#include "fl_server.hpp"

namespace mae
{
	namespace eventing
	{
		namespace fl
		{
			fl_server::fl_server(uint16_t port, std::string password)
					: server(
							std::shared_ptr<i_sequence_serializer<mae::fl::laban::laban_sequence> >(
									new laban_serializer()), port, password)
			{
			}

			fl_server::~fl_server()
			{
			}

		} // namespace fl
	} // namespace eventing
} // namespace mae
