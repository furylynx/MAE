/*
 * e_level.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef E_LEVEL_HPP_
#define E_LEVEL_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "../../e_fl_direction.hpp"

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

				enum class e_level
				{
						NONE,
						HIGH,
						MIDDLE,
						LOW
				};

				class e_level_c
				{
					public:
						static std::string str(e_level level);
						static e_level lvl(e_fl_direction direction);
				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_LEVEL_HPP_
