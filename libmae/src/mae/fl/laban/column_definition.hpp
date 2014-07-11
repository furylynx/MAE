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
				 * Prints the xml representation for this element to a string.
				 *
				 * @param indent The number of tab indent.
				 * @return The xml string.
				 */
				virtual std::string xml(unsigned int indent = 0);

			private:
				int column_index_;
				std::shared_ptr<ps::i_pre_sign> pre_sign_;

		};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // LABAN_COLUMN_HPP_
