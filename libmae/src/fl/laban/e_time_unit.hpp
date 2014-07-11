/*
 * e_time_unit.hpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#ifndef E_TIME_UNIT_HPP_
#define E_TIME_UNIT_HPP_

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

			enum class e_time_unit
			{
					NONE,
					MINUTE,
					SECOND,
					MILLISECOND
			};

			class e_time_unit_str
			{
				public:
					static std::string str(e_time_unit unit);
			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_TIME_UNIT_HPP_
