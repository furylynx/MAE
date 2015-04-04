/*
 * msr_spec.hpp
 *
 *  Created on: 04.04.2015
 *      Author: keks
 */

#ifndef MSR_SPEC_HPP_
#define MSR_SPEC_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
#include "../hierarchy.hpp"

//global includes
#include <unordered_map>
#include <memory>
#include <exception>

namespace mae
{
	namespace fl
	{

		class msr_spec
		{
			public:
				/**
				 * Creates a new specification for the msr import. The specification defines
				 * the IDs that are assigned to the rows in whicht the joint positions are
				 * given.
				 *
				 * @param string_id_map The map for the row number and the joint id.
				 * @param hierarchy The skeleton hierarchy to be used.
				 */
				msr_spec(std::map<unsigned int, int> id_map, std::shared_ptr<hierarchy> hierarchy);
				virtual ~msr_spec();


				/**
				 * Returns the map that maps row number to joint id of the hierarchy.
				 *
				 * @return The map.
				 */
				std::map<unsigned int, int> get_id_map();

				/**
				 * Returns the skeleton hierarchy.
				 *
				 * @return The hierarchy.
				 */
				std::shared_ptr<hierarchy> get_hierarchy();

				/**
				 * Creates a default specification that fits the default hierarchy definition.
				 *
				 * @return The default specification.
				 */
				static std::shared_ptr<msr_spec> default_spec();


			private:
				std::map<unsigned int, int> id_map_;
				std::shared_ptr<hierarchy> hierarchy_;

		};

	} // namespace fl
} // namespace mae

#endif // MSR_SPEC_HPP_
