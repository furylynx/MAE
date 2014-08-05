/*
 * custom_limb.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef CUSTOM_LIMB_HPP_
#define CUSTOM_LIMB_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "i_limb.hpp"
#include "i_endpoint.hpp"

//global includes
#include <string>
#include <sstream>
#include <memory>
#include <stdexcept>

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{

				class custom_limb: public i_limb
				{
					public:
						/**
						 * Creates a custom limb pre-sign which is defined as the limb between two endpoints.
						 *
						 * @param fixed_end The fixed end of the limb.
						 * @param extremity (optional) The extremity end of the limb.
						 */
						custom_limb(std::shared_ptr<i_endpoint> fixed_end, std::shared_ptr<i_endpoint> extremity = nullptr);
						virtual ~custom_limb();

						/**
						 * Returns the fixed end of the limb.
						 *
						 * @return
						 */
						std::shared_ptr<i_endpoint> get_fixed_end();

						/**
						 * Returns the extremity end of the limb if set. Returns null otherwise.
						 *
						 * @return
						 */
						std::shared_ptr<i_endpoint> get_extremity();

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
						std::shared_ptr<i_endpoint> fixed_end_;
						std::shared_ptr<i_endpoint> extremity_;
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // CUSTOM_LIMB_HPP_
