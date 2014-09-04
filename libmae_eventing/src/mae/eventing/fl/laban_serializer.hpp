/*
 * laban_serializer.hpp
 *
 *  Created on: 03.09.2014
 *      Author: keks
 */

#ifndef LABAN_SERIALIZER_HPP_
#define LABAN_SERIALIZER_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
#include "../i_sequence_serializer.hpp"

//global includes
#include <mae/fl/laban/laban_sequence.hpp>

namespace mae
{
	namespace eventing
	{
		namespace fl
		{

			class laban_serializer: public i_sequence_serializer<mae::fl::laban::laban_sequence>
			{
				public:
					laban_serializer();
					virtual ~laban_serializer();

					/**
					 * Serializes the sequence so that it can be printed to a string.
					 *
					 * @param sequence The sequence.
					 * @return The string containing the serialized sequence.
					 */
					virtual std::string serialize(std::shared_ptr<mae::fl::laban::laban_sequence> sequence);

					/**
					 * Deserializes the sequence so that it can be registered to the engine.
					 *
					 * @param sequence The serialized sequence string.
					 * @return The sequence object.
					 */
					virtual std::shared_ptr<mae::fl::laban::laban_sequence> deserialize(std::string sequence);

			};

		} // namespace fl
	} // namespace eventing
} // namespace mae

#endif // LABAN_SERIALIZER_HPP_
