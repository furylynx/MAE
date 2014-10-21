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

					if (cancel == e_cancel::NONE_CANCEL)
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

				bool cancellation_symbol::equals(std::shared_ptr<i_symbol> a)
				{
					if (std::shared_ptr<cancellation_symbol> a_c = std::dynamic_pointer_cast<cancellation_symbol>(a))
					{
						if (a_c->get_cancel() == cancel_)
						{
							return true;
						}
					}

					return false;
				}

				std::string cancellation_symbol::xml(unsigned int indent, std::string namesp)
				{
					std::stringstream indent_stream;

					for (unsigned int i = 0; i < indent; i++)
					{
						indent_stream << "\t";
					}

					std::string ns = namesp;
					if (ns.size() > 0 && ns.at(ns.size()-1) != ':')
					{
						ns.push_back(':');
					}

					std::stringstream sstr;

					//print cancel symbol
					sstr << indent_stream.str() << "<" << ns << "cancel>" << std::endl;

					sstr << indent_stream.str() << "\t" << "<" << ns << "cancel>" << e_cancel_c::str(cancel_) << "</" << ns << "cancel>" << std::endl;

					sstr << indent_stream.str() << "</" << ns << "cancel>" << std::endl;

					return sstr.str();

				}

				std::string cancellation_symbol::svg(std::string identifier, double posx, double posy, double width, double height, bool left)
				{
					std::stringstream sstr;

					//TODO

					return sstr.str();
				}

				std::string cancellation_symbol::str() const
				{
					std::stringstream sstr;

					sstr << "(" << e_cancel_c::str(cancel_) << ")";

					return sstr.str();
				}

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
