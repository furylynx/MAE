/*
 * Hierarchy.cpp
 *
 *  Created on: 15.06.2014
 *      Author: keks
 */

#include "Hierarchy.hpp"
#include "HierarchyElement.hpp"

namespace mae
{

	Hierarchy::Hierarchy()
	{
	}

	Hierarchy::Hierarchy(std::shared_ptr<HierarchyElement> root)
	{
		this->root = root;

		if (root)
		{
			root->set_parent(nullptr);
			//root->set_hierarchy(this);
		}
	}

	Hierarchy::~Hierarchy()
	{
		if (root)
		{
			root->set_hierarchy(nullptr);
		}
	}

	std::shared_ptr<HierarchyElement> Hierarchy::get_root() const
	{
		return root;
	}

	void Hierarchy::set_root(std::shared_ptr<HierarchyElement> root)
	{
		this->root = root;
		if (root)
		{
			root->set_parent(nullptr);
			//root->set_hierarchy(this);
		}
	}

	std::vector<std::shared_ptr<HierarchyElement> > Hierarchy::get_element_sequence()
	{
		std::vector<std::shared_ptr<HierarchyElement> > result;

		result.push_back(root);

		std::vector<std::shared_ptr<HierarchyElement> > roots_sequence = root->get_element_sequence();

		result.insert(result.end(), roots_sequence.begin(), roots_sequence.end());

		return result;
	}

	HierarchyElement * const Hierarchy::at(int element_id) const
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

	std::shared_ptr<Hierarchy> Hierarchy::default_hierarchy()
	{
		std::shared_ptr<Hierarchy> result;

		//TODO construct this one!

		//dummy joints for torso split

		//dummy joints for end sites

		return result;
	}

	void Hierarchy::add_element(HierarchyElement* element)
	{
		if (hashmap_elements.find(element->get_id()) == hashmap_elements.end())
		{
			//not in hashmap, therefore element will be added
			hashmap_elements.insert(std::make_pair(element->get_id(), element));
		}
	}

	void Hierarchy::remove_element(HierarchyElement* element)
	{
		if (hashmap_elements.find(element->get_id()) != hashmap_elements.end())
		{
			//in hashmap, therefore element will be erased
			hashmap_elements.erase(element->get_id());
		}
	}

} // namespace mae
