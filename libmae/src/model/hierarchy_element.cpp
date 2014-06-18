/*
 * HierarchyElement.cpp
 *
 *  Created on: 15.06.2014
 *      Author: keks
 */

#include "hierarchy_element.hpp"
#include "hierarchy.hpp"

namespace mae
{

	hierarchy_element::hierarchy_element(int id, std::string name, bool torso_joint, bool dummy)
	{
		this->id = id;
		this->name = name;
		this->torso_joint = torso_joint;
		this->dummy = dummy;

		this->parent = nullptr;
		this->hierarchy_ = nullptr;
	}

	hierarchy_element::~hierarchy_element()
	{
		//reset parent of children and hierarchy
		for (unsigned int i = 0; i < children.size(); i++)
		{
			children.at(i)->set_parent(nullptr);

			if (hierarchy_)
			{
				//update hierarchy
				children.at(i)->set_hierarchy(nullptr);
			}
		}
	}

	int hierarchy_element::get_id() const
	{
		return id;
	}

	std::string hierarchy_element::get_name() const
	{
		return name;
	}

	bool hierarchy_element::is_dummy() const
	{
		return dummy;
	}

	hierarchy_element * const hierarchy_element::get_parent() const
	{
		return parent;
	}

	bool hierarchy_element::is_parent() const
	{
		return !children.empty();
	}

	bool hierarchy_element::is_parent_of(int element_id) const
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

	std::vector<std::shared_ptr<hierarchy_element> > hierarchy_element::get_children() const
	{
		return children;
	}

	void hierarchy_element::push_front(std::shared_ptr<hierarchy_element> child)
	{
		children.insert(children.begin(), child);

		//assign parent and hierarchy
		child->set_parent(this, false);

	}

	void hierarchy_element::add_child(unsigned int pos, std::shared_ptr<hierarchy_element> child)
	{
		children.insert(children.begin() + pos, child);

		//assign parent and hierarchy
		child->set_parent(this, false);
	}

	void hierarchy_element::push_back(std::shared_ptr<hierarchy_element> child)
	{
		children.push_back(child);

		//assign parent and hierarchy
		child->set_parent(this, false);
	}

	void hierarchy_element::erase(int element_id)
	{
		for (unsigned int i = 0; i < children.size(); i++)
		{
			if (children.at(i)->get_id() == element_id)
			{
				erase_at(i);
			}
		}
	}

	void hierarchy_element::erase_at(unsigned int i)
	{
		if (i < children.size())
		{
			children.at(i)->set_parent(nullptr, false);
			children.erase(children.begin() + i);
		}
	}

	void hierarchy_element::clear()
	{
		for (unsigned int i = 0; i < children.size(); i++)
		{
			children.at(i)->set_parent(nullptr, false);
		}

		children.clear();
	}

	std::vector<std::shared_ptr<hierarchy_element> > hierarchy_element::get_element_sequence()
	{
		std::vector<std::shared_ptr<hierarchy_element> > result;

		for (unsigned int i = 0; i < children.size(); i++)
		{
			result.push_back(children.at(i));

			std::vector<std::shared_ptr<hierarchy_element> > childrens_sequence = children.at(i)->get_element_sequence();
			result.insert(result.end(), childrens_sequence.begin(), childrens_sequence.end());
		}

		return result;
	}

	void hierarchy_element::set_parent(hierarchy_element * const parent, bool fix_parent)
	{
		if (this->parent == parent)
		{
			return;
		}

		hierarchy_element* former_parent = this->parent;

		this->parent = parent;

		if (this->hierarchy_ && this->hierarchy_->get_root().get() == this)
		{
			//this element is assigned to a hierarchy
			//therefore the root of the old hierarchy must be
			//cleared
			hierarchy_->set_root(std::shared_ptr<hierarchy_element>());
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
		else if (parent->get_hierarchy() != this->hierarchy_)
		{
			//update hierarchy to parent's one
			set_hierarchy(parent->hierarchy_);
		}

	}

	void hierarchy_element::set_hierarchy(hierarchy * const h)
	{
		if (this->hierarchy_ == h)
		{
			return;
		}

		hierarchy* former_h = this->hierarchy_;

		if (former_h && former_h->get_root().get() == this)
		{
			//this element is assigned to another hierarchy
			//therefore the root of the old hierarchy must be
			//cleared
			former_h->set_root(std::shared_ptr<hierarchy_element>());
		}

		//update former hierarchy
		former_h->remove_element(this);

		this->hierarchy_ = h;

		//update new hierarchy
		hierarchy_->add_element(this);

		//update children, too
		for (unsigned int i = 0; i < children.size(); i++)
		{
			children.at(i)->set_hierarchy(hierarchy_);
		}
	}

	hierarchy * const hierarchy_element::get_hierarchy() const
	{
		return hierarchy_;
	}

} // namespace mae
