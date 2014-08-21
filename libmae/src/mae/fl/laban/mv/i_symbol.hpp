/*
 * i_symbol.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef I_SYMBOL_HPP_
#define I_SYMBOL_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
//...

//global includes
#include <memory>
#include <string>

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				class i_symbol
				{
					public:
						virtual ~i_symbol(){}

						virtual bool equals(std::shared_ptr<i_symbol> a) = 0;

						virtual std::string xml(unsigned int indent = 0, std::string namesp = "") = 0;
				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // I_SYMBOL_HPP_
