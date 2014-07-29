/*
 * e_direction.h
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef E_DIRECTION_H_
#define E_DIRECTION_H_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "../../e_fl_direction.hpp"
#include "../../../mstr.hpp"

//global includes
#include <string>
#include <stdexcept>
#include <vector>

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				enum class e_direction
				{
						NONE,
						PLACE,
						FORWARD,
						BACKWARD,
						LEFT,
						RIGHT,
						LEFT_FORWARD,
						LEFT_BACKWARD,
						RIGHT_FORWARD,
						RIGHT_BACKWARD
				};

				class e_direction_c
				{
					public:
						static std::string str(e_direction direction);
						static e_direction dir(e_fl_direction direction);
						static std::vector<e_direction> vec();
						static e_direction parse(std::string str);

				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_DIRECTION_H_
