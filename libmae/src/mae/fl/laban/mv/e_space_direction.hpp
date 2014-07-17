/*
 * e_space_direction.h
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef E_SPACE_DIRECTION_H_
#define E_SPACE_DIRECTION_H_

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

				enum class e_space_direction
				{
						NONE,
						LEFT,
						FRONT_LEFT,
						FRONT,
						FRONT_RIGHT,
						RIGHT,
						BACK_RIGHT,
						BACK,
						BACK_LEFT
				};

				class e_space_direction_c
				{
					public:
						static std::string str(e_space_direction space_direction);
				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_SPACE_DIRECTION_H_
