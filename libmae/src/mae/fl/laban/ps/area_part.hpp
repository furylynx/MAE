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
						area_part(e_area area);
						virtual ~area_part();

						e_area get_area();

						virtual std::string xml(unsigned int indent = 0, std::string namesp = "");

					private:
						e_area area_;
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // AREA_PART_HPP_
