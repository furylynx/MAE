/*
 * cancellation_symbol.hpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#ifndef CANCELLATION_SYMBOL_HPP_
#define CANCELLATION_SYMBOL_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "i_symbol.hpp"
#include "e_cancel.hpp"

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
			namespace mv
			{

				class cancellation_symbol : public i_symbol
				{
					public:
						/**
						 * Creates a cancellation symbol.
						 *
						 * @param cancel The cancellation type.
						 */
						cancellation_symbol(e_cancel cancel);
						virtual ~cancellation_symbol();

						/**
						 * Returns the cancellation type.
						 *
						 * @return The cancellation type.
						 */
						e_cancel get_cancel();

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
						e_cancel cancel_;
				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // CANCELLATION_SYMBOL_HPP_
