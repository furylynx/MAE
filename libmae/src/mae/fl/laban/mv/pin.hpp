/*
 * pin.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef PIN_HPP_
#define PIN_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "i_degree_sign.hpp"
#include "e_level.hpp"

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

				class pin: public i_degree_sign
				{
					public:
						/**
						 * Creates a pin. The horizontal direction must be a value between -1 and 360.
						 *
						 * @param level The level type.
						 * @param horizontal The horizontal direction which must be a value between -1
						 * 						and 360. -1 represents at place whereas a value between
						 * 						0 and 360 represents a the degree relative to the
						 * 						forward direction (e.g. 90 represents "right").
						 */
						pin(e_level level, int horizontal);
						virtual ~pin();

						/**
						 * Returns the level.
						 *
						 * @return The level.
						 */
						e_level get_level();

						/**
						 * Returns the (horizontal) direction which is a value between -1 and 360.
						 * -1 represents at place whereas a value between 0 and 360 represents a
						 * the degree relative to the forward direction (e.g. 90 represents
						 * "right").
						 *
						 * @return The direction.
						 */
						int get_horizontal();

						/**
						 * Returns true if signs are equal.
						 *
						 * @param a The sign to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<i_degree_sign> a);

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
						e_level level_;
						int horizontal_;
				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // PIN_HPP_
