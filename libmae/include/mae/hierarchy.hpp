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
#include "e_kinect_joint.hpp"


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
			virtual std::vector<std::shared_ptr<hierarchy_element> > get_element_sequence() const;

			/**
			 * Returns the sorted element sequence containing all elements of this hierarchy.
			 * The sequence is sorted by the element's IDs.
			 *
			 * @return The sorted sequence.
			 */
			std::vector<std::shared_ptr<hierarchy_element> > get_sorted_element_sequence() const;

			/**
			 * Returns the element with the given id. This is done in constant time.
			 *
			 * @param element_id The element's id.
			 * @return A plain pointer to the element.
			 */
			virtual hierarchy_element * const at(int element_id) const;

			/**
			 * Compares the two hierarchy_elements.
			 *
			 * @param lhs The first element.
			 * @param rhs The second element.
			 *
			 * @return True if lhs is less than rhs.
			 */
			static bool compare_elements(const std::shared_ptr<hierarchy_element> &lhs, const std::shared_ptr<hierarchy_element> &rhs);


			/**
			 * Returns a string that represents the hierarchy containing all elements.
			 *
			 * @return The string representation.
			 */
			virtual std::string str() const;

			/**
			 * Returns a default hierarchy that fits the needs of the OpenNI/NiTE skeletons.
			 * If none of the default hierarchies is sufficient and/or another hierarchy is
			 * needed it must be constructed manually.
			 *
			 * @return The default hierarchy.
			 */
			static std::shared_ptr<hierarchy> default_hierarchy();

			/**
			 * Returns a default hierarchy that fits the needs of the Kinect SDK skeletons.
			 * If none of the default hierarchies is sufficient and/or another hierarchy is
			 * needed it must be constructed manually.
			 *
			 * @return The default kinect skeleton.
			 */
			static std::shared_ptr<hierarchy> default_kinect_hierarchy();


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
