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
			children.at(i)->update_ph(nullptr, nullptr, false, false);
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

	bool hierarchy_element::is_torso_joint() const
	{
		return torso_joint;
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

	void hierarchy_element::push_front(std::shared_ptr<hierarchy_element> child, bool fix_child)
	{
		children.insert(children.begin(), child);

		//assign parent and hierarchy
		child->update_ph(this, hierarchy_, false, true);

	}

	void hierarchy_element::insert(unsigned int pos, std::shared_ptr<hierarchy_element> child, bool fix_child)
	{
		children.insert(children.begin() + pos, child);

		//assign parent and hierarchy
		child->update_ph(this, hierarchy_, false, true);
	}

	void hierarchy_element::push_back(std::shared_ptr<hierarchy_element> child, bool fix_child)
	{
		children.push_back(child);

		if (fix_child)
		{
			//assign parent and hierarchy
			child->update_ph(this, hierarchy_, false, true);
		}
	}

	void hierarchy_element::erase(int element_id, bool fix_child)
	{
		for (unsigned int i = 0; i < children.size(); i++)
		{
			if (children.at(i)->get_id() == element_id)
			{
				erase_at(i, fix_child);
			}
		}
	}

	void hierarchy_element::erase_at(unsigned int i, bool fix_child)
	{
		if (i < children.size())
		{
			if (fix_child)
			{
				children.at(i)->update_ph(nullptr, nullptr, false, false);
			}
			children.erase(children.begin() + i);
		}
	}

	void hierarchy_element::clear(bool fix_child)
	{
		if (fix_child)
		{
			for (unsigned int i = 0; i < children.size(); i++)
			{
				children.at(i)->update_ph(nullptr, nullptr, false, false);
			}
		}

		children.clear();
	}

	std::vector<std::shared_ptr<hierarchy_element> > hierarchy_element::get_element_sequence()
	{
		std::vector<std::shared_ptr<hierarchy_element> > result;

		for (unsigned int i = 0; i < children.size(); i++)
		{
			result.push_back(children.at(i));

			std::vector<std::shared_ptr<hierarchy_element> > childrens_sequence =
					children.at(i)->get_element_sequence();
			result.insert(result.end(), childrens_sequence.begin(), childrens_sequence.end());
		}

		return result;
	}

	std::string hierarchy_element::str(int offset) const
	{
		std::stringstream sstr;

		for (int i = 0; i < offset; i++)
		{
			sstr << "\t";
		}

		sstr << name;
		sstr << " (" << id << ")";

		if (dummy)
		{
			sstr << " #DUMMY_JOINT";
		}

		if (torso_joint)
		{
			sstr << " #TORSO_JOINT";
		}

		sstr << std::endl;

		for (unsigned int i = 0; i < children.size(); i++)
		{
			sstr << children.at(i)->str(offset + 1);
		}

		return sstr.str();
	}

	void hierarchy_element::update_ph(hierarchy_element * const parent, hierarchy * const h, bool fix_parent,
			bool fix_former_h)
	{
		if (this->parent != parent)
		{
			hierarchy_element* former_parent = this->parent;

			this->parent = parent;

			if (h && h->get_root().get() == this)
			{
				//this element is assigned to a hierarchy
				//therefore the root of the old hierarchy must be
				//cleared
				h->set_root(std::shared_ptr<hierarchy_element>());
			}

			if (former_parent && fix_parent)
			{
				//remove this element from the former parent
				former_parent->erase(id, false);
			}
		}

		if (hierarchy_ != h)
		{
			hierarchy* former_h = hierarchy_;

			if (fix_former_h && former_h && former_h->get_root().get() == this)
			{
				//this element is assigned to another hierarchy
				//therefore the root of the old hierarchy must be
				//cleared
				former_h->set_root(std::shared_ptr<hierarchy_element>());
			}

			if (fix_former_h && former_h)
			{
				//update former hierarchy
				former_h->remove_element(this);
			}

			hierarchy_ = h;

			if (hierarchy_)
			{
				//update new hierarchy
				hierarchy_->add_element(this);
			}

			for (unsigned int i = 0; i < children.size(); i++)
			{
				children.at(i)->update_ph(this, hierarchy_, false, false);
			}
		}

	}

	hierarchy * const hierarchy_element::get_hierarchy() const
	{
		return hierarchy_;
	}

} // namespace mae
