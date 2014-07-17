/*
 * e_cancel.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef E_CANCEL_HPP_
#define E_CANCEL_HPP_

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

				enum class e_cancel
				{
						NONE,
						BACK_NORMAL,
						RELEASE_CONTACT
				};

				class e_cancel_c
				{
					public:
						static std::string str(e_cancel cancel);
				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_CANCEL_HPP_
