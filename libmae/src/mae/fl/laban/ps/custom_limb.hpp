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
						custom_limb(std::shared_ptr<i_endpoint> extremity, std::shared_ptr<i_endpoint> fixed_end = nullptr);
						virtual ~custom_limb();

						/**
						 * Returns the fixed end of the limb.
						 *
						 * @return
						 */
						std::shared_ptr<i_endpoint> get_fixed_end() const;

						/**
						 * Returns the extremity end of the limb if set. Returns null otherwise.
						 *
						 * @return
						 */
						std::shared_ptr<i_endpoint> get_extremity() const;

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
						 * Returns true if elements are equal.
						 *
						 * @param a The element to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<i_part> a) const;

						/**
						 * Returns true if elements are equal.
						 *
						 * @param a The element to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<i_limb> a) const;

					private:
						std::shared_ptr<i_endpoint> fixed_end_;
						std::shared_ptr<i_endpoint> extremity_;
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // CUSTOM_LIMB_HPP_
