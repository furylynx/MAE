/*
 * labanmovement.hpp
 *
 *  Created on: 07.07.2014
 *      Author: keks
 */

#ifndef MOVEMENT_HPP_
#define MOVEMENT_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
#include "i_movement.hpp"
#include "ps/i_pre_sign.hpp"
#include "mv/i_symbol.hpp"

//global includes
#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>
#include <ios>
#include <iomanip>


namespace mae
{
	namespace fl
	{
		namespace laban
		{

		class movement : public i_movement
		{
			public:
				movement(int column, unsigned int measure, double beat, double duration, std::shared_ptr<mv::i_symbol> symbol, bool hold = false, std::shared_ptr<ps::i_pre_sign> pre_sign = nullptr);
				virtual ~movement();

				int get_column();
				unsigned int get_measure();
				double get_beat();
				double get_duration();
				std::shared_ptr<ps::i_pre_sign> get_pre_sign();
				bool get_hold();
				std::shared_ptr<mv::i_symbol> get_symbol();

				virtual std::string xml(unsigned int indent = 0, std::string namesp = "");

			private:
				int column_;
				unsigned int measure_;
				double beat_;
				double duration_;
				std::shared_ptr<ps::i_pre_sign> pre_sign_;
				bool hold_;
				std::shared_ptr<mv::i_symbol> symbol_;

		};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // LABANMOVEMENT_HPP_
