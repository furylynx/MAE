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
						digit_part(e_digit digit, unsigned int knuckle);
						virtual ~digit_part();

						e_digit get_digit();
						unsigned int get_knuckle();

						virtual std::string xml(unsigned int indent = 0);

					private:
						e_digit digit_;
						unsigned int knuckle_;
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // DIGIT_PART_HPP_
