/*
 * area_part.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef AREA_PART_HPP_
#define AREA_PART_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "i_endpoint.hpp"
#include "e_area.hpp"

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

				class area_part: public i_endpoint
				{
					public:
						/**
						 * Creates a new area pre-sign.
						 *
						 * @param area The addressed area.
						 */
						area_part(e_area area);
						virtual ~area_part();

						/**
						 * Returns the addressed area.
						 *
						 * @return
						 */
						e_area get_area() const;

						/**
						 * Returns the XML representation for this element.
						 *
						 * @param indent The applied indent.
						 * @param namesp The prefixed XML namespace.
						 *
						 * @return The XML string.
						 */
						virtual std::string xml(unsigned int indent = 0, std::string namesp = "")  const;

						/**
						 * Returns the successor of the current endpoint (which is the default extremity endpoint). If the endpoint is the end of the extremity null is returned.
						 *
						 * @return The successor element.
						 */
						virtual std::shared_ptr<i_endpoint> get_fixed_end() const;

						/**
						 * Returns true if elements are equal.
						 *
						 * @param a The element to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<i_part> a) const;

						/**
						 * Returns true if elements are equal.
						 *
						 * @param a The element to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<i_endpoint> a) const;


					private:
						e_area area_;
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // AREA_PART_HPP_
