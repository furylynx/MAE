/*
 * accent_sign.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef ACCENT_SIGN_HPP_
#define ACCENT_SIGN_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "i_dynamics_sign.hpp"

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

				class accent_sign: public i_dynamics_sign
				{
					public:
						/**
						 * Creates an accent sign. The accent must be a value between 1 and 5.
						 *
						 * @param accent The accent which must be an integer value between 1 and 5.
						 */
						accent_sign(unsigned int accent);
						virtual ~accent_sign();

						/**
						 * Returns the accent.
						 * @return
						 */
						unsigned int get_accent() const;

						/**
						 * Returns true if signs are equal.
						 *
						 * @param a The sign to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<i_dynamics_sign> a) const;

						/**
						 * Returns the XML representation for this element.
						 *
						 * @param indent The applied indent.
						 * @param namesp The prefixed XML namespace.
						 *
						 * @return The XML string.
						 */
						virtual std::string xml(unsigned int indent = 0, std::string namesp = "") const;

					private:
						unsigned int accent_;
				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // ACCENT_SIGN_HPP_
