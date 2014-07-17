/*
 * e_cancel.cpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#include "e_cancel.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				std::string e_cancel_c::str(e_cancel cancel)
				{
					switch (cancel)
					{
					case e_cancel::NONE           		: return "none";
					case e_cancel::BACK_NORMAL    		: return "back-normal";
					case e_cancel::RELEASE_CONTACT 		: return "release-contact";
					}

					throw std::invalid_argument("Enum value not listed in the str() method");
				}


			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
