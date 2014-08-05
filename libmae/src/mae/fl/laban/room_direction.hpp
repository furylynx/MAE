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
					/**
					 * Creates a room direction sign.
					 *
					 * @param measure The measure in which this symbol is placed.
					 * @param beat The beat where this symbol is placed.
					 * @param direction The direction of the room.
					 */
					room_direction(unsigned int measure, double beat, std::shared_ptr<mv::pin> direction);
					virtual ~room_direction();

					/**
					 * Returns the measure in which this symbol is placed.
					 * @return
					 */
					unsigned int get_measure();

					/**
					 * Returns the beat in which this symbol is placed.
					 *
					 * @return
					 */
					double get_beat();

					/**
					 * Returns the room direction.
					 *
					 * @return
					 */
					std::shared_ptr<mv::pin> get_direction();

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
					unsigned int measure_;
					double beat_;
					std::shared_ptr<mv::pin> direction_;

			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // ROOM_DIRECTION_HPP_
