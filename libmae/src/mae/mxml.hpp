/*
 * mxml.hpp
 *
 *  Created on: 05.09.2014
 *      Author: keks
 */

#ifndef MXML_HPP_
#define MXML_HPP_

//eclipse indexer fix
#include "indexer_fix.hpp"

//custom includes
#include "mstr.hpp"

//global includes
#include <string>
#include <sstream>
#include <memory>
#include <vector>

#include <libxml++/libxml++.h>

namespace mae
{
	class mxml
	{
		public:

			/**
			 * Returns the correct xpath.
			 *
			 * @param element The element to be prefixed.
			 * @param nsp The namespace
			 * @return The xpath.
			 */
			static std::string get_xpath(std::string element, std::string nsp = "");

			/**
			 * Returns the content of a node if it can be found. Returns the default_return parameter otherwise.
			 *
			 * @param parent_node The parent node from which the lookup will start.
			 * @param namespace_map The namespace map containing all namespaces.
			 * @param element The element to be looked for.
			 * @param nsp The namespace of the element.
			 * @param default_return The default return value used if no node is found.
			 * @return The node's content or the default return value.
			 */
			static std::string get_node_content(xmlpp::Node* parent_node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string element, std::string nsp, std::string default_return);

			/**
			 * Returns the contents of all found nodes if any. Returns the default_return parameter otherwise.
			 *
			 * @param parent_node The parent node from which the lookup will start.
			 * @param namespace_map The namespace map containing all namespaces.
			 * @param element The elements name to be looked for.
			 * @param nsp The namespace of the element.
			 * @param default_return The default return value used if no node is found.
			 * @return The node's content or the default return value.
			 */
			static std::vector<std::string> get_node_contents(xmlpp::Node* parent_node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string element, std::string nsp, std::string default_return);

	};

} // namespace mae

#endif // MXML_HPP_
