/*
 * accent_sign.cpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#include "accent_sign.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				accent_sign::accent_sign(unsigned int accent)
				{
					accent_ = accent;

					if (accent > 5 || accent == 0)
					{
						throw std::invalid_argument("Accent must be a value between 1 and 5.");
					}
				}

				accent_sign::~accent_sign()
				{
				}

				unsigned int accent_sign::get_accent()
				{
					return accent_;
				}

				std::string accent_sign::xml(unsigned int indent)
				{
					std::stringstream indent_stream;

					for (unsigned int i = 0; i < indent; i++)
					{
						indent_stream << "\t";
					}

					std::stringstream sstr;

					//print accent sign
					sstr << indent_stream.str() << "<dynamics>" << std::endl;

					sstr << indent_stream.str() << "\t" << "<accent>" << accent_ << "</accent>" << std::endl;

					sstr << indent_stream.str() << "</dynamics>" << std::endl;

					return sstr.str();
				}

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
