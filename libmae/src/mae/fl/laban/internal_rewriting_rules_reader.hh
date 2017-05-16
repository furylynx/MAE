#ifndef MAE_FL_LABAN_INTERNAL_REWRITING_RULES_READER_HH_
#define MAE_FL_LABAN_INTERNAL_REWRITING_RULES_READER_HH_

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

			class internal_rewriting_rules_reader
			{
				public:
					/**
					 * Creates a new reader for rewriting rules.
					 */
					internal_rewriting_rules_reader();
					virtual ~internal_rewriting_rules_reader();

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


				protected:
					/**
					 * Parses the node and returns the rule.
					 *
					 * @param node The XML node.
					 * @param namespace_map The namespace map.
					 * @param nsp The namespace.
					 * @return The rule.
					 */
					std::shared_ptr<decision_value<i_movement, std::vector<std::vector<std::shared_ptr<i_movement> > > > > read_rule(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp);

					/**
					 * Parses the node and returns the sequence for the rule.
					 *
					 * @param node The XML node.
					 * @param namespace_map The namespace map.
					 * @param nsp The namespace.
					 * @return The sequence.
					 */
					std::vector<std::shared_ptr<i_movement> > read_rule_sequence(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp);

					/**
					 * Parses the node and returns the movement element.
					 *
					 * @param node The XML node.
					 * @param namespace_map The namespace map.
					 * @param nsp The namespace.
					 * @return The movement element.
					 */
					std::shared_ptr<i_movement> read_element(xmlpp::Node* node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string nsp);



			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_INTERNAL_REWRITING_RULES_READER_HH_
