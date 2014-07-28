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
#include "../../mbool.hpp"

#include "laban_sequence.hpp"

#include "ps/i_pre_sign.hpp"
#include "ps/body_part.hpp"
#include "ps/area_part.hpp"
#include "ps/digit_part.hpp"
#include "ps/joint_part.hpp"
#include "ps/i_limb.hpp"
#include "ps/i_endpoint.hpp"
#include "ps/surface_part.hpp"
#include "ps/default_limb.hpp"
#include "ps/custom_limb.hpp"
#include "ps/prop.hpp"

#include "ps/e_side.hpp"
#include "ps/e_area.hpp"

#include "mv/accent_sign.hpp"
#include "mv/i_dynamics_sign.hpp"
#include "mv/pin.hpp"
#include "mv/cancellation_symbol.hpp"
#include "mv/turn_symbol.hpp"
#include "mv/vibration_symbol.hpp"
#include "mv/space_symbol.hpp"
#include "mv/space_measurement.hpp"
#include "mv/direction_symbol.hpp"
#include "mv/dynamic_sign.hpp"

#include "mv/e_direction.hpp"
#include "mv/e_level.hpp"
#include "mv/e_dynamic.hpp"


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

					static std::shared_ptr<ps::i_pre_sign> read_pre_sign(xmlpp::Node* node);

					static std::shared_ptr<ps::i_endpoint> read_end_point(xmlpp::Node* node);

					static std::shared_ptr<ps::i_limb> read_limb(xmlpp::Node* node);

					static std::shared_ptr<ps::surface_part> read_surface(xmlpp::Node* node);

					/**
					 * Reads the XML node and generates a movement element from it.
					 *
					 * @return A shared pointer to the movement.
					 */
					static std::shared_ptr<i_movement> read_movement(xmlpp::Node* node);

					static std::shared_ptr<mv::pin> read_pin(xmlpp::Node* node);

					static std::shared_ptr<mv::space_measurement> read_space_measurement(xmlpp::Node* node);

					static std::shared_ptr<mv::i_dynamics_sign> read_dynamics(xmlpp::Node* node);

					static std::shared_ptr<mv::direction_symbol> read_direction(xmlpp::Node* node);

					static std::shared_ptr<mv::space_symbol> read_space(xmlpp::Node* node);

					static std::shared_ptr<mv::turn_symbol> read_turn(xmlpp::Node* node);

					static std::shared_ptr<mv::vibration_symbol> read_vibration(xmlpp::Node* node);

					static std::shared_ptr<mv::cancellation_symbol> read_cancellation(xmlpp::Node* node);

			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // LABAN_SEQUENCE_READER_HPP_
