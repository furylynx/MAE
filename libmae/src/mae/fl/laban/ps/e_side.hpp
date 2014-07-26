/*
 * e_side.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef E_SIDE_HPP_
#define E_SIDE_HPP_

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
			namespace ps
			{

				enum class e_side
				{
						NONE,
						LEFT,
						RIGHT
				};

				class e_side_c
				{
					public:
						static std::string str(e_side e_side_);
						static std::vector<e_side> vec();
						static e_side parse(std::string vec);
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_SIDE_HPP_
