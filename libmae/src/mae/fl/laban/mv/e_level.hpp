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

				enum class e_level
				{
						NONE,
						HIGH,
						MIDDLE,
						LOW
				};

				class e_level_str
				{
					public:
						static std::string str(e_level level);
				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_LEVEL_HPP_
