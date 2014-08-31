/*
 * relationship_endpoint.hpp
 *
 *  Created on: 22.08.2014
 *      Author: keks
 */

#ifndef RELATIONSHIP_ENDPOINT_HPP_
#define RELATIONSHIP_ENDPOINT_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "../ps/i_pre_sign.hpp"
#include "i_dynamics_sign.hpp"

//global includes
#include <memory>
#include <stdexcept>
#include <string>
#include <sstream>
#include <unordered_map>

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				class relationship_endpoint
				{
					public:
						//TODO doxygen
						relationship_endpoint(int column, bool active, std::shared_ptr<ps::i_pre_sign> pre_sign = nullptr, std::shared_ptr<i_dynamics_sign> dynamics = nullptr);
						virtual ~relationship_endpoint();

						int get_column() const;

						std::shared_ptr<ps::i_pre_sign> get_pre_sign() const;

						std::shared_ptr<i_dynamics_sign> get_dynamics() const;

						bool get_active() const;

						/**
						 * Returns the XML representation for this element.
						 *
						 * @param indent The applied indent.
						 * @param namesp The prefixed XML namespace.
						 *
						 * @return The XML string.
						 */
						virtual std::string xml(unsigned int indent = 0, std::string namesp = "") const;

						/**
						 * Recreates the element using the column mapping for the new columns.
						 *
						 * @param column_mapping
						 * @return The new endpoint.
						 */
						virtual std::shared_ptr<relationship_endpoint> recreate(std::unordered_map<int, int> column_mapping) const;

						/**
						 * Returns true if elements are equal.
						 *
						 * @param a The element to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<relationship_endpoint> a) const;

					private:
						int column_;
						std::shared_ptr<ps::i_pre_sign> pre_sign_;
						std::shared_ptr<i_dynamics_sign> dynamics_;
						bool active_;
				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // RELATIONSHIP_ENDPOINT_HPP_
