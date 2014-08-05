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
						e_area get_area();

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
						e_area area_;
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // AREA_PART_HPP_
