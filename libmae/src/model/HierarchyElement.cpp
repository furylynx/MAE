/*
 * HierarchyElement.cpp
 *
 *  Created on: 15.06.2014
 *      Author: keks
 */

#include "HierarchyElement.hpp"
#include "Hierarchy.hpp"

namespace mae
{

	HierarchyElement::HierarchyElement(int id, std::string name, std::string bone_name)
	{
		this->id = id;
		this->name = name;
		this->bone_name = bone_name;

		this->parent = nullptr;
		this->hierarchy = nullptr;
	}

	HierarchyElement::~HierarchyElement()
	{
		//reset parent of children and hierarchy
		for (unsigned int i = 0; i < children.size(); i++)
		{
			children.at(i)->set_parent(nullptr);

			if (hierarchy)
			{
				//update hierarchy
				children.at(i)->set_hierarchy(nullptr);
			}
		}
	}

	int HierarchyElement::get_id() const
	{
		return id;
	}

	std::string HierarchyElement::get_name() const
	{
		return name;
	}

	std::string HierarchyElement::get_bone_name() const
	{
		return bone_name;
	}

	HierarchyElement * const HierarchyElement::get_parent() const
	{
		return parent;
	}

	bool HierarchyElement::is_parent() const
	{
		return !children.empty();
	}

	bool HierarchyElement::is_parent_of(int element_id) const
	{
		for (unsigned int i = 0; i < children.size(); i++)
		{
			if (element_id == children.at(i)->get_id())
			{
				return true;
			}
		}

		return false;
	}

	std::vector<std::shared_ptr<HierarchyElement> > HierarchyElement::get_children() const
	{
		return children;
	}

	void HierarchyElement::push_front(std::shared_ptr<HierarchyElement> child)
	{
		children.insert(children.begin(), child);

		//assign parent and hierarchy
		child->set_parent(this, false);

	}

	void HierarchyElement::add_child(unsigned int pos, std::shared_ptr<HierarchyElement> child)
	{
		children.insert(children.begin() + pos, child);

		//assign parent and hierarchy
		child->set_parent(this, false);
	}

	void HierarchyElement::push_back(std::shared_ptr<HierarchyElement> child)
	{
		children.push_back(child);

		//assign parent and hierarchy
		child->set_parent(this, false);
	}

	void HierarchyElement::erase(int element_id)
	{
		for (unsigned int i = 0; i < children.size(); i++)
		{
			if (children.at(i)->get_id() == element_id)
			{
				erase_at(i);
			}
		}
	}

	void HierarchyElement::erase_at(unsigned int i)
	{
		if (i < children.size())
		{
			children.at(i)->set_parent(nullptr, false);
			children.erase(children.begin() + i);
		}
	}

	void HierarchyElement::clear()
	{
		for (unsigned int i = 0; i < children.size(); i++)
		{
			children.at(i)->set_parent(nullptr, false);
		}

		children.clear();
	}

	std::vector<std::shared_ptr<HierarchyElement> > HierarchyElement::get_element_sequence()
	{
		std::vector<std::shared_ptr<HierarchyElement> > result;

		for (unsigned int i = 0; i < children.size(); i++)
		{
			result.push_back(children.at(i));

			std::vector<std::shared_ptr<HierarchyElement> > childrens_sequence = children.at(i)->get_element_sequence();
			result.insert(result.end(), childrens_sequence.begin(), childrens_sequence.end());
		}

		return result;
	}

	void HierarchyElement::set_parent(HierarchyElement * const parent, bool fix_parent)
	{
		if (this->parent == parent)
		{
			return;
		}

		HierarchyElement* former_parent = this->parent;

		this->parent = parent;

		if (this->hierarchy && this->hierarchy->get_root().get() == this)
		{
			//this element is assigned to a hierarchy
			//therefore the root of the old hierarchy must be
			//cleared
			hierarchy->set_root(std::shared_ptr<HierarchyElement>());
		}

		if (former_parent && fix_parent)
		{
			//remove this element from the former parent
			former_parent->erase(id);
		}

		//update hierarchy
		if (!parent)
		{
			set_hierarchy(nullptr);
		}
		else if (parent->hierarchy != this->hierarchy)
		{
			//update hierarchy to parent's one
			set_hierarchy(parent->hierarchy);
		}

	}

	void HierarchyElement::set_hierarchy(Hierarchy * const hierarchy)
	{
		if (this->hierarchy == hierarchy)
		{
			return;
		}

		Hierarchy* former_hierarchy = this->hierarchy;

		if (former_hierarchy && former_hierarchy->get_root().get() == this)
		{
			//this element is assigned to another hierarchy
			//therefore the root of the old hierarchy must be
			//cleared
			former_hierarchy->set_root(std::shared_ptr<HierarchyElement>());
		}

		//update former hierarchy
		former_hierarchy->remove_element(this);

		this->hierarchy = hierarchy;

		//update new hierarchy
		hierarchy->add_element(this);

		//update children, too
		for (unsigned int i = 0; i < children.size(); i++)
		{
			children.at(i)->set_hierarchy(hierarchy);
		}
	}

} // namespace mae
