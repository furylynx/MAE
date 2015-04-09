/*
 * bone.hpp
 *
 *  Created on: 18.06.2014
 *      Author: keks
 */

#ifndef BONE_HPP_
#define BONE_HPP_

//eclipse indexer fix
#include "indexer_fix.hpp"

//custom includes
#include "e_bone.hpp"
#include "e_joint.hpp"
#include "e_kinect_joint.hpp"

//global includes
#include <string>
#include <vector>
#include <stdexcept>

namespace mae
{

	class bone
	{
		public:
			/**
			 * Creates a new empty bone with no information.
			 */
			bone();

			/**
			 * Creates a bone with an id and a name. A bone should typically be defined
			 * pointing away from the root or parent.
			 *
			 * Please note that the id is used by the FL* sequence generator to identify
			 * the column of the subsequence that is addressed by the bone. The id can and
			 * should be negative to distinguish left and right side. The left side is typically
			 * the negative side.
			 *
			 * @param id The bone's id. Please note that the reserved values 9999 and 10000 should not be used.
			 * @param name The bone's name.
			 * @param from This bone is ranging from the joint with this id.
			 * @param to This bone is ranging to the joint with this id.
			 */
			bone(int id, std::string name, int from, int to);

			/**
			 * Creates a bone that has a middle joint with an ID and a name. A bone should typically be defined
			 * pointing away from the root or parent.
			 *
			 * Please note that the id is used by the FL* sequence generator to identify
			 * the column of the subsequence that is addressed by the bone. The id can and
			 * should be negative to distinguish left and right side. The left side is typically
			 * the negative side.
			 *
			 * @param id The bone's id. Please note that the reserved values 9999 and 10000 should not be used.
			 * @param name The bone's name.
			 * @param from his bone is ranging from the joint with this id.
			 * @param to his bone is ranging to the joint with this id.
			 * @param middle_joint Joint lying between the two outer ones (e.g. the elbow for from shoulder to hand).
			 */
			bone(int id, std::string name, int from, int to, int middle_joint);

			/**
			 * Creates a bone from the e_bone enum value by referring to the default bones.
			 *
			 * @param eb The bone enum value.
			 */
			bone(e_bone eb);

			/**
			 * Creates a bone from the e_bone enum value by referring to the given bones.
			 *
			 * @param eb The bone enum value.
			 * @param bones_set The bones set to be searched for the enum value.
			 */
			bone(e_bone eb, std::vector<bone> bones_set);
			virtual ~bone();

			/**
			 * Returns this bone's ID.
			 *
			 * @return The ID.
			 */
			virtual int get_id() const;

			/**
			 * Returns the name of the bone.
			 *
			 * @return The name.
			 */
			virtual std::string get_name() const;

			/**
			 * Returns the ID of the joint where this bone begins.
			 *
			 * @return The "from" joint's ID.
			 */
			virtual int get_from() const;

			/**
			 * Returns the ID of the joint where this bone ends.
			 * @return The "to" joint's ID.
			 */
			virtual int get_to() const;

			/**
			 * Returns true if this bone has a joint in it.
			 *
			 * @return True if there is a middle joint.
			 */
			virtual bool has_middle_joint() const;

			/**
			 * Returns the ID of the joint in the middle.
			 *
			 * @return The ID.
			 */
			virtual int get_middle_joint() const;

			/**
			 * Returns a default bones vector that fits the needs of the OpenNI/NiTE
			 * skeletons. If the default hierarchies are not sufficient and/or other
			 * bones are needed it must be constructed manually.
			 *
			 * @return The default bones.
			 */
			static std::vector<bone> default_bones();

			/**
			 * Returns the default bones for the kinect skeleton.  If the default hierarchies are not sufficient and/or other
			 * bones are needed it must be constructed manually.
			 *
			 * @return The kinect bones.
			 */
			static std::vector<bone> default_kinect_bones();

			/**
			 * The reserved value for the top-down bone. This bone is used for the general skeleton.
			 */
			static const int RESERVED_TOP_DOWN = 9999;

			/**
			 * The reserved value for the right-left bone. This bone is used for the general skeleton.
			 */
			static const int RESERVED_RIGHT_LEFT = 10000;

		private:
			int id_;
			std::string name_;
			int from_;
			int to_;

			bool middle_;
			int middle_joint_;

			static std::vector<bone> default_bones_;
			static std::vector<bone> default_kinect_bones_;


			void initialize_by_e_bone(e_bone eb, std::vector<bone> bones_set);
	};

} // namespace mae

#endif // BONE_HPP_
