/*
 * direction_symbol.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef DIRECTION_SYMBOL_HPP_
#define DIRECTION_SYMBOL_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "i_symbol.hpp"
#include "e_level.hpp"
#include "e_direction.hpp"
#include "e_contact_hook.hpp"
#include "i_dynamics_sign.hpp"
#include "space_measurement.hpp"
#include "pin.hpp"

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

				class direction_symbol: public i_symbol
				{
					public:
						/**
						 * Creates a direction symbol.
						 *
						 * @param vertical The level of this symbol.
						 * @param horizontal The (horizontal) direction of this symbol.
						 * @param modification_pin (optional) A modification pin.
						 * @param relationship_pin (optional) A relationship pin.
						 * @param dynamics (optional) A dynamics sign.
						 * @param space_measurement (optional) A space measurement sign.
						 * @param contact_hook (optional) The contact hook.
						 */
						direction_symbol(e_level vertical, e_direction horizontal, std::shared_ptr<pin> modification_pin = nullptr, std::shared_ptr<pin> relationship_pin = nullptr, std::shared_ptr<i_dynamics_sign> dynamics = nullptr, std::shared_ptr<space_measurement> space_measurement = nullptr, e_contact_hook contact_hook = e_contact_hook::NONE_CONTACT_HOOK);
						virtual ~direction_symbol();

						/**
						 * Returns the level of this symbol.
						 *
						 * @return The level.
						 */
						e_level get_vertical();

						/**
						 * Returns the (horizontal) direction of this symbol.
						 *
						 * @return The direction.
						 */
						e_direction get_horizontal();

						/**
						 * Returns the applied modification pin if any. Returns null otherwise.
						 *
						 * @return A shared pointer to the pin.
						 */
						std::shared_ptr<pin> get_modification_pin();

						/**
						 * Returns the relationship pin if any. Returns null otherwise.
						 *
						 * @return A shared pointer to the pin.
						 */
						std::shared_ptr<pin> get_relationship_pin();

						/**
						 * Returns the dynamics sign if any. Returns null otherwise.
						 *
						 * @return A shared pointer to the dynamics sign.
						 */
						std::shared_ptr<i_dynamics_sign> get_dynamics();

						/**
						 * Returns the space measurement sign if any. Returns null otherwise.
						 *
						 * @return A shared pointer to the space measurement.
						 */
						std::shared_ptr<space_measurement> get_space_measurement();

						/**
						 * Returns the contact hook. Contact hook is set to NONE if unused.
						 *
						 * @return The contact hook.
						 */
						e_contact_hook get_contact_hook();

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

						/**
						 * Returns the SVG representation for this symbol.
						 *
						 * @param posx The x position.
						 * @param posy The y position.
						 * @param width The width.
						 * @param height The height.
						 * @return The SVG.
						 */
						virtual std::string svg(std::string identifier, double posx, double posy, double width, double height, bool left = false);

						/**
						 * Returns the string representation for this element.
						 *
						 * @return The string.
						 */
						virtual std::string str() const;

						friend std::ostream& operator<<(std::ostream& os, const direction_symbol& obj)
						{
							os << obj.str();
							return os;
						}

						friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<direction_symbol>& obj)
						{
							os << obj->str();
							return os;
						}

					private:
						e_level vertical_;
						e_direction horizontal_;
						std::shared_ptr<pin> modification_pin_;
						std::shared_ptr<pin> relationship_pin_;
						std::shared_ptr<i_dynamics_sign> dynamics_;
						std::shared_ptr<space_measurement> space_measurement_;
						e_contact_hook contact_hook_;
				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // DIRECTION_SYMBOL_HPP_
