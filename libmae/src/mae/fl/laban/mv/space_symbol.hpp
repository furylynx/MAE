/*
 * space_symbol.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef SPACE_SYMBOL_HPP_
#define SPACE_SYMBOL_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "i_symbol.hpp"
#include "space_measurement.hpp"
#include "i_dynamics_sign.hpp"

//global includes
#include <string>
#include <sstream>
#include <stdexcept>
#include <memory>


namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				class space_symbol: public i_symbol
				{
					public:
						/**
						 * Creates a new space symbol. It is not to be confused with the space measurement sign
						 * which is a member of this symbol.
						 *
						 * @param space_measurement The space measurement sign.
						 * @param dynamics (optional) The dynamics sign.
						 */
						space_symbol(std::shared_ptr<space_measurement> space_measurement, std::shared_ptr<i_dynamics_sign> dynamics = nullptr);
						virtual ~space_symbol();

						/**
						 * Returns the dynamics sign if any. Returns null otherwise.
						 *
						 * @return A shared pointer to the dynamics sign.
						 */
						std::shared_ptr<i_dynamics_sign> get_dynamics();

						/**
						 * Returns the space measurement sign.
						 *
						 * @return The space measurement.
						 */
						std::shared_ptr<space_measurement> get_space_measurement();

						/**
						 * Returns true if signs are equal.
						 *
						 * @param a The sign to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<i_symbol> a);

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
						std::shared_ptr<i_dynamics_sign> dynamics_;
						std::shared_ptr<space_measurement> space_measurement_;

				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // SPACE_SYMBOL_HPP_
