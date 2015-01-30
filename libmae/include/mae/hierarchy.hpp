/*
 * Hierarchy.hpp
 *
 *  Created on: 15.06.2014
 *      Author: keks
 */

#ifndef HIERARCHY_HPP_
#define HIERARCHY_HPP_

//eclipse indexer fix
#include "indexer_fix.hpp"

//custom includes
#include "e_joint.hpp"


//global includes
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <iostream>

namespace mae
{
	//forward declaration of the hierarchy element
	class hierarchy_element;

	class hierarchy
	{
			friend class hierarchy_element;

		public:
			/**
			 * Creates a new empty hierarchy.
			 */
			hierarchy();

			/**
			 * Creates a new hierarchy giving the root of elements.
			 *
			 * @param root The root which is (in-)direct parent of all elements.
			 */
			hierarchy(std::shared_ptr<hierarchy_element> root);

			/**
			 * Destructs this element and fixes the root (hierarchy).
			 */
			virtual ~hierarchy();

			/**
			 * Returns a shared pointer to the root element.
			 *
			 * @return The root element.
			 */
			virtual std::shared_ptr<hierarchy_element> get_root() const;

			/**
			 * Sets the root element. Fixes the former root's hierarchy if existing.
			 *
			 * @param root A shared pointer to new root element.
			 */
			virtual void set_root(std::shared_ptr<hierarchy_element> root);

			/**
			 * Returns the element sequence containing all elements of this hierarchy.
			 *
			 * @return The sequence.
			 */
			virtual std::vector<std::shared_ptr<hierarchy_element> > get_element_sequence();

			/**
			 * Returns the element with the given id. This is done in constant time.
			 *
			 * @param element_id The element's id.
			 * @return A plain pointer to the element.
			 */
			virtual hierarchy_element * const at(int element_id) const;

			/**
			 * Returns a string that represents the hierarchy containing all elements.
			 *
			 * @return The string representation.
			 */
			virtual std::string str() const;

			/**
			 * Returns a default hierarchy that fits the needs of the OpenNI/NiTE skeletons.
			 * If the OpenNI/NiTE hierarchy is not sufficient and/or another hierarchy is
			 * needed it must be constructed manually.
			 *
			 * @return The default hierarchy.
			 */
			static std::shared_ptr<hierarchy> default_hierarchy();

		protected:
			/**
			 * Adds a new element to the elements hashmap in order to provide fast access to
			 * the elements. This method is invoked automatically from the HierarchyElement.
			 *
			 * @param element The element to be added.
			 */
			virtual void add_element(hierarchy_element * const element);

			/**
			 * Removes an element from the elements hashmap in order to provide fast access to
			 * the elements. This method is invoked automatically from the HierarchyElement.
			 *
			 * @param element The element to be removed
			 */
			virtual void remove_element(hierarchy_element * const element);

		private:
			std::shared_ptr<hierarchy_element> root;

			std::unordered_map<int, hierarchy_element * const > hashmap_elements;

	};

} // namespace mae

#endif // HIERARCHY_HPP_
