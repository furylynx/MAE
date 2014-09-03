/*
 * rewriting_rules_reader.hpp
 *
 *  Created on: 27.08.2014
 *      Author: keks
 */

#ifndef REWRITING_RULES_READER_HPP_
#define REWRITING_RULES_READER_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
#include "decision_value.hpp"
#include "i_movement.hpp"
#include "movement.hpp"

#include "mv/direction_symbol.hpp"

#include "../../mbool.hpp"


//global includes
#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <vector>

#include <libxml++/libxml++.h>

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			class rewriting_rules_reader
			{
				public:
					rewriting_rules_reader();
					virtual ~rewriting_rules_reader();

					/**
					 * Reads the rewriting rules XML file and generates a vector of rules from it.
					 *
					 * @param xml_string The path to the XML file.
					 * @return A shared pointer to the sequence.
					 */
					virtual std::vector<std::shared_ptr<decision_value<i_movement, std::vector<std::vector<std::shared_ptr<i_movement> > > > > > read_rules_file(std::string file_name);

					/**
					 * Reads the rewriting rules XML string and generates a vector of rules from it.
					 *
					 * @param xml_string The XML string.
					 * @return A shared pointer to the sequence.
					 */
					virtual std::vector<std::shared_ptr<decision_value<i_movement, std::vector<std::vector<std::shared_ptr<i_movement> > > > > > read_rules_str(std::string xml_string);


				private:
					/**
					 * Returns the correct xpath.
					 *
					 * @param element The element to be prefixed.
					 * @param nsp The namespace
					 * @return The xpath.
					 */
					std::string get_xpath(std::string element, std::string nsp = "");

					std::string get_node_content(xmlpp::Node* parent_node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string element, std::string nsp, std::string default_return);

					std::vector<std::string> get_node_contents(xmlpp::Node* parent_node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string element, std::string nsp, std::string default_return);

					std::shared_ptr<decision_value<i_movement, std::vector<std::vector<std::shared_ptr<i_movement> > > > > read_rule(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp);

					std::vector<std::shared_ptr<i_movement> > read_rule_sequence(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp);

					std::shared_ptr<i_movement> read_element(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp);



			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // REWRITING_RULES_READER_HPP_