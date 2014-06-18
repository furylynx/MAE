/*
 * bvhspec.hpp
 *
 *  Created on: 20.06.2014
 *      Author: keks
 */

#ifndef BVHSPEC_HPP_
#define BVHSPEC_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "../model/maej.hpp"
#include "../controller/mstr.hpp"

//global includes
#include <unordered_map>
#include <string>
#include <memory>

namespace mae
{
	namespace fl
	{

		class bvh_spec
		{
			public:
				/**
				 * Creates a new specification for the bvh import. The specification defines
				 * the IDs that are assigned to the read string values of the joints. If the
				 * id map is empty the position of occurrence in the bvh file is used by the
				 * reader. Additionally the torso joints can be defined by the torso map. If
				 * the torso map is empty a suffix sharp '#' after the joint name is used to
				 * denote torso joints.
				 *
				 * @param string_id_map
				 * @param string_torso_map
				 */
				bvh_spec(std::unordered_map<std::string, int> string_id_map, std::unordered_map<std::string, bool> string_torso_map);
				virtual ~bvh_spec();

				/**
				 * Returns the string to id map.
				 *
				 * @return The string to id map.
				 */
				virtual std::unordered_map<std::string, int> get_id_map() const;

				/**
				 * Returns the string to torso joint map.
				 *
				 * @return
				 */
				virtual std::unordered_map<std::string, bool> get_torso_map() const;

				/**
				 * Creates a default specification that fits the default hierarchy definition.
				 *
				 * @return The default specification.
				 */
				static std::shared_ptr<bvh_spec> default_spec();

			private:
				std::unordered_map<std::string, int> string_id_map_;
				std::unordered_map<std::string, bool> string_torso_map_;

		};

	} // namespace fl
} // namespace mae

#endif // BVHSPEC_HPP_
