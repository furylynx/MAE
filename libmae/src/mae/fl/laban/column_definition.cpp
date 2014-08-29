/*
 * laban_column.cpp
 *
 *  Created on: 07.07.2014
 *      Author: keks
 */

#include "column_definition.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			column_definition::column_definition(int column_index, std::shared_ptr<ps::i_pre_sign> pre_sign)
			{
				column_index_ = column_index;
				pre_sign_ = pre_sign;

				if (column_index == -4 || column_index == -2 || column_index == -1 || column_index == 1 || column_index == 2 || column_index == 4 )
				{
					throw std::invalid_argument("Default columns must not be overridden.");
				}

				if (column_index == 0)
				{
					throw std::invalid_argument("Column index must not be zero.");
				}

				if (pre_sign == nullptr)
				{
					throw std::invalid_argument("Pre-sign must not be null.");
				}
			}

			column_definition::~column_definition()
			{

			}

			int column_definition::get_column_index() const
			{
				return column_index_;
			}

			std::shared_ptr<ps::i_pre_sign> column_definition::get_pre_sign() const
			{
				return pre_sign_;
			}

			std::string column_definition::xml(unsigned int indent, std::string namesp) const
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

				//print definition
				sstr << indent_stream.str() << "<" << ns << "columnDefinition>" << std::endl;

				sstr << indent_stream.str() << "\t" << "<" << ns << "index>" << column_index_ << "</" << ns << "index>" << std::endl;

				//print pre sign
				sstr << pre_sign_->xml(indent + 1, namesp);

				sstr << indent_stream.str() << "</" << ns << "columnDefinition>" << std::endl;

				return sstr.str();
			}

			bool column_definition::equals(std::shared_ptr<column_definition> a) const
			{
				return (column_index_ == a->get_column_index() && pre_sign_->equals(a->get_pre_sign()));
			}

		} // namespace laban
	} // namespace fl
} // namespace mae
