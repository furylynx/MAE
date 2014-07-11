/*
 * e_space.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef E_SPACE_HPP_
#define E_SPACE_HPP_

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

				enum class e_space
				{
						NONE,
						NARROW,
						WIDE,
						FOLDING,
						UNFOLDING,
						JOINING,
						SPREADING
				};

				class e_space_str
				{
					public:
						static std::string str(e_space space);
				};


			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_SPACE_HPP_
