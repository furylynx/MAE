/*
 * internal_laban_sequence_reader.hh
 *
 *  Created on: 26.07.2014
 *      Author: furylynx
 */

#ifndef INTERNAL_LABAN_SEQUENCE_READER_HH_
#define INTERNAL_LABAN_SEQUENCE_READER_HH_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
#include "../../mbool.hpp"
#include "../../mstr.hpp"

#include "laban_sequence.hpp"

#include "movement.hpp"
#include "path.hpp"
#include "relationship_bow.hpp"
#include "room_direction.hpp"

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
#include "mv/relationship_endpoint.hpp"

//global includes
#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <fstream>

#include <libxml++/libxml++.h>


namespace mae
{
	namespace fl
	{
		namespace laban
		{

			class internal_laban_sequence_reader
			{
				public:
					/**
					 * Creates a new internal laban sequence reader.
					 */
					internal_laban_sequence_reader();
					virtual ~internal_laban_sequence_reader();

					/**
					 * Reads the Labanotation XML (which is defined by the Labanotation XML schema v.0.5) file
					 * and generates a sequence of it.
					 *
					 * @param xml_string The path to the XML file.
					 * @return A shared pointer to the sequence.
					 */
					virtual std::shared_ptr<laban_sequence> read_sequence_file(std::string file_name);

					/**
					 * Reads the Labanotation XML (which is defined by the Labanotation XML schema v.0.5) string
					 * and generates a sequence of it. The string should contain the whole XML part which is
					 * validated against the XML schema.
					 *
					 * @param xml_string The XML string.
					 * @return A shared pointer to the sequence.
					 */
					virtual std::shared_ptr<laban_sequence> read_sequence_str(std::string xml_string);

				protected:

					/**
					 * Reads the XML node and generates a column definition from it.
					 *
					 * The node should contain the content of the column definition.
					 *
					 * @param node The XML node whose content contains the subelements of the column definition.
					 * @param namespace_map The namespace mapping.
					 * @param nsp The applied namespace.
					 * @return A shared pointer to the column definition.
					 */
					std::shared_ptr<column_definition> read_column_definition(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp);

					/**
					 * Reads the XML node and generates a pre sign.
					 *
					 * The node should be the parent of the pre sign.
					 *
					 * @param node The XML node.
					 * @param namespace_map The namespace mapping.
					 * @param nsp The applied namespace.
					 * @return A shared pointer to the pre sign.
					 */
					std::shared_ptr<ps::i_pre_sign> read_pre_sign(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp);

					/**
					 * Reads the XML node and generates an end point sign.
					 *
					 * The node should be the parent of the endpoint element.
					 *
					 * @param node The XML node.
					 * @param namespace_map The namespace mapping.
					 * @param nsp The applied namespace.
					 * @return A shared pointer to the endpoint.
					 */
					std::shared_ptr<ps::i_endpoint> read_end_point(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp);

					/**
					 * Reads the XML node and generates a limb sign.
					 *
					 * The node should be the parent of the limb element.
					 *
					 * @param node The XML node.
					 * @param namespace_map The namespace mapping.
					 * @param nsp The applied namespace.
					 * @return A shared pointer to the limb.
					 */
					std::shared_ptr<ps::i_limb> read_limb(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp);

					/**
					 * Reads the XML node and generates a surface sign.
					 *
					 * The node should be the parent of the surface element.
					 *
					 * @param node The XML node.
					 * @param namespace_map The namespace mapping.
					 * @param nsp The applied namespace.
					 * @return A shared pointer to the surface.
					 */
					std::shared_ptr<ps::surface_part> read_surface(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp);

					/**
					 * Reads the XML node and generates a movement element from it.
					 *
					 * The node should be the movement element itself.
					 *
					 * @param node The XML node.
					 * @param namespace_map The namespace mapping.
					 * @param nsp The applied namespace.
					 * @return A shared pointer to the movement.
					 */
					std::shared_ptr<i_movement> read_movement(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp);

					/**
					 * Reads the XML node and generates a pin sign.
					 *
					 * The node should be the pin element itself.
					 *
					 * @param node The XML node.
					 * @param namespace_map The namespace mapping.
					 * @param nsp The applied namespace.
					 * @return A shared pointer to the pin.
					 */
					std::shared_ptr<mv::pin> read_pin(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp);

