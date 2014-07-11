/*
 * i_movement.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef I_MOVEMENT_HPP_
#define I_MOVEMENT_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

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

			class i_movement
			{
				public:
					virtual ~i_movement();

					virtual std::string xml(unsigned int indent = 0) = 0;
			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // I_MOVEMENT_HPP_
