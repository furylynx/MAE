/*
 * accent_sign.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef ACCENT_SIGN_HPP_
#define ACCENT_SIGN_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "i_dynamics_sign.hpp"

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

				class accent_sign: public i_dynamics_sign
				{
					public:
						accent_sign(unsigned int accent);
						virtual ~accent_sign();

						unsigned int get_accent();

						virtual std::string xml(unsigned int indent = 0);

					private:
						unsigned int accent_;
				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // ACCENT_SIGN_HPP_
