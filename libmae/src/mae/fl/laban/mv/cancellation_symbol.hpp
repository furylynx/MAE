/*
 * cancellation_symbol.hpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#ifndef CANCELLATION_SYMBOL_HPP_
#define CANCELLATION_SYMBOL_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "i_symbol.hpp"
#include "e_cancel.hpp"

//global includes
#include <string>
#include <sstream>
#include <stdexcept>

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				class cancellation_symbol : public i_symbol
				{
					public:
						cancellation_symbol(e_cancel cancel);
						virtual ~cancellation_symbol();

						e_cancel get_cancel();

						virtual std::string xml(unsigned int indent = 0, std::string namesp = "");

					private:
						e_cancel cancel_;
				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // CANCELLATION_SYMBOL_HPP_
