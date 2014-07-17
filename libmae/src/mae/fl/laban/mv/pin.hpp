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
						pin(e_level level, int horizontal);
						virtual ~pin();

						e_level get_level();
						int get_horizontal();

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
