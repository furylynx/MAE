/*
 * i_dynamics_sign.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef I_DYNAMICS_SIGN_HPP_
#define I_DYNAMICS_SIGN_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
//...

//global includes
#include <string>

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				class i_dynamics_sign
				{
					public:
						virtual ~i_dynamics_sign(){}

						virtual std::string xml(unsigned int indent = 0) = 0;
				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // I_DYNAMICS_SIGN_HPP_
