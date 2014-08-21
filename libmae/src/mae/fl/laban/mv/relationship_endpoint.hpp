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
						relationship_endpoint(unsigned int column, bool active, std::shared_ptr<ps::i_pre_sign> pre_sign = nullptr, std::shared_ptr<i_dynamics_sign> dynamics = nullptr);
						virtual ~relationship_endpoint();

						unsigned int get_column();
						std::shared_ptr<ps::i_pre_sign> get_pre_sign();
						std::shared_ptr<i_dynamics_sign> get_dynamics();
						bool get_active();

						/**
						 * Returns the XML representation for this element.
						 *
						 * @param indent The applied indent.
						 * @param namesp The prefixed XML namespace.
						 *
						 * @return The XML string.
						 */
						virtual std::string xml(unsigned int indent = 0, std::string namesp = "");

					private:
						unsigned int column_;
						std::shared_ptr<ps::i_pre_sign> pre_sign_;
						std::shared_ptr<i_dynamics_sign> dynamics_;
						bool active_;
				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // RELATIONSHIP_ENDPOINT_HPP_
