/*
 * e_digit.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef E_DIGIT_HPP_
#define E_DIGIT_HPP_

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

				enum class e_digit
				{
						NONE,
						THUMB,
						INDEXFINGER,
						MIDDLEFINGER,
						RINGFINGER,
						LITTLEFINGER,
						BIGTOE,
						LONGTOE,
						MIDDLETOE,
						RINGTOE,
						LITTLETOE
				};

				class e_digit_c
				{
					public:
						static std::string str(e_digit digit);
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // E_DIGIT_HPP_
