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
#include "maej.hpp"

//this is forwarded
//#include "HierarchyElement.hpp"


//global includes
#include <vector>
#include <memory>
#include <unordered_map>

namespace mae
{
	//forward declaration of the hierarchy element
	class hierarchy_element;


	class hierarchy
	{
			friend class hierarchy_element;

		public:
			hierarchy();
			hierarchy(std::shared_ptr<hierarchy_element> root);
			virtual ~hierarchy();

			virtual std::shared_ptr<hierarchy_element> get_root() const;
			virtual void set_root(std::shared_ptr<hierarchy_element> root);

			virtual std::vector<std::shared_ptr<hierarchy_element> > get_element_sequence();

			virtual hierarchy_element * const at(int element_id) const;

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

			std::unordered_map<int, hierarchy_element * const> hashmap_elements;

	};

} // namespace mae

#endif // HIERARCHY_HPP_
