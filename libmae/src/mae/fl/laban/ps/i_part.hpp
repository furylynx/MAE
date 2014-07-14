/*
 * i_part.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef I_PART_HPP_
#define I_PART_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

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
			namespace ps
			{

				class i_part
				{
					public:
						virtual ~i_part(){}

						virtual std::string xml(unsigned int indent = 0) = 0;
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // I_PART_HPP_
