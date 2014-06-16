/*
 * HierarchyElement.hpp
 *
 *  Created on: 15.06.2014
 *      Author: keks
 */

#ifndef HIERARCHYELEMENT_HPP_
#define HIERARCHYELEMENT_HPP_

//custom includes
//...

//global includes
#include <string>
#include <vector>
#include <memory>
#include <cstddef>

namespace mae
{

	class HierarchyElement
	{
		public:
			HierarchyElement(int id, std::string name);
			virtual ~HierarchyElement();

			virtual int get_id() const;
			virtual std::string get_name() const;

			virtual bool is_parent() const;
			virtual bool is_parent_of(int element_id) const;

			virtual std::vector<std::shared_ptr<HierarchyElement> > get_children();

			virtual void push_front(std::shared_ptr<HierarchyElement> child);
			virtual void add_child(unsigned int pos, std::shared_ptr<HierarchyElement> child);
			virtual void push_back(std::shared_ptr<HierarchyElement> child);

			virtual std::vector<std::shared_ptr<HierarchyElement> > get_element_sequence();

			/**
			 * Returns the shared pointer to the HierarchyElement that is the parent of the
			 * element with the given id. Returns a nullpointer if the element has no parent or
			 * is not found.
			 *
			 * Please note that the search starts with the children of this element and this
			 * element is not returned if it matches the search pattern.
			 *
			 * @param element_id The element's id.
			 * @return The HierarchyElement if found. Nullpointer otherwise.
			 */
			virtual std::shared_ptr<HierarchyElement> find_parent(int element_id);

			/**
			 * Returns the shared pointer to the HierarchyElement that is the first child of the
			 * element with the given id. Returns a nullpointer if the element has no children or
			 * is not found.
			 *
			 * @param element_id
			 * @return
			 */
			virtual std::shared_ptr<HierarchyElement> find_first_child(int element_id);

			/**
			 * Returns the shared pointer to the HierarchyElements that are the children of the
			 * element with the given id. Returns an empty vector if the element has no children
			 * or is not found.
			 *
			 *
			 * @param element_id
			 * @return The HierarchyElements if found. Empty vector otherwise.
			 */
			virtual std::vector<std::shared_ptr<HierarchyElement> > find_children(int element_id);

			/**
			 * Returns the shared pointer to the HierarchyElement that has the given id. Returns a
			 * nullpointer if the element has no parent or is not found.
			 *
			 * Please note that the search starts with the children of this element and this
			 * element is not returned if it matches the search pattern.
			 *
			 * @param element_id
			 * @return
			 */
			virtual std::shared_ptr<HierarchyElement> find_element(int element_id);

		private:
			int id;
			std::string name;
			std::vector<std::shared_ptr<HierarchyElement> > children;
	};

} // namespace mae

#endif // HIERARCHYELEMENT_HPP_
