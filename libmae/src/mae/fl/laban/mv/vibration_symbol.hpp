/*
 * vibration_symbol.hpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#ifndef VIBRATION_SYMBOL_HPP_
#define VIBRATION_SYMBOL_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "i_symbol.hpp"
#include "pin.hpp"
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

				class vibration_symbol: public i_symbol
				{
					public:
						/**
						 * Creates a vibration symbol. A vibration symbol represents an alternation
						 * between two directions which is represented by two pins.
						 *
						 * @param displacement1 The first pin.
						 * @param displacement2 The second pin.
						 * @param dynamics (optional) A dynamics sign.
						 */
						vibration_symbol(std::shared_ptr<pin> displacement1, std::shared_ptr<pin> displacement2, std::shared_ptr<i_dynamics_sign> dynamics = nullptr);
						virtual ~vibration_symbol();

						/**
						 * Returns the dynamics sign if any. Returns null otherwise.
						 *
						 * @return
						 */
						std::shared_ptr<i_dynamics_sign> get_dynamics();

						/**
						 * The first of the two alternating directions.
						 *
						 * @return The pin.
						 */
						std::shared_ptr<pin> get_displacement1();

						/**
						 * The second of the two alternating directions.
						 *
						 * @return The pin.
						 */
						std::shared_ptr<pin> get_displacement2();

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
						std::shared_ptr<pin> displacement1_;
						std::shared_ptr<pin> displacement2_;

				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // VIBRATION_SYMBOL_HPP_
