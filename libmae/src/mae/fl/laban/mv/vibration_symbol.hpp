/*
 * vibration_symbol.hpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#ifndef VIBRATION_SYMBOL_HPP_
#define VIBRATION_SYMBOL_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "i_symbol.hpp"
#include "pin.hpp"
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

				class vibration_symbol: public i_symbol
				{
					public:
						vibration_symbol(std::shared_ptr<pin> displacement1, std::shared_ptr<pin> displacement2, std::shared_ptr<i_dynamics_sign> dynamics = nullptr);
						virtual ~vibration_symbol();

						std::shared_ptr<i_dynamics_sign> get_dynamics();
						std::shared_ptr<pin> get_displacement1();
						std::shared_ptr<pin> get_displacement2();

						virtual std::string xml(unsigned int indent = 0, std::string namesp = "");

					private:
						std::shared_ptr<i_dynamics_sign> dynamics_;
						std::shared_ptr<pin> displacement1_;
						std::shared_ptr<pin> displacement2_;

				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // VIBRATION_SYMBOL_HPP_
