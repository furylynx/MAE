/*
 * e_path_type.hpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#ifndef E_PATH_TYPE_HPP_
#define E_PATH_TYPE_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
//...

//global includes
#include <string>

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			enum class e_path_type
			{
					NONE,
					STRAIGHT,
					CIRCULAR_LEFT,
					CIRCULAR_RIGHT,
					ANY
			};

			class e_path_type_str
			{
				public:
					static std::string str(e_path_type type);
			};


		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_PATH_TYPE_HPP_
