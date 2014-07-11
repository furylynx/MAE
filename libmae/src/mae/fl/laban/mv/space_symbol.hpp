/*
 * space_symbol.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef SPACE_SYMBOL_HPP_
#define SPACE_SYMBOL_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "i_symbol.hpp"
#include "space_measurement.hpp"
#include "i_dynamics_sign.hpp"

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
			namespace mv
			{

				class space_symbol: public i_symbol
				{
					public:
						space_symbol(std::shared_ptr<space_measurement> space_measurement, std::shared_ptr<i_dynamics_sign> dynamics = nullptr);
						virtual ~space_symbol();

						std::shared_ptr<i_dynamics_sign> get_dynamics();
						std::shared_ptr<space_measurement> get_space_measurement();

						virtual std::string xml(unsigned int indent = 0);

					private:
						std::shared_ptr<i_dynamics_sign> dynamics_;
						std::shared_ptr<space_measurement> space_measurement_;

				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // SPACE_SYMBOL_HPP_
