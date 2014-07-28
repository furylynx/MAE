/*
 * e_dynamic.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef E_DYNAMIC_HPP_
#define E_DYNAMIC_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
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

				enum class e_dynamic
				{
						NONE,
						STRONG,
						GENTLE,
						EMPHASIZED,
						RELAXED,
						LIMP,
						UNEMPHASIZED,
						RESILIENT,
						VERY_RESILIENT
				};

				class e_dynamic_c
				{
					public:
						static std::string str(e_dynamic dynamic);
						static std::vector<e_dynamic> vec();
						static e_dynamic parse(std::string str);

				};


			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_DYNAMIC_HPP_
