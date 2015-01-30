/*
 * body_part.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef BODY_PART_HPP_
#define BODY_PART_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "i_pre_sign.hpp"
#include "e_side.hpp"
#include "i_part.hpp"

//global includes
#include <string>
#include <sstream>
#include <memory>
#include <stdexcept>


namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{

				class body_part: public i_pre_sign
				{
					public:
						/**
						 * Creates a new body part pre-sign. It contains of a specific part and a side.
						 * If the side has no meaning to the part (e.g. head) is should be set to NONE.
						 *
						 * @param side The side of the body.
						 * @param part The body part.
						 */
						body_part(e_side side, std::shared_ptr<i_part> part);
						virtual ~body_part();

						/**
						 * Returns the addressed side of the body.
						 *
						 * @return
						 */
						e_side get_side() const;

						/**
						 * Returns the addressed body part.
						 * @return
						 */
						std::shared_ptr<i_part> get_part() const;

						/**
						 * Returns the XML representation for this element.
						 *
						 * @param indent The applied indent.
						 * @param namesp The prefixed XML namespace.
						 *
						 * @return The XML string.
						 */
						virtual std::string xml(unsigned int indent = 0, std::string namesp = "") const;

						/**
						 * Returns the SVG representation for this symbol.
						 *
						 * @param posx The x position.
						 * @param posy The y position.
						 * @param width The width.
						 * @param height The height.
						 * @return The SVG.
						 */
						virtual std::string svg(std::string identifier, double posx, double posy, double width, double height, bool left = false) const;

						/**
						 * Returns true if elements are equal.
						 *
						 * @param a The element to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<i_pre_sign> a) const;

					private:
						e_side side_;
						std::shared_ptr<i_part> part_;

				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // BODY_PART_HPP_
