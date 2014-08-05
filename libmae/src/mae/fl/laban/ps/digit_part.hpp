/*
 * digit_part.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef DIGIT_PART_HPP_
#define DIGIT_PART_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "i_endpoint.hpp"
#include "e_digit.hpp"

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

				class digit_part: public i_endpoint
				{
					public:
						/**
						 * Creates a digit pre-sign which consist of a digit (finger or toes) and a knuckle.
						 *
						 * @param digit The addressed digit.
						 * @param knuckle The addressed knuckle. Zero represents the whole digit, whereas
						 * 					A number represents the knuckle counted from the base. Therefore
						 * 					3 for toes and 4 for fingers is the maximum valid value.
						 */
						digit_part(e_digit digit, unsigned int knuckle);
						virtual ~digit_part();

						/**
						 * Returns the addressed digit.
						 *
						 * @return
						 */
						e_digit get_digit();

						/**
						 * Returns the addressed knuckle. Zero represents the whole digit whereas a number
						 * represents the knuckle counted from the base.
						 *
						 * @return
						 */
						unsigned int get_knuckle();

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
						e_digit digit_;
						unsigned int knuckle_;
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // DIGIT_PART_HPP_
