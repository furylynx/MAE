#ifndef MAE_FL_LABAN_ROOM_DIRECTION_HPP_
#define MAE_FL_LABAN_ROOM_DIRECTION_HPP_

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
					 * @return True if types equal.
					 */
					virtual bool symbol_equals(std::shared_ptr<i_movement> a) const;

					/**
					 * Returns true if the symbols and all subelements have the same type making them comparable by feature vectors.
					 *
					 * @param a The movement to be compared to.
					 * @return True if symbols equal.
					 */
					virtual bool all_types_equal(std::shared_ptr<i_movement> a) const;

					/**
					 * Returns the symbol's feature vector without the length and position information.
					 *
					 * @param hierarchy_factor The factor for subelements.
					 * @return The feature vector.
					 */
					virtual std::vector<double> symbol_feature_vector(double hierarchy_factor = 0.5) const;

					/**
					 * Returns the path of the type hierarchy beginning with the i_movement type. The path can be used to compare elements by their position in the hierarchy. Uses the shortest path if multiple paths are possible (diamond hierarchy).
					 *
					 * @return The path from the current type to the i_movement type.
					 */
					virtual std::vector<std::type_index> get_type_path() const;

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

#endif // MAE_FL_LABAN_ROOM_DIRECTION_HPP_
