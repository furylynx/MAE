/*
 * i_limb.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef I_LIMB_HPP_
#define I_LIMB_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "i_part.hpp"

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

				class i_limb: public i_part
				{
					public:
						virtual ~i_limb(){}

						virtual std::string xml(unsigned int indent = 0) = 0;
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // I_LIMB_HPP_
