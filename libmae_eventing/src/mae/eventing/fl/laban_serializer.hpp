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
#include <mae/fl/laban/laban_sequence_reader.hpp>

namespace mae
{
	namespace eventing
	{
		namespace fl
		{

			class laban_serializer: public i_sequence_serializer<mae::fl::laban::laban_sequence>
			{
				public:
					/**
					 * Creates a new laban serializer.
					 */
					laban_serializer();
					virtual ~laban_serializer();

					/**
					 * Serializes the sequence so that it can be printed to a string.
					 *
					 * @param sequence The sequence.
					 * @return The string containing the serialized sequence.
					 */
					virtual std::string serialize(std::shared_ptr<mae::fl::laban::laban_sequence> sequence, bool short_type, bool no_header = false, unsigned int indent = 0, std::string namesp = "");

					/**
					 * Deserializes the sequence so that it can be registered to the engine.
					 *
					 * @param sequence The serialized sequence string.
					 * @return The sequence object.
					 */
					virtual std::shared_ptr<mae::fl::laban::laban_sequence> deserialize(std::string sequence);

				private:
					mae::fl::laban::laban_sequence_reader laban_reader_;

			};

		} // namespace fl
	} // namespace eventing
} // namespace mae

#endif // LABAN_SERIALIZER_HPP_
