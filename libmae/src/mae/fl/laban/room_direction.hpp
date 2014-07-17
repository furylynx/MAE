/*
 * room_direction.hpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#ifndef ROOM_DIRECTION_HPP_
#define ROOM_DIRECTION_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
#include "i_movement.hpp"
#include "mv/pin.hpp"

//global includes
#include <string>
#include <sstream>
#include <stdexcept>
#include <ios>
#include <iomanip>
#include <memory>


namespace mae
{
	namespace fl
	{
		namespace laban
		{

			class room_direction: public i_movement
			{
				public:
					room_direction(unsigned int measure, double beat, std::shared_ptr<mv::pin> direction);
					virtual ~room_direction();

					unsigned int get_measure();
					double get_beat();
					std::shared_ptr<mv::pin> get_direction();

					virtual std::string xml(unsigned int indent = 0, std::string namesp = "");

				private:
					unsigned int measure_;
					double beat_;
					std::shared_ptr<mv::pin> direction_;

			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // ROOM_DIRECTION_HPP_
