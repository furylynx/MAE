/*
 * e_limb_side.h
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef E_LIMB_SIDE_H_
#define E_LIMB_SIDE_H_

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

				enum class e_limb_side{
						NONE,
						INNER,
						OUTER,
						LITTLEFINGER,
						THUMB,
						OUTERLITTLEFINGER,
						INNERLITTLEFINGER,
						OUTERTHUMB,
						INNERTHUMB
				};

				class e_limb_side_c
				{
					public:
						static std::string str(e_limb_side lside);
						static std::vector<e_limb_side> vec();
						static e_limb_side parse(std::string str);
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_LIMB_SIDE_H_
