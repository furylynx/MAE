/*
 * Hierarchy.hpp
 *
 *  Created on: 15.06.2014
 *      Author: keks
 */

#ifndef HIERARCHY_HPP_
#define HIERARCHY_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
//#include "HierarchyElement.hpp"

//global includes
#include <vector>
#include <memory>
#include <unordered_map>

namespace mae
{
	//forward declaration of the hierarchy element
	class HierarchyElement;


	class Hierarchy
	{
			friend class HierarchyElement;

		public:
			Hierarchy();
			Hierarchy(std::shared_ptr<HierarchyElement> root);
			virtual ~Hierarchy();

			virtual std::shared_ptr<HierarchyElement> get_root() const;
			virtual void set_root(std::shared_ptr<HierarchyElement> root);

			virtual std::vector<std::shared_ptr<HierarchyElement> > get_element_sequence();

			virtual HierarchyElement * const at(int element_id) const;

			static std::shared_ptr<Hierarchy> default_hierarchy();

		protected:
			/**
			 * Adds a new element to the elements hashmap in order to provide fast access to
			 * the elements. This method is invoked automatically from the HierarchyElement.
			 *
			 * @param element The element to be added.
			 */
			virtual void add_element(HierarchyElement * const element);

			/**
			 * Removes an element from the elements hashmap in order to provide fast access to
			 * the elements. This method is invoked automatically from the HierarchyElement.
			 *
			 * @param element The element to be removed
			 */
			virtual void remove_element(HierarchyElement * const element);

		private:
			std::shared_ptr<HierarchyElement> root;

			std::unordered_map<int, HierarchyElement * const> hashmap_elements;

	};

} // namespace mae

#endif // HIERARCHY_HPP_
