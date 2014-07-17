/*
 * e_area.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef E_AREA_HPP_
#define E_AREA_HPP_

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

				enum class e_area
				{
						NONE,
						HEAD,
						CHEST,
						WAIST,
						PELVIS,
						TORSO
				};

				class e_area_c
				{
					public:
						static std::string str(e_area area);
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_AREA_HPP_
