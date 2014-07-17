/*
 * dynamics_sign.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef DYNAMIC_SIGN_HPP_
#define DYNAMIC_SIGN_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "i_dynamics_sign.hpp"
#include "e_dynamic.hpp"

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

				class dynamic_sign: public i_dynamics_sign
				{
					public:
						dynamic_sign(e_dynamic dynamic);
						virtual ~dynamic_sign();

						e_dynamic get_dynamic();

						virtual std::string xml(unsigned int indent = 0, std::string namesp = "");

					private:
						e_dynamic dynamic_;
				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // DYNAMICS_SIGN_HPP_
