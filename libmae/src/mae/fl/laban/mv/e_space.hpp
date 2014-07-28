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

				class e_space_c
				{
					public:
						static std::string str(e_space space);
						static std::vector<e_space> vec();
						static e_space parse(std::string str);
				};


			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_SPACE_HPP_
