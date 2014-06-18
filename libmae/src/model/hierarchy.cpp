/*
 * Hierarchy.cpp
 *
 *  Created on: 15.06.2014
 *      Author: keks
 */

#include "hierarchy.hpp"
#include "hierarchy_element.hpp"

namespace mae
{

	hierarchy::hierarchy()
	{
	}

	hierarchy::hierarchy(std::shared_ptr<hierarchy_element> root)
	{
		this->root = root;

		if (root)
		{
			root->set_parent(nullptr);
			//root->set_hierarchy(this);
		}
	}

	hierarchy::~hierarchy()
	{
		if (root)
		{
			root->set_hierarchy(nullptr);
		}
	}

	std::shared_ptr<hierarchy_element> hierarchy::get_root() const
	{
		return root;
	}

	void hierarchy::set_root(std::shared_ptr<hierarchy_element> root)
	{
		this->root = root;
		if (root)
		{
			root->set_parent(nullptr);
			root->set_hierarchy(this);
		}
	}

	std::vector<std::shared_ptr<hierarchy_element> > hierarchy::get_element_sequence()
	{
		std::vector<std::shared_ptr<hierarchy_element> > result;

		result.push_back(root);

		std::vector<std::shared_ptr<hierarchy_element> > roots_sequence = root->get_element_sequence();

		result.insert(result.end(), roots_sequence.begin(), roots_sequence.end());

		return result;
	}

	hierarchy_element * const hierarchy::at(int element_id) const
	{
		if (hashmap_elements.find(element_id) == hashmap_elements.end())
		{
			// returns nullpointer
			return nullptr;
		}
		else
		{
			// returns the element
			return hashmap_elements.at(element_id);
		}
	}

	std::shared_ptr<hierarchy> hierarchy::default_hierarchy()
	{
		std::shared_ptr<hierarchy> result;

		//TODO construct this one!
		std::shared_ptr<hierarchy_element> root = std::shared_ptr<hierarchy_element>(new hierarchy_element(MAEJ_TORSO, maej_str[MAEJ_TORSO], true));


		//dummy joints for torso split

		//dummy joints for end sites

		return result;
	}

	void hierarchy::add_element(hierarchy_element* element)
	{
		if (hashmap_elements.find(element->get_id()) == hashmap_elements.end())
		{
			//not in hashmap, therefore element will be added
			hashmap_elements.insert(std::make_pair(element->get_id(), element));
		}
	}

	void hierarchy::remove_element(hierarchy_element* element)
	{
		if (hashmap_elements.find(element->get_id()) != hashmap_elements.end())
		{
			//in hashmap, therefore element will be erased
			hashmap_elements.erase(element->get_id());
		}
	}

} // namespace mae