					/**
					 * Reads the XML node and generates a space measurement element.
					 * The space measurement is an element which holds the subelements
					 * type, degree and direction. It is not to be confused with the
					 * space symbol which contains a space measurement element.
					 *
					 * The node should be the parent of the space measurement.
					 *
					 * @param node The xml node which is the parent of the space measurement.
					 * @param namespace_map The namespace mapping.
					 * @param nsp The applied namespace.
					 * @return A shared pointer to the space measurement.
					 */
					std::shared_ptr<mv::space_measurement> read_space_measurement(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp);

					/**
					 * Reads the XML node and generates a dynamics sign.
					 *
					 * The node should be the parent of the dynamics element.
					 *
					 * @param node The XML node.
					 * @param namespace_map The namespace mapping.
					 * @param nsp The applied namespace.
					 * @return A shared pointer to the dynamics sign.
					 */
					std::shared_ptr<mv::i_dynamics_sign> read_dynamics(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp);

					/**
					 * Reads the XML node and generates a direction symbol.
					 *
					 * The node should be the direction element itself.
					 *
					 * @param node The XML node.
					 * @param namespace_map The namespace mapping.
					 * @param nsp The applied namespace.
					 * @return  A shared pointer to the direction symbol.
					 */
					std::shared_ptr<mv::direction_symbol> read_direction(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp);

					/**
					 * Reads the XML node and generates a space symbol. A space symbols contains
					 * a space measurement sign and is not to be confused with it.
					 *
					 * The node should be the space element itself.
					 *
					 * @param node The XML node.
					 * @param namespace_map The namespace mapping.
					 * @param nsp The applied namespace.
					 * @return A shared pointer to the space symbol.
					 */
					std::shared_ptr<mv::space_symbol> read_space(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp);

					/**
					 *	Reads the XML node and generates a turn symbol.
					 *
					 * The node should be the turn element itself.
					 *
					 * @param node The XML node.
					 * @param namespace_map The namespace mapping.
					 * @param nsp The applied namespace.
					 * @return A shared pointer to the turn symbol.
					 */
					std::shared_ptr<mv::turn_symbol> read_turn(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp);

					/**
					 * Reads the XML node and generates a vibration symbol.
					 *
					 * The node should be the turn element itself.
					 *
					 * @param node The XML node.
					 * @param namespace_map The namespace mapping.
					 * @param nsp The applied namespace.
					 * @return A shared pointer to the vibration symbol.
					 */
					std::shared_ptr<mv::vibration_symbol> read_vibration(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp);

					/**
					 * Reads the XML node and generates a cancellation symbol.
					 *
					 * The node should be the turn element itself.
					 *
					 * @param node The XML node.
					 * @param namespace_map The namespace mapping.
					 * @param nsp The applied namespace.
					 * @return A shared pointer to the cancellation symbol.
					 */
					std::shared_ptr<mv::cancellation_symbol> read_cancellation(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp);

					/**
					 * Reads the XML node and generates a path symbol.
					 *
					 * The node should be the path element itself.
					 *
					 * @param node The XML node.
					 * @param namespace_map The namespace mapping.
					 * @param nsp The applied namespace.
					 * @return A shared pointer to the path symbol.
					 */
					std::shared_ptr<i_movement> read_path(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp);

					/**
					 * Reads the XML node and generates a room direction symbol.
					 *
					 * The node should be the room direction element itself.
					 *
					 * @param node The XML node.
					 * @param namespace_map The namespace mapping.
					 * @param nsp The applied namespace.
					 * @return A shared pointer to the room direction symbol.
					 */
					std::shared_ptr<i_movement> read_room_direction(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp);

					/**
					 * Reads the XML node and generates a relationship bow symbol.
					 *
					 * The node should be the relationship bow element itself.
					 *
					 * @param node The XML node.
					 * @param namespace_map The namespace mapping.
					 * @param nsp The applied namespace.
					 * @return A shared pointer to the relationship bow symbol.
					 */
					std::shared_ptr<i_movement> read_relationship_bow(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp);

					/**
					 * Reads the XML node and generates a relationship endpoint element.
					 *
					 * The node should be the relationship endpoint element itself.
					 *
					 * @param node The XML node.
					 * @param namespace_map The namespace mapping.
					 * @param nsp The applied namespace.
					 * @return A shared pointer to the relationship endpoint element.
					 */
					std::shared_ptr<mv::relationship_endpoint> read_relationship_endpoint(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp);

			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // INTERNAL_LABAN_SEQUENCE_READER_HH_
