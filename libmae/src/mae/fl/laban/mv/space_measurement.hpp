/*
 * space_measurement.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef SPACE_MEASUREMENT_HPP_
#define SPACE_MEASUREMENT_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "i_degree_sign.hpp"
#include "e_space.hpp"
#include "e_space_direction.hpp"

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

				class space_measurement: public i_degree_sign
				{
					public:
						/**
						 * Creates a space measurement sign. It is not to be confused with the space symbol which
						 * is a symbol that represents a space measurement and therefore contains one.
						 *
						 * @param type The type of the space measurement.
						 * @param degree The degree which is an integer between 1 and 6.
						 * @param direction (optional) The space direction (similiar to the (horizontal) direction of a direction symbol).
						 */
						space_measurement(e_space type, unsigned int degree, e_space_direction direction = e_space_direction::NONE_SPACE_DIRECTION);
						virtual ~space_measurement();

						/**
						 * Returns the type of the space measurement.
						 *
						 * @return The type.
						 */
						e_space get_type();

						/**
						 * Returns the degree of the space measurement which is an integer between 1 and 6.
						 *
						 * @return The degree.
						 */
						unsigned int get_degree();

						/**
						 * Returns the space direction which is a horizontal direction similar to the (horizontal) direction
						 * of the direction symbols. Returns NONE if this element is not set.
						 *
						 * @return The space direction.
						 */
						e_space_direction get_direction();

						/**
						 * Compares this element to the given one and returns true if the elements are equal.
						 *
						 * @param a The element to be compared to.
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

						/**
						 * Returns the string representation for this element.
						 *
						 * @return The string.
						 */
						virtual std::string str() const;

						friend std::ostream& operator<<(std::ostream& os, const space_measurement& obj)
						{
							os << obj.str();
							return os;
						}

						friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<space_measurement>& obj)
						{
							os << obj->str();
							return os;
						}


					private:
						e_space type_;
						unsigned int degree_;
						e_space_direction direction_;

				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // SPACE_MEASUREMENT_HPP_
