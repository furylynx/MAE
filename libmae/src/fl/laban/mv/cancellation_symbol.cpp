/*
 * cancellation_symbol.cpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#include "cancellation_symbol.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				cancellation_symbol::cancellation_symbol(e_cancel cancel)
				{
					cancel_ = cancel;

					if (cancel == e_cancel::NONE)
					{
						throw std::invalid_argument("Cancel must not be NONE.");
					}
				}

				cancellation_symbol::~cancellation_symbol()
				{
				}

				e_cancel cancellation_symbol::get_cancel()
				{
					return cancel_;
				}

				std::string cancellation_symbol::xml(unsigned int indent)
				{
					std::stringstream indent_stream;

					for (unsigned int i = 0; i < indent; i++)
					{
						indent_stream << "\t";
					}

					std::stringstream sstr;

					//print cancel symbol
					sstr << indent_stream.str() << "<cancel>" << std::endl;

					sstr << indent_stream.str() << "\t" << "<cancel>" << e_cancel_str::str(cancel_) << "</cancel>" << std::endl;

					sstr << indent_stream.str() << "</cancel>" << std::endl;

					return sstr.str();

				}


			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
