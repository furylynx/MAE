/*
 * bone.hpp
 *
 *  Created on: 18.06.2014
 *      Author: keks
 */

#ifndef BONE_HPP_
#define BONE_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
//...

//global includes
#include <string>

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
			 * should be negative to denote left and right side. The left side is typically
			 * the negative side.
			 *
			 * @param id The bone's id.
			 * @param name The bone's name.
			 * @param from Bone ranging from the joint with this id.
			 * @param to Bone ranging to the joint with this id.
			 */
			bone(int id, std::string name, int from, int to);
			virtual ~bone();

			virtual int get_id() const;
			virtual std::string get_name() const;
			virtual int get_from() const;
			virtual int get_to() const;

		private:
			int id;
			std::string name;
			int from;
			int to;
	};

} // namespace mae

#endif // BONE_HPP_
