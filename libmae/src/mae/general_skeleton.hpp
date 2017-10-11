#ifndef MAE_GENERALSKELETON_HPP_
#define MAE_GENERALSKELETON_HPP_

//custom includes
#include "general_joint.hpp"
#include "hierarchy.hpp"
#include "hierarchy_element.hpp"
#include "bone.hpp"
#include "math/vec3d.hpp"
#include "math/basis.hpp"

//global includes
#include <unordered_map>
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <fstream>
#include <iostream>

namespace mae
{

	class general_skeleton
	{
		public:
			/**
			 * Creates a general skeleton.
			 *
			 */
			general_skeleton();

			/**
			 * Creates a general skeleton with a pre-defined hierarchy.
			 *
			 * @param hierarchy The hierarchy.
			 */
			general_skeleton(std::shared_ptr<hierarchy> hierarchy);

			virtual ~general_skeleton();

			/**
			 * Sets a new joint for the given body part.
			 *
			 * @param bodyPart The addressed body part.
			 * @param joint A shared pointer to the joint.
			 */
			virtual void set_joint(int body_part, std::shared_ptr<general_joint> joint);

			/**
			 * Returns a shared pointer to the joint of the body part.
			 *
			 * @param bodyPart The addressed body part.
			 * @return A shared pointer to the joint.
			 */
			virtual std::shared_ptr<general_joint> get_joint(int body_part) const;

			/**
			 * Returns a shared pointer to the used hierarchy. If not hierarchy is set, a default hierarchy is assumed.
			 * @return A shared pointer to the hierarchy.
			 */
			virtual std::shared_ptr<mae::hierarchy> get_hierarchy() const;

			/**
			 * Sets the hierarchy
			 * @param hierarchy  A smart pointer to the hierarchy.
			 */
			virtual void set_hierarchy(std::shared_ptr<mae::hierarchy> hierarchy);

			/**
			 * Sets the top-down direction of this skeleton by defining a bone. The bone must
			 * range from one torso joint to another and need not to follow the hierarchy (but
			 * the id's must be defined).
			 *
			 * @param top_down A shared pointer to the bone.
			 */
			virtual void set_top_down(std::shared_ptr<bone> top_down);

			/**
			 * Returns the top-down direction of this skeleton by giving a bone. The bone ranges
			 * from one torso joint to another.
			 *
			 * @param top_down A shared pointer to the bone.
			 */
			virtual std::shared_ptr<bone> get_top_down() const;

			/**
			 * Sets the right-left direction of this skeleton by defining a bone. The bone must
			 * range from one torso joint to another and need not to follow the hierarchy (but
			 * the id's must be defined).
			 *
			 * @param top_down A shared pointer to the bone.
			 */
			virtual void set_right_left(std::shared_ptr<bone> right_left);

			/**
			 * Returns the right-left direction of this skeleton by giving a bone. The bone ranges
			 * from one torso joint to another.
			 *
			 * @param top_down A shared pointer to the bone.
			 */
			virtual std::shared_ptr<bone> get_right_left() const;

			/**
			 * Sets the weight vector for this skeleton.
			 *
			 * @param weight The weight vector.
			 */
			virtual void set_weight(std::shared_ptr<mae::math::vec3d> weight);

			/**
			 * Returns the weight vector for this skeleton. If none is set, a null pointer will be returned.
			 *
			 * @return The weight or null.
			 */
			virtual std::shared_ptr<mae::math::vec3d> get_weight() const;

			/**
			 * Converts this object to a string.
			 *
			 * @return This object as a string.
			 */
			virtual std::string str() const;

			/**
			 * Exports the skeleton data in the Stanford Triagle format as a string.
			 * @return
			 */
			virtual std::string ply_str() const;

			/**
			 * Exports the skeleton data to the file using the Stanford Triangle Format format.
			 *
			 * @param filename The target output file.
			 *
			 */
			virtual void ply_file(std::string filename) const;

			/**
			 * Prints the object to the stream.
			 *
			 * @param os
			 * @param obj The object to be printed.
			 * @return
			 */
			friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<general_skeleton>& obj)
			{
				os << obj->str();

				return os;
			}

			/**
			 * Prints the object to the stream.
			 *
			 * @param os
			 * @param obj The object to be printed.
			 * @return
			 */
			friend std::ostream& operator<<(std::ostream& os, const general_skeleton& obj)
			{
				os << obj.str();

				return os;
			}

		private:
			std::unordered_map<int, std::shared_ptr<general_joint> > hashmap_joints_;
			std::shared_ptr<hierarchy> hierarchy_;

			std::shared_ptr<bone> top_down_;
			std::shared_ptr<bone> right_left_;

			std::shared_ptr<mae::math::vec3d> weight_;
	};

} // namespace mae

#endif // MAE_GENERALSKELETON_HPP_
