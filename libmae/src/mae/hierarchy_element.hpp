#ifndef HIERARCHYELEMENT_HPP_
#define HIERARCHYELEMENT_HPP_

//custom includes
//#include "Hierarchy.hpp"

//global includes
#include <string>
#include <vector>
#include <memory>
#include <sstream>

namespace mae
{
	//forward declaration of the hierarchy
	class hierarchy;

	class hierarchy_element
	{
			friend class hierarchy;

		public:
			/**
			 * Creates a new hierarchy element. Elements are defined by their id and
			 * have a name that is printed whenever needed (e.g. for bvh export).
			 *
			 * Please note that at least three (correlated) base joints must be defined in order
			 * to use the skeleton for the FL* motion controller.
			 *
			 *
			 * @param id The id of the element.
			 * @param name The name of the element.
			 * @param base_joint True if the joint is a base joint (part of a system of reference, e.g. the torso or palm).
			 * @param dummy True if the joint is a dummy joint.
			 */
			hierarchy_element(int id, std::string name, bool base_joint = false, bool dummy = false);

			/**
			 * Destructs this element and fixes its children (parent and hierarchy).
			 */
			virtual ~hierarchy_element();

			/**
			 * Returns the id of this element.
			 *
			 * @return The id of this element.
			 */
			virtual int get_id() const;

			/**
			 * Returns the name of this element.
			 *
			 * @return The name.
			 */
			virtual std::string get_name() const;

			/**
			 * Returns the base joint (formerly called torso joint) property of the element. If base joint is set
			 * this joint is part of the basis (e.g. the torso, the palm or any other system of reference).
			 *
			 * @return True if this is a base joint (formerly called torso joint). False otherwise.
			 */
			//[[deprecated("Replaced by is_base_joint()")]]
			virtual bool is_torso_joint() const;

			/**
			 * Returns the base joint property of the element. If base joint is set
			 * this joint is part of the basis (e.g. the torso, the palm or any other system of reference).
			 *
			 * @return True if this is a base joint. False otherwise.
			 */
			virtual bool is_base_joint() const;

			/**
			 * Returns the dummy property of this element. If the joint is a dummy joint
			 * it has not offset to its parent and will be used for the bvh export in order
			 * to preserve the names of the joints and the rotations.
			 *
			 * @return True if this joint is a dummy. False otherwise.
			 */
			virtual bool is_dummy() const;

			/**
			 * Returns a plain pointer to the parent of this element.
			 *
			 * @return The parent.
			 */
			virtual hierarchy_element * const get_parent() const;

			/**
			 * Returns true if this element is a parent of another element.
			 *
			 * @return True if this is a parent.
			 */
			virtual bool is_parent() const;

			/**
			 * Returns true if this element is the parent of the given element.
			 *
			 * @param element_id The id of the potential child element.
			 * @return True if this is the parent of the element.
			 */
			virtual bool is_parent_of(int element_id) const;

			/**
			 * Returns a vector of shared pointers to the children.
			 *
			 * @return All children.
			 */
			virtual std::vector<std::shared_ptr<hierarchy_element> > get_children() const;

			/**
			 * Adds a child to this element in front of all other children.
			 *
			 * @param child The child to be added.
			 * @param fix_child True if the child's parent shall be set to this element.
			 */
			virtual void push_front(std::shared_ptr<hierarchy_element> child, bool fix_child = true);

			/**
			 * Adds a child to this element at the given position.
			 *
			 * @param child The child to be added.
			 * @param fix_child True if the child's parent shall be set to this element.
			 */
			virtual void insert(unsigned int pos, std::shared_ptr<hierarchy_element> child, bool fix_child = true);

			/**
			 * Adds a child to this element at the back of all other children.
			 *
			 * @param child The child to be added.
			 * @param fix_child True if the child's parent shall be set to this element.
			 */
			virtual void push_back(std::shared_ptr<hierarchy_element> child, bool fix_child = true);

			/**
			 * Removes the child with the given id from this element.
			 *
			 * @param element_id The child's id.
			 * @param fix_child True if the child's parent and hierarchy shall be fixed
			 */
			virtual void erase(int element_id, bool fix_child = true);

			/**
			 * Removes the child at the given position.
			 *
			 * @param i The index of the child in the children vector.
			 * @param fix_child True if the child's parent and hierarchy shall be fixed
			 */
			virtual void erase_at(unsigned int i, bool fix_child = true);

			/**
			 * Removes all children from this element.
			 *
			 * @param fix_child True if the children's parent and hierarchy shall be fixed
			 */
			virtual void clear(bool fix_child = true);

			/**
			 * Returns a sequence containing all direct and indirect children.
			 *
			 * @return The sequence containing all direct and indirect subelements of this element.
			 */
			virtual std::vector<std::shared_ptr<hierarchy_element> > get_element_sequence();

			/**
			 * Returns a string that represents the hierarchy of this element and its direct and indirect children.
			 *
			 * @param offset Number of prefixed tabs.
			 * @return The string representation.
			 */
			virtual std::string str(int offset = 0) const;

		protected:
			/**
			 * Updates the parent and the hierarchy of this element. This is done automatically
			 * when children are assigned.
			 *
			 * @param parent A pointer to the parent element.
			 * @param h A pointer to the hierarchy.
			 * @param fix_parent If true the former and current parent will be fixed.
			 * @param fix_former_h If true the former hierarchy will be fixed.
			 */
			virtual void update_ph(hierarchy_element * const parent, hierarchy * const h, bool fix_parent = true,
					bool fix_former_h = true);

			/**
			 * Returns a pointer to the hierarchy to which this element is assigned directly or indirectly (via parents).
			 *
			 * @return A pointer to the hierarchy.
			 */
			virtual hierarchy * const get_hierarchy() const;

		private:
			int id_;
			std::string name_;
			bool dummy_;
			bool base_joint_;

			std::vector<std::shared_ptr<hierarchy_element> > children_;

			hierarchy_element* parent_;
			hierarchy* hierarchy_;
	};

} // namespace mae

#endif // HIERARCHYELEMENT_HPP_
