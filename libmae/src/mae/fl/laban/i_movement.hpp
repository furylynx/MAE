#ifndef MAE_FL_LABAN_I_MOVEMENT_HPP_
#define MAE_FL_LABAN_I_MOVEMENT_HPP_

//custom includes
#include "draw_laban_rect.hpp"
#include "svg_style.hpp"

//global includes
#include <string>
#include <memory>
#include <iostream>
#include <map>
#include <vector>
#include <typeindex>

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
					 * Returns the duration of the symbol in beats. Room direction symbols do not have a duration and will return 0.
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
					 * Returns true if the symbols and all subelements have the same type making them comparable by feature vectors.
					 *
					 * @param a The movement to be compared to.
					 * @return True if types equal.
					 */
					virtual bool all_types_equal(std::shared_ptr<i_movement> a) const = 0;

					/**
					 * Returns the symbol's feature vector without the length and position information.
					 *
					 * @param hierarchy_factor The factor for subelements.
					 * @return The feature vector.
					 */
					virtual std::vector<double> symbol_feature_vector(double hierarchy_factor = 0.5) const = 0;

					/**
					 * Returns the path of the type hierarchy beginning with the i_movement type. The path can be used to compare elements by their position in the hierarchy. Uses the shortest path if multiple paths are possible (diamond hierarchy).
					 *
					 * @return The path from the current type to the i_movement type.
					 */
					virtual std::vector<std::type_index> get_type_path() const = 0;

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
					 * @param im_width The im_width.
					 * @param im_height The im_height.
					 * @param max_column The max_column.
					 * @param measures The measures.
					 * @param beats_per_measure beats_per_measure
					 * @return The SVG.
					 */
					virtual std::string svg(unsigned int im_width, unsigned int im_height, unsigned int max_column, unsigned int measures, unsigned int beats_per_measure) const = 0;

                    /**
                     * Returns the SVG representation for this element.
                     *
                     * @param rect The laban rectangle.
                     * @param style The svg style.
                     * @return The SVG.
                     */
                    virtual std::string svg(draw_laban_rect rect, svg_style style = svg_style()) const = 0;

					/**
					 * Recreates the movement by copying its members but changing the position in the staff.
					 *
					 * @param column_mapping The mapping for columns. Maps old columns to new ones.
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

#endif // MAE_FL_LABAN_I_MOVEMENT_HPP_
