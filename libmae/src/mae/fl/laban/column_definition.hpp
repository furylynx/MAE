/*
 * laban_column.hpp
 *
 *  Created on: 07.07.2014
 *      Author: keks
 */

#ifndef COLUMN_DEFINITION_HPP_
#define COLUMN_DEFINITION_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
#include "ps/i_pre_sign.hpp"

//global includes
#include <string>
#include <sstream>
#include <stdexcept>
#include <memory>

namespace mae
{
	namespace fl
	{
		namespace laban
		{

		class column_definition
		{
			public:
				/**
				 * Creates a new column definition.
				 *
				 * @param column_index The index of the column.
				 * @param pre_sign The pre-sign.
				 */
				column_definition(int column_index, std::shared_ptr<ps::i_pre_sign> pre_sign);

				virtual ~column_definition();

				/**
				 * Returns the column index. This specifies the addressed column in the chart.
				 *
				 * @return
				 */
				int get_column_index();

				/**
				 * Returns the pre-sign.
				 *
				 * @return
				 */
				std::shared_ptr<ps::i_pre_sign> get_pre_sign();

				/**
				 * Returns the XML representation for this element.
				 *
				 * @param indent The applied indent.
				 * @param namesp The prefixed XML namespace.
				 *
				 * @return The XML string.
				 */
				virtual std::string xml(unsigned int indent = 0, std::string namesp = "");

			private:
				int column_index_;
				std::shared_ptr<ps::i_pre_sign> pre_sign_;

		};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // LABAN_COLUMN_HPP_
