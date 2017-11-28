#ifndef MAE_FL_LABAN_MV_VIBRATION_SYMBOL_HPP_
#define MAE_FL_LABAN_MV_VIBRATION_SYMBOL_HPP_

//custom includes
#include "i_symbol.hpp"
#include "pin.hpp"
#include "i_dynamics_sign.hpp"

//global includes
#include <string>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <cmath>


namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				class vibration_symbol: public i_symbol
				{
					public:
						/**
						 * Creates a vibration symbol. A vibration symbol represents an alternation
						 * between two directions which is represented by two pins.
						 *
						 * @param displacement1 The first pin.
						 * @param displacement2 The second pin.
						 * @param dynamics (optional) A dynamics sign.
						 */
						vibration_symbol(std::shared_ptr<pin> displacement1, std::shared_ptr<pin> displacement2, std::shared_ptr<i_dynamics_sign> dynamics = nullptr);
						virtual ~vibration_symbol();

						/**
						 * Returns the dynamics sign if any. Returns null otherwise.
						 *
						 * @return
						 */
						std::shared_ptr<i_dynamics_sign> get_dynamics() const;

						/**
						 * The first of the two alternating directions.
						 *
						 * @return The pin.
						 */
						std::shared_ptr<pin> get_displacement1() const;

						/**
						 * The second of the two alternating directions.
						 *
						 * @return The pin.
						 */
						std::shared_ptr<pin> get_displacement2() const;

						/**
						 * Returns true if signs are equal.
						 *
						 * @param a The sign to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<i_symbol> a) const;

						/**
						 * Returns true if the symbols and all subelements have the same type making them comparable by feature vectors.
						 *
						 * @param a The symbol to be compared to.
						 * @return True if types equal.
						 */
						virtual bool all_types_equal(std::shared_ptr<i_symbol> a) const;

						/**
						 * Returns the feature vector for the symbol.
						 *
						 * @param hierarchy_factor The factor for subelements.
						 * @return The feature vector.
						 */
						virtual std::vector<double> feature_vector(double hierarchy_factor = 0.5) const;

						/**
						 * Returns the path of the type hierarchy beginning with the i_symbol type. The path can be used to compare elements by their position in the hierarchy. Uses the shortest path if multiple paths are possible (diamond hierarchy).
						 *
						 * @return The path from the current type to the i_symbol type.
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
						 * Returns the SVG representation for this symbol.
						 *
						 * @param posx The x position.
						 * @param posy The y position.
						 * @param width The width.
						 * @param height The height.
						 * @return The SVG.
						 */
						virtual std::string svg(std::string identifier, double posx, double posy, double width, double height, bool left = false) const;

						/**
						 * Returns the string representation for this element.
						 *
						 * @return The string.
						 */
						virtual std::string str() const;

						friend std::ostream& operator<<(std::ostream& os, const vibration_symbol& obj)
						{
							os << obj.str();
							return os;
						}

						friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<vibration_symbol>& obj)
						{
							os << obj->str();
							return os;
						}

					private:
						std::shared_ptr<i_dynamics_sign> dynamics_;
						std::shared_ptr<pin> displacement1_;
						std::shared_ptr<pin> displacement2_;

				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_MV_VIBRATION_SYMBOL_HPP_
