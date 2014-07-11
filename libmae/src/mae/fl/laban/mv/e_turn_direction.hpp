/*
 * e_turn_direction.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef E_TURN_DIRECTION_HPP_
#define E_TURN_DIRECTION_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
//...

//global includes
#include <string>
#include <stdexcept>

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				enum class e_turn_direction
				{
						NONE,
						COUNTER_CLOCKWISE,
						CLOCKWISE,
						ANY
				};

				class e_turn_direction_str
				{
					public:
						static std::string str(e_turn_direction turn);
				};


			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_TURN_DIRECTION_HPP_
