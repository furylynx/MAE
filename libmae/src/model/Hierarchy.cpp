/*
 * Hierarchy.cpp
 *
 *  Created on: 15.06.2014
 *      Author: keks
 */

#include "Hierarchy.hpp"

namespace mae
{

	Hierarchy::Hierarchy()
	{
		// TODO Auto-generated constructor stub

	}

	Hierarchy::Hierarchy(std::shared_ptr<HierarchyElement> root)
	{
		this->root = root;
	}

	Hierarchy::~Hierarchy()
	{
		// TODO Auto-generated destructor stub
	}

	std::shared_ptr<HierarchyElement> Hierarchy::get_root()
	{
		return root;
	}

	virtual void Hierarchy::set_root(std::shared_ptr<HierarchyElement> root)
	{
		this->root = root;
	}

	std::vector<std::shared_ptr<HierarchyElement> > Hierarchy::get_element_sequence()
	{
		std::vector<std::shared_ptr<HierarchyElement> > result;

		result.push_back(root);

		std::vector<std::shared_ptr<HierarchyElement> > roots_sequence = root->get_element_sequence();

		result.insert(result.end(), roots_sequence.begin(), roots_sequence.end());

		return result;
	}

	std::shared_ptr<HierarchyElement> Hierarchy::find_parent(int element_id)
	{
		if (root->is_parent_of(element_id))
		{
			return root;
		}
		else
		{
			return root->find_parent(element_id);
		}

	}

	std::shared_ptr<HierarchyElement> Hierarchy::find_first_child(int element_id)
	{
		return root->find_first_child(element_id);
	}

	std::vector<std::shared_ptr<HierarchyElement> > Hierarchy::find_children(int element_id)
	{
		return root->find_children(element_id);
	}

	std::shared_ptr<HierarchyElement> Hierarchy::find_element(int element_id)
	{
		if (root->get_id() == element_id)
		{
			return root;
		}
		else
		{
			return root->find_element(element_id);
		}
	}

} // namespace mae
