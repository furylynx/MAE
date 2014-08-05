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
					 * and generates a sequence of it. The string should contain the whole XML part which is
					 * validated against the XML schema.
					 *
					 * @param xml_string The XML string.
					 * @return A shared pointer to the sequence.
					 */
					static std::shared_ptr<laban_sequence> read_sequence(std::string xml_string);

				private:
					/**
					 * Reads the XML node and generates a column definition from it.
					 *
					 * The node should contain the content of the column definition.
					 *
					 * @param node The XML node whose content contains the subelements of the column definition.
					 * @return A shared pointer to the column definition.
					 */
					static std::shared_ptr<column_definition> read_column_definition(xmlpp::Node* node);

					/**
					 * Reads the XML node and generates a pre sign.
					 *
					 * The node should be the parent of the pre sign.
					 *
					 * @param node The XML node.
					 * @return A shared pointer to the pre sign.
					 */
					static std::shared_ptr<ps::i_pre_sign> read_pre_sign(xmlpp::Node* node);

					/**
					 * Reads the XML node and generates an end point sign.
					 *
					 * The node should be the parent of the endpoint element.
					 *
					 * @param node The XML node.
					 * @return A shared pointer to the endpoint.
					 */
					static std::shared_ptr<ps::i_endpoint> read_end_point(xmlpp::Node* node);

					/**
					 * Reads the XML node and generates a limb sign.
					 *
					 * The node should be the parent of the limb element.
					 *
					 * @param node The XML node.
					 * @return A shared pointer to the limb.
					 */
					static std::shared_ptr<ps::i_limb> read_limb(xmlpp::Node* node);

					/**
					 * Reads the XML node and generates a surface sign.
					 *
					 * The node should be the parent of the surface element.
					 *
					 * @param node The XML node.
					 * @return A shared pointer to the surface.
					 */
					static std::shared_ptr<ps::surface_part> read_surface(xmlpp::Node* node);

					/**
					 * Reads the XML node and generates a movement element from it.
					 *
					 * The node should be the movement element itself.
					 *
					 * @param node The XML node.
					 * @return A shared pointer to the movement.
					 */
					static std::shared_ptr<i_movement> read_movement(xmlpp::Node* node);

					/**
					 * Reads the XML node and generates a pin sign.
					 *
					 * The node should be the pin element itself.
					 *
					 * @param node The XML node.
					 * @return A shared pointer to the pin.
					 */
					static std::shared_ptr<mv::pin> read_pin(xmlpp::Node* node);

					/**
					 * Reads the XML node and generates a space measurement element.
					 * The space measurement is an element which holds the subelements
					 * type, degree and direction. It is not to be confused with the
					 * space symbol which contains a space measurement element.
					 *
					 * The node should be the parent of the space measurement.
					 *
					 * @param node The xml node which is the parent of the space measurement.
					 * @return A shared pointer to the space measurement.
					 */
					static std::shared_ptr<mv::space_measurement> read_space_measurement(xmlpp::Node* node);

					/**
					 * Reads the XML node and generates a dynamics sign.
					 *
					 * The node should be the parent of the dynamics element.
					 *
					 * @param node The XML node.
					 * @return A shared pointer to the dynamics sign.
					 */
					static std::shared_ptr<mv::i_dynamics_sign> read_dynamics(xmlpp::Node* node);

					/**
					 * Reads the XML node and generates a direction symbol.
					 *
					 * The node should be the direction element itself.
					 *
					 * @param node The XML node.
					 * @return  A shared pointer to the direction symbol.
					 */
					static std::shared_ptr<mv::direction_symbol> read_direction(xmlpp::Node* node);

					/**
					 * Reads the XML node and generates a space symbol. A space symbols contains
					 * a space measurement sign and is not to be confused with it.
					 *
					 * The node should be the space element itself.
					 *
					 * @param node The XML node.
					 * @return A shared pointer to the space symbol.
					 */
					static std::shared_ptr<mv::space_symbol> read_space(xmlpp::Node* node);

					/**
					 *	Reads the XML node and generates a turn symbol.
					 *
					 * The node should be the turn element itself.
					 *
					 * @param node The XML node.
					 * @return A shared pointer to the turn symbol.
					 */
					static std::shared_ptr<mv::turn_symbol> read_turn(xmlpp::Node* node);

					/**
					 * Reads the XML node and generates a vibration symbol.
					 *
					 * The node should be the turn element itself.
					 *
					 * @param node The XML node.
					 * @return A shared pointer to the vibration symbol.
					 */
					static std::shared_ptr<mv::vibration_symbol> read_vibration(xmlpp::Node* node);

					/**
					 * Reads the XML node and generates a cancellation symbol.
					 *
					 * The node should be the turn element itself.
					 *
					 * @param node The XML node.
					 * @return A shared pointer to the cancellation symbol.
					 */
					static std::shared_ptr<mv::cancellation_symbol> read_cancellation(xmlpp::Node* node);

			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // LABAN_SEQUENCE_READER_HPP_
