#ifndef MAE_FL_LABAN_MOVEMENT_HPP_
#define MAE_FL_LABAN_MOVEMENT_HPP_

//custom includes
#include "i_movement.hpp"
#include "ps/i_pre_sign.hpp"
#include "mv/i_symbol.hpp"

#include "../../math/math.hpp"

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
				/**
				 * Creates a movement element which represents a movement symbol in the
				 * score (e.g. direction and level or a turn) and (if present) a hold sign.
				 *
				 * @param column The column to which this symbol is meant to be added.
				 * @param measure The measure in which this symbol starts (and therefore the motion).
				 * @param beat The beat (decimals allowed) of the measure which is the beginning of the motion.
				 * @param duration The duration of the symbol (given in an amount of beats).
				 * @param symbol The symbol defining the kind of movement (e.g. direction+level or turn)
				 * @param hold If true a hold sign is attached to symbol.
				 * @param pre_sign A pre-sign which can be used to address another body part than the one defined by the column.
				 */
				movement(int column, unsigned int measure, double beat, double duration, std::shared_ptr<mv::i_symbol> symbol, bool hold = false, std::shared_ptr<ps::i_pre_sign> pre_sign = nullptr);
				virtual ~movement();

				/**
				 * Returns the column to which this symbol was added.
				 *
				 * @return
				 */
				virtual int get_column() const;

				/**
				 * Returns the measure in which this symbols begins.
				 * @return
				 */
				virtual unsigned int get_measure() const;

				/**
				 * Returns the beat in which this symbol begins.
				 *
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
				 * Returns the pre sign if assigned. Returns null otherwise.
				 *
				 * @return
				 */
				std::shared_ptr<ps::i_pre_sign> get_pre_sign() const;

				/**
				 * Returns true if a hold sign is attached.
				 *
				 * @return
				 */
				bool get_hold() const;

				/**
				 * Returns the movement symbol.
				 *
				 * @return
				 */
				std::shared_ptr<mv::i_symbol> get_symbol() const;

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
				 * Returns true if the symbols and all subelements have the same type making them comparable by feature vectors.
				 *
				 * @param a The movement to be compared to.
				 * @return True if types equal.
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

				friend std::ostream& operator<<(std::ostream& os, const movement& obj)
				{
					os << obj.str();
					return os;
				}

				friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<movement>& obj)
				{
					os << obj->str();
					return os;
				}


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

#endif // MAE_FL_LABAN_MOVEMENT_HPP_
