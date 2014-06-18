/*
 * HierarchyElement.hpp
 *
 *  Created on: 15.06.2014
 *      Author: keks
 */

#ifndef HIERARCHYELEMENT_HPP_
#define HIERARCHYELEMENT_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
//#include "Hierarchy.hpp"

//global includes
#include <string>
#include <vector>
#include <memory>
#include <cstddef>

namespace mae
{
	//forward declaration of the hierarchy
	class Hierarchy;


	class HierarchyElement
	{
			friend class Hierarchy;

		public:
			/**
			 * Creates a new hierarchy element. Elements are defined by their id and
			 * have a name that is printed whenever needed (e.g. for bvh export).
			 *
			 * Please note that at least three torso joints must be defined in order
			 * to use the skeleton for the FL* motion controller.
			 *
			 *
			 * @param id
			 * @param name
			 * @param torso
			 * @param dummy
			 */
			HierarchyElement(int id, std::string name, bool torso_joint=false, bool dummy=false);
			virtual ~HierarchyElement();

			virtual int get_id() const;
			virtual std::string get_name() const;

			/**
			 * Returns the torso joint property of the element. If torso joint is set
			 * this joint is part of the torso.
			 *
			 * @return
			 */
			virtual bool is_torso_joint() const;
			virtual bool is_dummy() const;

			virtual HierarchyElement * const get_parent() const;

			virtual bool is_parent() const;
			virtual bool is_parent_of(int element_id) const;

			virtual std::vector<std::shared_ptr<HierarchyElement> > get_children() const;

			virtual void push_front(std::shared_ptr<HierarchyElement> child);
			virtual void add_child(unsigned int pos, std::shared_ptr<HierarchyElement> child);
			virtual void push_back(std::shared_ptr<HierarchyElement> child);

			virtual void erase(int element_id);
			virtual void erase_at(unsigned int i);
			virtual void clear();

			virtual std::vector<std::shared_ptr<HierarchyElement> > get_element_sequence();

		protected:
			/**
			 * Sets the parent of this element. This is done automatically when
			 * children are assigned to an element.
			 *
			 * @param parent A shared pointer to the parent.
			 */
			virtual void set_parent(HierarchyElement * const parent, bool fix_parent = true);

			/**
			 * Sets the root hierarchy of this element. This is done automatically
			 * when an element is assigned to a hierarchy.
			 *
			 * @param hierarchy
			 */
			virtual void set_hierarchy(Hierarchy * const  hierarchy);

		private:
			int id;
			std::string name;
			bool dummy;
			bool torso_joint;

			std::vector<std::shared_ptr<HierarchyElement> > children;

			HierarchyElement* parent;
			Hierarchy* hierarchy;
	};

} // namespace mae

#endif // HIERARCHYELEMENT_HPP_
