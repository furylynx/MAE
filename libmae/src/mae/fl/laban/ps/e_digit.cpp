/*
 * e_digit.cpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#include "e_digit.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{

				std::string e_digit_str::str(e_digit digit)
				{
					switch (digit)
					{
						case e_digit::NONE        	: return "none";
						case e_digit::THUMB       	: return "thumb";
						case e_digit::INDEXFINGER 	: return "indexFinger";
						case e_digit::MIDDLEFINGER	: return "middleFinger";
						case e_digit::RINGFINGER  	: return "ringFinger";
						case e_digit::LITTLEFINGER	: return "littleFinger";
						case e_digit::BIGTOE      	: return "bigToe";
						case e_digit::LONGTOE     	: return "longToe";
						case e_digit::MIDDLETOE     : return "middleToe";
						case e_digit::RINGTOE       : return "ringToe";
						case e_digit::LITTLETOE     : return "littleToe";
					}

					throw std::invalid_argument("Enum value not listed in the str() method");
				}



			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae
