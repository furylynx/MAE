/*
 * default_limb.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef DEFAULT_LIMB_HPP_
#define DEFAULT_LIMB_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "i_limb.hpp"
#include "e_limb.hpp"

//global includes
#include <string>
#include <sstream>
#include <stdexcept>


namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{

				class default_limb: public i_limb
				{
					public:
						/**
						 * Creates a default limb pre-sign which uses one of the defined limbs.
						 *
						 * @param limb The limb type.
						 */
						default_limb(e_limb limb);
						virtual ~default_limb();

						/**
						 * Returns the limb type.
						 *
						 * @return
						 */
						e_limb get_limb();

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
						e_limb limb_;
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // DEFAULT_LIMB_HPP_
