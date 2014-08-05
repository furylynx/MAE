/*
 * prop.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef PROP_HPP_
#define PROP_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "i_pre_sign.hpp"

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

				class prop : public i_pre_sign
				{
					public:
						/**
						 * Creates a prop pre-sign which can be used to freely define a pre-sign
						 * using a name and an optional description.
						 *
						 * @param name The expressive name of the pre-sign.
						 * @param description The optional description.
						 */
						prop(std::string name, std::string description = "");
						virtual ~prop();

						/**
						 * Returns the name of the pre-sign.
						 * @return
						 */
						std::string get_name();

						/**
						 * Returns the description of the pre-sign. Returns an empty
						 * string if none set.
						 *
						 * @return
						 */
						std::string get_description();

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
						std::string name_;
						std::string description_;
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // PROP_HPP_
