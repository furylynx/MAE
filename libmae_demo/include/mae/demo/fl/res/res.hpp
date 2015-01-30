/*
 * res.hpp
 *
 *  Created on: 12.10.2014
 *      Author: keks
 */

#ifndef RES_HPP_
#define RES_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "../../mae_res.hpp"

#include "laban_direction1.png.h"
#include "laban_direction2.png.h"
#include "laban_direction3.png.h"
#include "laban_direction4.png.h"
#include "laban_direction5.png.h"
#include "laban_direction6.png.h"
#include "laban_direction7.png.h"
#include "laban_direction8.png.h"
#include "laban_direction9.png.h"
#include "laban_direction10.png.h"
#include "laban_direction11.png.h"
#include "laban_direction12.png.h"
#include "laban_direction13.png.h"
#include "laban_direction14.png.h"
#include "laban_direction15.png.h"
#include "laban_direction16.png.h"
#include "laban_direction17.png.h"
#include "laban_direction18.png.h"
#include "laban_direction19.png.h"
#include "laban_direction20.png.h"
#include "laban_direction21.png.h"
#include "laban_direction22.png.h"
#include "laban_direction23.png.h"
#include "laban_direction24.png.h"
#include "laban_direction25.png.h"
#include "laban_direction26.png.h"
#include "laban_direction27.png.h"
#include "laban_direction28.png.h"
#include "laban_direction29.png.h"
#include "laban_direction30.png.h"
#include "laban_direction31.png.h"
#include "laban_direction32.png.h"
#include "laban_direction33.png.h"

#include "background0.png.h"

#include "droidsans.ttf.h"

#include "directions_handler.hpp"

//global includes
//...

namespace mae
{
	namespace demo
	{
		namespace fl
		{
			namespace res
			{
				static unsigned char data_laban_dir_1 [] = MAE_LABAN_DIRECTION1_DATA ;
				static unsigned char data_laban_dir_2 [] = MAE_LABAN_DIRECTION2_DATA ;
				static unsigned char data_laban_dir_3 [] = MAE_LABAN_DIRECTION3_DATA ;
				static unsigned char data_laban_dir_4 [] = MAE_LABAN_DIRECTION4_DATA ;
				static unsigned char data_laban_dir_5 [] = MAE_LABAN_DIRECTION5_DATA ;
				static unsigned char data_laban_dir_6 [] = MAE_LABAN_DIRECTION6_DATA ;
				static unsigned char data_laban_dir_7 [] = MAE_LABAN_DIRECTION7_DATA ;
				static unsigned char data_laban_dir_8 [] = MAE_LABAN_DIRECTION8_DATA ;
				static unsigned char data_laban_dir_9 [] = MAE_LABAN_DIRECTION9_DATA ;
				static unsigned char data_laban_dir_10[] = MAE_LABAN_DIRECTION10_DATA;
				static unsigned char data_laban_dir_11[] = MAE_LABAN_DIRECTION11_DATA;
				static unsigned char data_laban_dir_12[] = MAE_LABAN_DIRECTION12_DATA;
				static unsigned char data_laban_dir_13[] = MAE_LABAN_DIRECTION13_DATA;
				static unsigned char data_laban_dir_14[] = MAE_LABAN_DIRECTION14_DATA;
				static unsigned char data_laban_dir_15[] = MAE_LABAN_DIRECTION15_DATA;
				static unsigned char data_laban_dir_16[] = MAE_LABAN_DIRECTION16_DATA;
				static unsigned char data_laban_dir_17[] = MAE_LABAN_DIRECTION17_DATA;
				static unsigned char data_laban_dir_18[] = MAE_LABAN_DIRECTION18_DATA;
				static unsigned char data_laban_dir_19[] = MAE_LABAN_DIRECTION19_DATA;
				static unsigned char data_laban_dir_20[] = MAE_LABAN_DIRECTION20_DATA;
				static unsigned char data_laban_dir_21[] = MAE_LABAN_DIRECTION21_DATA;
				static unsigned char data_laban_dir_22[] = MAE_LABAN_DIRECTION22_DATA;
				static unsigned char data_laban_dir_23[] = MAE_LABAN_DIRECTION23_DATA;
				static unsigned char data_laban_dir_24[] = MAE_LABAN_DIRECTION24_DATA;
				static unsigned char data_laban_dir_25[] = MAE_LABAN_DIRECTION25_DATA;
				static unsigned char data_laban_dir_26[] = MAE_LABAN_DIRECTION26_DATA;
				static unsigned char data_laban_dir_27[] = MAE_LABAN_DIRECTION27_DATA;
				static unsigned char data_laban_dir_28[] = MAE_LABAN_DIRECTION28_DATA;
				static unsigned char data_laban_dir_29[] = MAE_LABAN_DIRECTION29_DATA;
				static unsigned char data_laban_dir_30[] = MAE_LABAN_DIRECTION30_DATA;
				static unsigned char data_laban_dir_31[] = MAE_LABAN_DIRECTION31_DATA;
				static unsigned char data_laban_dir_32[] = MAE_LABAN_DIRECTION32_DATA;
				static unsigned char data_laban_dir_33[] = MAE_LABAN_DIRECTION33_DATA;

