/*
 * mae_res.hpp
 *
 *  Created on: 29.09.2014
 *      Author: keks
 */

#ifndef MAE_RES_HPP_
#define MAE_RES_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
//...

//global includes
//...

namespace mae
{
	namespace demo
	{

		struct mae_res
		{
				unsigned int size;
//				unsigned int width;
//				unsigned int height;
//				unsigned int bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */
				const void* data;
		};

	} // namespace demo
} // namespace mae

#endif // MAE_RES_HPP_
