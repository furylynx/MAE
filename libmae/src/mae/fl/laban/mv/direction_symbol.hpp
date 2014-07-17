/*
 * direction_symbol.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef DIRECTION_SYMBOL_HPP_
#define DIRECTION_SYMBOL_HPP_

//eclipse indexer fix
#include "../../../indexer_fix.hpp"

//custom includes
#include "i_symbol.hpp"
#include "e_level.hpp"
#include "e_direction.hpp"
#include "e_contact_hook.hpp"
#include "i_dynamics_sign.hpp"
#include "space_measurement.hpp"
#include "pin.hpp"

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

				class direction_symbol: public i_symbol
				{
					public:
						direction_symbol(e_level vertical, e_direction horizontal, std::shared_ptr<pin> modification_pin = nullptr, std::shared_ptr<pin> relationship_pin = nullptr, std::shared_ptr<i_dynamics_sign> dynamics = nullptr, std::shared_ptr<space_measurement> space_measurement = nullptr, e_contact_hook contact_hook = e_contact_hook::NONE);
						virtual ~direction_symbol();

						e_level get_vertical();
						e_direction get_horizontal();
						std::shared_ptr<pin> get_modification_pin();
						std::shared_ptr<pin> get_relationship_pin();
						std::shared_ptr<i_dynamics_sign> get_dynamics();
						std::shared_ptr<space_measurement> get_space_measurement();
						e_contact_hook get_contact_hook();

						virtual std::string xml(unsigned int indent = 0, std::string namesp = "");


					private:
						e_level vertical_;
						e_direction horizontal_;
						std::shared_ptr<pin> modification_pin_;
						std::shared_ptr<pin> relationship_pin_;
						std::shared_ptr<i_dynamics_sign> dynamics_;
						std::shared_ptr<space_measurement> space_measurement_;
						e_contact_hook contact_hook_;
				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // DIRECTION_SYMBOL_HPP_