				static unsigned char data_background0[] = MAE_BACKGROUND0_DATA;

				static const mae_res background0 = {MAE_BACKGROUND0_SIZE, data_background0 };

				const int laban_res_size = 33;
				static const mae_res laban_res[laban_res_size]
				{
					{MAE_LABAN_DIRECTION1_SIZE   , data_laban_dir_1 } ,
					{MAE_LABAN_DIRECTION2_SIZE   , data_laban_dir_2 } ,
					{MAE_LABAN_DIRECTION3_SIZE   , data_laban_dir_3 } ,
					{MAE_LABAN_DIRECTION4_SIZE   , data_laban_dir_4 } ,
					{MAE_LABAN_DIRECTION5_SIZE   , data_laban_dir_5 } ,
					{MAE_LABAN_DIRECTION6_SIZE   , data_laban_dir_6 } ,
					{MAE_LABAN_DIRECTION7_SIZE   , data_laban_dir_7 } ,
					{MAE_LABAN_DIRECTION8_SIZE   , data_laban_dir_8 } ,
					{MAE_LABAN_DIRECTION9_SIZE   , data_laban_dir_9 } ,
					{MAE_LABAN_DIRECTION10_SIZE  , data_laban_dir_10} ,
					{MAE_LABAN_DIRECTION11_SIZE  , data_laban_dir_11} ,
					{MAE_LABAN_DIRECTION12_SIZE  , data_laban_dir_12} ,
					{MAE_LABAN_DIRECTION13_SIZE  , data_laban_dir_13} ,
					{MAE_LABAN_DIRECTION14_SIZE  , data_laban_dir_14} ,
					{MAE_LABAN_DIRECTION15_SIZE  , data_laban_dir_15} ,
					{MAE_LABAN_DIRECTION16_SIZE  , data_laban_dir_16} ,
					{MAE_LABAN_DIRECTION17_SIZE  , data_laban_dir_17} ,
					{MAE_LABAN_DIRECTION18_SIZE  , data_laban_dir_18} ,
					{MAE_LABAN_DIRECTION19_SIZE  , data_laban_dir_19} ,
					{MAE_LABAN_DIRECTION20_SIZE  , data_laban_dir_20} ,
					{MAE_LABAN_DIRECTION21_SIZE  , data_laban_dir_21} ,
					{MAE_LABAN_DIRECTION22_SIZE  , data_laban_dir_22} ,
					{MAE_LABAN_DIRECTION23_SIZE  , data_laban_dir_23} ,
					{MAE_LABAN_DIRECTION24_SIZE  , data_laban_dir_24} ,
					{MAE_LABAN_DIRECTION25_SIZE  , data_laban_dir_25} ,
					{MAE_LABAN_DIRECTION26_SIZE  , data_laban_dir_26} ,
					{MAE_LABAN_DIRECTION27_SIZE  , data_laban_dir_27} ,
					{MAE_LABAN_DIRECTION28_SIZE  , data_laban_dir_28} ,
					{MAE_LABAN_DIRECTION29_SIZE  , data_laban_dir_29} ,
					{MAE_LABAN_DIRECTION30_SIZE  , data_laban_dir_30} ,
					{MAE_LABAN_DIRECTION31_SIZE  , data_laban_dir_31} ,
					{MAE_LABAN_DIRECTION32_SIZE  , data_laban_dir_32} ,
					{MAE_LABAN_DIRECTION33_SIZE  , data_laban_dir_33} ,
				};

				static unsigned char data_droidsans[] = MAE_DROIDSANS_DATA;

				static const mae_res droidsans_ttf = {MAE_DROIDSANS_SIZE, data_droidsans };

			} // namespace res
		} // namespace fl
	} // namespace demo
} // namespace mae


#endif // RES_HPP_
