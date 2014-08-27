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
#include <iostream>
#include <memory>

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

						/**
						 * Returns the string representation for this element.
						 *
						 * @return The string.
						 */
						virtual std::string str() const = 0;

						friend std::ostream& operator<<(std::ostream& os, const i_symbol& obj)
						{
							os << obj.str();
							return os;
						}

						friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<i_symbol>& obj)
						{
							os << obj->str();
							return os;
						}
				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // I_SYMBOL_HPP_
