/*
 * i_pre_sign.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef I_PRE_SIGN_HPP_
#define I_PRE_SIGN_HPP_

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
			namespace ps
			{

				class i_pre_sign
				{
					public:
						virtual ~i_pre_sign(){}

						virtual std::string xml(unsigned int indent = 0) = 0;
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // I_PRE_SIGN_HPP_
