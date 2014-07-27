/*
 * laban_sequence_reader.hpp
 *
 *  Created on: 26.07.2014
 *      Author: keks
 */

#ifndef LABAN_SEQUENCE_READER_HPP_
#define LABAN_SEQUENCE_READER_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
#include "laban_sequence.hpp"

#include "ps/i_pre_sign.hpp"
#include "ps/body_part.hpp"
#include "ps/area_part.hpp"
#include "ps/prop.hpp"

#include "ps/e_side.hpp"
#include "ps/e_area.hpp"

//global includes
#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>
#include <libxml++/libxml++.h>

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			class laban_sequence_reader
			{
				public:
					/**
					 * Reads the Labanotation XML (which is defined by the Labanotation XML schema v.0.5) string
					 * and generates a sequence of it.
					 *
					 * @param xml_string The XML string.
					 * @return A shared pointer to the sequence.
					 */
					static std::shared_ptr<laban_sequence> read_sequence(std::string xml_string);

				private:
					/**
					 * Reads the XML node and generates a column definition from it.
					 *
					 * @return A shared pointer to the column definition.
					 */
					static std::shared_ptr<column_definition> read_column_definition(xmlpp::Node* node);

					/**
					 * Reads the XML node and generates a movement element from it.
					 *
					 * @return A shared pointer to the movement.
					 */
					static std::shared_ptr<i_movement> read_movement(xmlpp::Node* node);


			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // LABAN_SEQUENCE_READER_HPP_
