/*
 * mxml.cpp
 *
 *  Created on: 05.09.2014
 *      Author: keks
 */

#include "mxml.hpp"

//internal includes
//...

namespace mae
{

	std::string mxml::get_xpath(std::string element, std::string nsp)
	{
		std::stringstream sstr;

		std::vector<std::string> split = mstr::split(element, '/');

		for (unsigned int i = 0; i < split.size() ; i++)
		{
			if (i > 0)
			{
				sstr << "/";
			}

			if (nsp.size() > 0)
			{
				sstr << nsp << ":";
			}

			sstr << split.at(i);
		}

		return sstr.str();
	}

	std::string mxml::get_node_content(xmlpp::Node* parent_node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string element, std::string nsp, std::string default_return)
	{
		xmlpp::NodeSet node_set = parent_node->find(get_xpath(element, nsp), *namespace_map);

		std::string result = default_return;

		if (node_set.size() > 0)
		{
			xmlpp::Element* node = dynamic_cast<xmlpp::Element*>(node_set.at(0));

			if (node->has_child_text())
			{
				result = node->get_child_text()->get_content();
			}
			else
			{
				result = "";
			}
		}

		return result;
	}

	std::vector<std::string> mxml::get_node_contents(xmlpp::Node* parent_node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string element, std::string nsp, std::string default_return)
	{
		xmlpp::NodeSet node_set = parent_node->find(get_xpath(element, nsp), *namespace_map);

		std::vector<std::string> result;

		if (node_set.size() > 0)
		{
			for (unsigned int i = 0; i < node_set.size(); i++)
			{
				xmlpp::Element* node = dynamic_cast<xmlpp::Element*>(node_set.at(i));

				if (node->has_child_text())
				{
					result.push_back(node->get_child_text()->get_content());
				}
				else
				{
					result.push_back("");
				}
			}
		}
		else
		{
			result.push_back(default_return);
		}

		return result;
	}

	std::vector<std::string> mxml::get_node_contents(xmlpp::Node* parent_node, std::shared_ptr<xmlpp::Node::PrefixNsMap> namespace_map, std::string element, std::string nsp)
	{
		xmlpp::NodeSet node_set = parent_node->find(get_xpath(element, nsp), *namespace_map);

		std::vector<std::string> result;

		if (node_set.size() > 0)
		{
			for (unsigned int i = 0; i < node_set.size(); i++)
			{
				xmlpp::Element* node = dynamic_cast<xmlpp::Element*>(node_set.at(i));

				if (node->has_child_text())
				{
					result.push_back(node->get_child_text()->get_content());
				}
				else
				{
					result.push_back("");
				}
			}
		}

		return result;
	}

} // namespace mae
