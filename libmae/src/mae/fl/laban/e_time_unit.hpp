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
#include "../../mstr.hpp"

//global includes
#include <string>
#include <vector>
#include <stdexcept>


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

			class e_time_unit_c
			{
				public:
					static std::string str(e_time_unit unit);
					static std::vector<e_time_unit> vec();
					static e_time_unit parse(std::string str);
			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_TIME_UNIT_HPP_
