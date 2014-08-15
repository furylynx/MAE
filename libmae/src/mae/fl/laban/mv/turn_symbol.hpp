/*
 * turn_symbol.hpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#ifndef TURN_SYMBOL_HPP_
#define TURN_SYMBOL_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "i_symbol.hpp"
#include "i_degree_sign.hpp"
#include "i_dynamics_sign.hpp"
#include "e_turn_direction.hpp"

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

				class turn_symbol: public i_symbol
				{
					public:
						/**
						 * Returns a turn symbol.
						 *
						 * @param direction The direction of the turn.
						 * @param dynamics (optional) An attached dynamics sign. Use null if unused and degree is required.
						 * @param degree (optional) The degree of the turn
						 */
						turn_symbol(e_turn_direction direction, std::shared_ptr<i_dynamics_sign> dynamics = nullptr, std::shared_ptr<i_degree_sign> degree = nullptr);
						virtual ~turn_symbol();

						/**
						 * Return the direction of the turn.
						 *
						 * @return The direction.
						 */
						e_turn_direction get_direction();

						/**
						 * Returns the dynamics sign if any. Returns null otherwise.
						 *
						 * @return The dynamics sign.
						 */
						std::shared_ptr<i_dynamics_sign> get_dynamics();

						/**
						 * Returns the degree of the turn if set. Returns null otherwise.
						 *
						 * @return The degree sign.
						 */
						std::shared_ptr<i_degree_sign> get_degree();

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
						e_turn_direction direction_;
						std::shared_ptr<i_dynamics_sign> dynamics_;
						std::shared_ptr<i_degree_sign> degree_;

				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // TURN_SYMBOL_HPP_
