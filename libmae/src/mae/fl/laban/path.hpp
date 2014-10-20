/*
 * path.hpp
 *
 *  Created on: 11.07.2014
 *      Author: keks
 */

#ifndef PATH_HPP_
#define PATH_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
#include "i_movement.hpp"
#include "e_path_type.hpp"

//global includes
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

			class path: public i_movement
			{
				public:
					/**
					 * Creates a path symbol.
					 *
					 * @param type The type of the path.
					 * @param measure The measure in which this symbol is placed.
					 * @param beat The beat mark of the measure where this symbol begins.
					 * @param duration The duration of the symbol (in beats).
					 */
					path(e_path_type type, unsigned int measure, double beat, double duration);

					virtual ~path();

					/**
					 * Returns the type of the path.
					 *
					 * @return
					 */
					e_path_type get_type() const;

					/**
					 * Returns the column to which this symbol was added. Since a path symbol is placed
					 * in its own column zero is returned.
					 *
					 * @return Zero.
					 */
					virtual int get_column() const;

					/**
					 * Returns the measure in which this symbol is placed.
					 * @return
					 */
					virtual unsigned int get_measure() const;

					/**
					 * Returns the beat where this symbol starts.
					 * @return
					 */
					virtual double get_beat() const;

					/**
					 * Returns the duration of the symbol in beats.
					 *
					 * @return
					 */
					virtual double get_duration() const;

					/**
					 * Returns true if the i_movement elements are equal.
					 *
					 * @param a The movement to be compared to.
					 * @return True if equal.
					 */
					virtual bool equals(std::shared_ptr<i_movement> a) const;

					/**
					 * Returns true if the symbols are equal. The position and duration are not regarded.
					 *
					 * @param a The movement to be compared to.
					 * @return True if symbols equal.
					 */
					virtual bool symbol_equals(std::shared_ptr<i_movement> a) const;

					/**
					 * Returns the XML representation for this element.
					 *
					 * @param indent The applied indent.
					 * @param namesp The prefixed XML namespace.
					 *
					 * @return The XML string.
					 */
					virtual std::string xml(unsigned int indent = 0, std::string namesp = "") const;

					/**
					 * Returns the SVG representation for this element.
					 *
					 * @param posx The x pos.
					 * @param posy The y pos.
					 * @param width The width.
					 * @param height The height.
					 * @return The SVG.
					 */
					virtual std::string svg(unsigned int im_width, unsigned int im_height, unsigned int max_column, unsigned int measures, unsigned int beats_per_measure) const;

					/**
					 * Recreates the movement by copying its members but changing the position in the staff.
					 *
					 * @param column The new column.
					 * @param measure The new measure.
					 * @param beat The new beat.
					 * @param duration The new duration.
					 * @return The new, recreated movement.
					 */
					virtual std::shared_ptr<i_movement> recreate(std::map<int, int> column_mapping, unsigned int measure, double beat, double duration) const;


					/**
					 * Returns the string representation for this element.
					 *
					 * @return The string.
					 */
					virtual std::string str() const;

					friend std::ostream& operator<<(std::ostream& os, const path& obj)
					{
						os << obj.str();
						return os;
					}

					friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<path>& obj)
					{
						os << obj->str();
						return os;
					}


				private:
					e_path_type type_;
					unsigned int measure_;
					double beat_;
					double duration_;

			};

		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // PATH_HPP_
