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

				class e_limb_side_str
				{
					public:
						static std::string str(e_limb_side lside);
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_LIMB_SIDE_H_
