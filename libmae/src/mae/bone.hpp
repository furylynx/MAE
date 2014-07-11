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


//global includes
#include <string>
#include <vector>

namespace mae
{

	class bone
	{
		public:
			/**
			 * Creates a bone with an id and a name. A bone should typically be defined
			 * pointing away from the root or parent.
			 *
			 * Please note that the id is used by the FL* sequence generator to identify
			 * the column of the subsequence that is addressed by the bone. The id can and
			 * should be negative to distinguish left and right side. The left side is typically
			 * the negative side.
			 *
			 * @param id The bone's id.
			 * @param name The bone's name.
			 * @param from Bone ranging from the joint with this id.
			 * @param to Bone ranging to the joint with this id.
			 */
			bone(int id, std::string name, int from, int to);

			bone(int id, std::string name, int from, int to, int middle_joint);
			virtual ~bone();

			virtual int get_id() const;
			virtual std::string get_name() const;
			virtual int get_from() const;
			virtual int get_to() const;

			virtual bool has_middle_joint() const;
			virtual int get_middle_joint() const;

			/**
			 * Returns a default bones vector that fits the needs of the OpenNI/NiTE
			 * skeletons. If the OpenNI/NiTE hierarchy is not sufficient and/or other
			 * bones are needed it must be constructed manually.
			 *
			 * @return The default hierarchy.
			 */
			static std::vector<bone> default_bones();

			static const int RESERVED_TOP_DOWN 	= 9999;
			static const int RESERVED_RIGHT_LEFT 	= 10000;

		private:
			int id_;
			std::string name_;
			int from_;
			int to_;

			bool middle_;
			int middle_joint_;

			static std::vector<bone> default_bones_;
	};

} // namespace mae

#endif // BONE_HPP_
