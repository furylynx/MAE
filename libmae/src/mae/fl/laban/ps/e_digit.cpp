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

				std::string e_digit_c::str(e_digit digit)
				{
					switch (digit)
					{
						case e_digit::NONE_DIGIT        	: return "none";
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

				std::vector<e_digit> e_digit_c::vec()
				{
					std::vector<e_digit> result;
					result.push_back(e_digit::NONE_DIGIT        	);
					result.push_back(e_digit::THUMB        	);
					result.push_back(e_digit::INDEXFINGER 	);
					result.push_back(e_digit::MIDDLEFINGER 	);
					result.push_back(e_digit::RINGFINGER  	);
					result.push_back(e_digit::LITTLEFINGER 	);
					result.push_back(e_digit::BIGTOE      	);
					result.push_back(e_digit::LONGTOE      	);
					result.push_back(e_digit::MIDDLETOE   	);
					result.push_back(e_digit::RINGTOE      	);
					result.push_back(e_digit::LITTLETOE   	);

					return result;
				}

				e_digit e_digit_c::parse(std::string str)
				{
					std::string str_l = mstr::to_lower(str);

					std::vector<e_digit> v = e_digit_c::vec();

					for (unsigned int i = 0; i < v.size(); i++)
					{
						std::string t = e_digit_c::str(v.at(i));
						if (str_l == mstr::to_lower(t))
						{
							return v.at(i);
						}
					}

					throw std::invalid_argument("Could not parse the given value since no match was found.");
				}


			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae
