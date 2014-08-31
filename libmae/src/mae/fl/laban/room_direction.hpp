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
					 * Returns the column to which this symbol was added. Since a room direction sign is
					 * placed in its own column zero is returned.
					 *
					 * @return
					 */
					virtual int get_column() const;

					/**
					 * Returns the measure in which this symbol is placed.
					 * @return
					 */
					virtual unsigned int get_measure() const;

					/**
					 * Returns the beat in which this symbol is placed.
					 *
					 * @return
					 */
					virtual double get_beat() const;

					/**
					 * Returns the duration of the symbol. Since a room direction symbol
					 * has no duration zero is returned.
					 *
					 * @return Zero.
					 */
					virtual double get_duration() const;

					/**
					 * Returns the room direction.
					 *
					 * @return
					 */
					std::shared_ptr<mv::pin> get_direction() const;

					/**
					 * Returns the XML representation for this element.
					 *
					 * @param indent The applied indent.
					 * @param namesp The prefixed XML namespace.
					 *
					 * @return The XML string.
					 */
					virtual std::string xml(unsigned int indent = 0, std::string namesp = "");

					/**
					 * Recreates the movement by copying its members but changing the position in the staff.
					 *
					 * @param column The new column.
					 * @param measure The new measure.
					 * @param beat The new beat.
					 * @param duration The new duration.
					 * @return The new, recreated movement.
					 */
					virtual std::shared_ptr<i_movement> recreate(std::unordered_map<int, int> column_mapping, unsigned int measure, double beat, double duration) const;


					/**
					 * Returns the string representation for this element.
					 *
					 * @return The string.
					 */
					virtual std::string str() const;

					friend std::ostream& operator<<(std::ostream& os, const room_direction& obj)
					{
						os << obj.str();
						return os;
					}

					friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<room_direction>& obj)
					{
						os << obj->str();
						return os;
					}


				private:
					unsigned int measure_;
					double beat_;
					std::shared_ptr<mv::pin> direction_;

			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // ROOM_DIRECTION_HPP_
