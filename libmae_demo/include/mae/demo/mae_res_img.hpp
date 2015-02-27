/*
 * mae_res_img.hpp
 *
 *  Created on: 30.09.2014
 *      Author: keks
 */

#ifndef MAE_RES_IMG_HPP_
#define MAE_RES_IMG_HPP_

//eclipse indexer fix
#include "indexer_fix.hpp"

//custom includes
//...

//global includes
//...

namespace mae
{
	namespace demo
	{

		struct mae_res_img
		{
				const int width;
				const int height;
				const int channels;
				const int size;
				const char* data;
		};

	} // namespace demo
} // namespace mae


#endif // MAE_RES_IMG_HPP_
