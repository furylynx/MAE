/*
 * i_movement.hpp
 *
 *  Created on: 10.07.2014
 *      Author: keks
 */

#ifndef I_MOVEMENT_HPP_
#define I_MOVEMENT_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
//...

//global includes
#include <string>
#include <memory>
#include <iostream>
#include <map>

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			class i_movement
			{
				public:
					virtual ~i_movement(){}

					/**
					 * Returns the column this movement is attached to. Room direction
					 * and path sign have their own specific column only for those signs
					 * and therefore return 0.
					 *
					 * @return The column id.
					 */
					virtual int get_column() const = 0;

					/**
					 * Returns the measure in which this symbols begins.
					 * @return
					 */
					virtual unsigned int get_measure() const = 0;

					/**
					 * Returns the beat in which this symbol begins.
					 *
					 * @return
					 */
					virtual double get_beat() const = 0;

					/**
					 * Returns the duration of the symbol. Room direction symbols do not have a duration and will return 0.
					 *
					 * @return
					 */
					virtual double get_duration() const = 0;

					/**
					 * Returns true if the i_movement elements are equal.
					 *
					 * @param a The movement to be compared to.
					 * @return True if equal.
					 */
					virtual bool equals(std::shared_ptr<i_movement> a) const = 0;

					/**
					 * Returns true if the symbols are equal. The position and duration are not regarded.
					 *
					 * @param a The movement to be compared to.
					 * @return True if symbols equal.
					 */
					virtual bool symbol_equals(std::shared_ptr<i_movement> a) const = 0;

					/**
					 * Returns the XML representation for this element.
					 *
					 * @param indent The applied indent.
					 * @param namesp The prefixed XML namespace.
					 *
					 * @return The XML string.
					 */
					virtual std::string xml(unsigned int indent = 0, std::string namesp = "") const = 0;

					/**
					 * Returns the SVG representation for this element.
					 *
					 * @param posx The x pos.
					 * @param posy The y pos.
					 * @param width The width.
					 * @param height The height.
					 * @return The SVG.
					 */
					virtual std::string svg(unsigned int im_width, unsigned int im_height, unsigned int max_column, unsigned int measures, unsigned int beats_per_measure) const = 0;

					/**
					 * Recreates the movement by copying its members but changing the position in the staff.
					 *
					 * @param column The new column.
					 * @param measure The new measure.
					 * @param beat The new beat.
					 * @param duration The new duration.
					 * @return The new, recreated movement.
					 */
					virtual std::shared_ptr<i_movement> recreate(std::map<int, int> column_mapping, unsigned int measure, double beat, double duration) const = 0;

					/**
					 * Returns the string representation for this element.
					 *
					 * @return The string.
					 */
					virtual std::string str() const = 0;

					friend std::ostream& operator<<(std::ostream& os, const i_movement& obj)
					{
						os << obj.str();
						return os;
					}

					friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<i_movement>& obj)
					{
						os << obj->str();
						return os;
					}

			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // I_MOVEMENT_HPP_
