/*
 * i_degree_sign.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef I_DEGREE_SIGN_HPP_
#define I_DEGREE_SIGN_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
//...

//global includes
#include <string>
#include <memory>

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				class i_degree_sign
				{
					public:
						virtual ~i_degree_sign(){}

						virtual bool equals(std::shared_ptr<i_degree_sign> a);

						virtual std::string xml(unsigned int indent = 0, std::string namesp = "") = 0;
				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // I_DEGREE_SIGN_HPP_
