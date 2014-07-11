/*
 * turn_symbol.hpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#ifndef TURN_SYMBOL_HPP_
#define TURN_SYMBOL_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "i_symbol.hpp"
#include "i_degree_sign.hpp"
#include "i_dynamics_sign.hpp"
#include "e_turn_direction.hpp"

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

				class turn_symbol: public i_symbol
				{
					public:
						turn_symbol(e_turn_direction direction, std::shared_ptr<i_dynamics_sign> dynamics = nullptr, std::shared_ptr<i_degree_sign> degree = nullptr);
						virtual ~turn_symbol();

						e_turn_direction get_direction();
						std::shared_ptr<i_dynamics_sign> get_dynamics();
						std::shared_ptr<i_degree_sign> get_degree();

						virtual std::string xml(unsigned int indent = 0);

					private:
						e_turn_direction direction_;
						std::shared_ptr<i_dynamics_sign> dynamics_;
						std::shared_ptr<i_degree_sign> degree_;

				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // TURN_SYMBOL_HPP_
