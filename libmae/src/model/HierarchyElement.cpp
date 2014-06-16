/*
 * HierarchyElement.cpp
 *
 *  Created on: 15.06.2014
 *      Author: keks
 */

#include "HierarchyElement.hpp"

namespace mae
{

	HierarchyElement::HierarchyElement(int id, std::string name)
	{
		this->id = id;
		this->name = name;
	}

	HierarchyElement::~HierarchyElement()
	{
		children.clear();
	}

	int HierarchyElement::get_id() const
	{
		return id;
	}

	std::string HierarchyElement::get_name() const
	{
		return name;
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

	std::vector<std::shared_ptr<HierarchyElement> > HierarchyElement::get_children()
	{
		return children;
	}

	void HierarchyElement::push_front(std::shared_ptr<HierarchyElement> child)
	{
		children.insert(children.begin(), child);
	}

	void HierarchyElement::add_child(unsigned int pos, std::shared_ptr<HierarchyElement> child)
	{
		children.insert(children.begin() + pos, child);
	}

	void HierarchyElement::push_back(std::shared_ptr<HierarchyElement> child)
	{
		children.push_back(child);
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

	std::shared_ptr<HierarchyElement> HierarchyElement::find_parent(int element_id)
	{
		if (children.empty())
		{
			//return null pointer
			std::shared_ptr<HierarchyElement>();
		}

		for (unsigned int i = 0; i < children.size(); i++)
		{
			if (children.at(i)->is_parent_of(element_id))
			{
				return children.at(i);
			}
		}

		for (unsigned int i = 0; i < children.size(); i++)
		{
			std::shared_ptr<HierarchyElement> element = children.at(i)->find_parent(element_id);

			if (element)
			{
				return element;
			}
		}

		//return null pointer
		return std::shared_ptr<HierarchyElement>();
	}

	std::shared_ptr<HierarchyElement> HierarchyElement::find_first_child(int element_id)
	{
		if (children.empty())
		{
			//return nullpointer
			return std::shared_ptr<HierarchyElement>();
		}

		if (id == element_id)
		{
			return children.at(0);
		}

		for (unsigned int i = 0; i < children.size(); i++)
		{
			std::shared_ptr<HierarchyElement> element =
					((std::shared_ptr<HierarchyElement>) children.at(i))->find_first_child(element_id);

			if (element)
			{
				return element;
			}
		}

		//return nullpointer
		return std::shared_ptr<HierarchyElement>();
	}

	std::vector<std::shared_ptr<HierarchyElement> > HierarchyElement::find_children(int element_id)
	{
		if (children.empty())
		{
			//return null pointer
			return std::vector<std::shared_ptr<HierarchyElement> >();
		}

		if (id == element_id)
		{
			return children;
		}

		for (unsigned int i = 0; i < children.size(); i++)
		{
			std::vector<std::shared_ptr<HierarchyElement> > elements = children[i]->find_children(element_id);

			if (!elements.empty())
			{
				return elements;
			}
		}

		//return null pointer
		return std::vector<std::shared_ptr<HierarchyElement> >();
	}

	std::shared_ptr<HierarchyElement> HierarchyElement::find_element(int element_id)
	{
		if (children.empty())
		{
			//return nullpointer
			std::shared_ptr<HierarchyElement>();
		}

		for (unsigned int i = 0; i < children.size(); i++)
		{
			if (children.at(i)->get_id() == element_id)
			{
				return children.at(i);
			}
		}

		for (unsigned int i = 0; i < children.size(); i++)
		{
			std::shared_ptr<HierarchyElement> element = children.at(i)->find_element(element_id);

			if (element)
			{
				return element;
			}
		}

		//return nullpointer
		return std::shared_ptr<HierarchyElement>();
	}

} // namespace mae
