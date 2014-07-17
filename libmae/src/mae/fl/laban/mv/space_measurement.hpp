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
						space_measurement(e_space type, unsigned int degree, e_space_direction direction = e_space_direction::NONE);
						virtual ~space_measurement();

						e_space get_type();
						unsigned int get_degree();
						e_space_direction get_direction();

						virtual std::string xml(unsigned int indent = 0, std::string namesp = "");

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
