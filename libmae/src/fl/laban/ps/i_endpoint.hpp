/*
 * i_endpoint.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef I_ENDPOINT_HPP_
#define I_ENDPOINT_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "i_part.hpp"

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

				class i_endpoint: public i_part
				{
					public:
						virtual ~i_endpoint();

						virtual std::string xml(unsigned int indent = 0) = 0;
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // I_ENDPOINT_HPP_
