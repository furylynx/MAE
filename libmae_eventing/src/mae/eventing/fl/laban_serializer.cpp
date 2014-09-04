/*
 * laban_serializer.cpp
 *
 *  Created on: 03.09.2014
 *      Author: keks
 */

#include "laban_serializer.hpp"

namespace mae
{
	namespace eventing
	{
		namespace fl
		{

			laban_serializer::laban_serializer()
			{
			}

			laban_serializer::~laban_serializer()
			{
			}

			std::string laban_serializer::serialize(std::shared_ptr<mae::fl::laban::laban_sequence> sequence)
			{
				return sequence->xml();
			}

			std::shared_ptr<mae::fl::laban::laban_sequence> laban_serializer::deserialize(std::string sequence)
			{
				//TODO do stuff in here

				return nullptr;
			}

		} // namespace fl
	} // namespace eventing
} // namespace mae
