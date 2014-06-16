/*
 * Hierarchy.hpp
 *
 *  Created on: 15.06.2014
 *      Author: keks
 */

#ifndef HIERARCHY_HPP_
#define HIERARCHY_HPP_

//custom includes
#include "HierarchyElement.hpp"

//global includes
#include <vector>
#include <memory>

namespace mae
{

	class Hierarchy
	{
		public:
			Hierarchy();
			Hierarchy(std::shared_ptr<HierarchyElement> root);
			virtual ~Hierarchy();

			virtual std::shared_ptr<HierarchyElement> get_root();
			virtual void set_root(std::shared_ptr<HierarchyElement> root);

			virtual std::vector<std::shared_ptr<HierarchyElement> > get_element_sequence();
			virtual std::shared_ptr<HierarchyElement> find_parent(int element_id);
			virtual std::shared_ptr<HierarchyElement> find_first_child(int element_id);
			virtual std::vector<std::shared_ptr<HierarchyElement> > find_children(int element_id);
			virtual std::shared_ptr<HierarchyElement> find_element(int element_id);

		private:
			std::shared_ptr<HierarchyElement> root;
	};

} // namespace mae

#endif // HIERARCHY_HPP_
