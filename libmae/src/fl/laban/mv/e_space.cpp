/*
 * e_space.cpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#include "e_space.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{
				std::string e_space_str::str(e_space space)
				{
					switch (space)
					{
					case e_space::NONE    		: return "none";
					case e_space::NARROW  		: return "narrow";
					case e_space::WIDE    		: return "wide";
					case e_space::FOLDING 		: return "folding";
					case e_space::UNFOLDING		: return "unfolding";
					case e_space::JOINING 		: return "joining";
					case e_space::SPREADING		: return "spreading";
					}
				};



			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
