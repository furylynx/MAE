#ifndef MAE_FL_LABAN_MV_SPACE_SYMBOL_HPP_
#define MAE_FL_LABAN_MV_SPACE_SYMBOL_HPP_

//custom includes
#include "i_symbol.hpp"
#include "space_measurement.hpp"
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

				class space_symbol: public i_symbol
				{
					public:
						/**
						 * Creates a new space symbol. It is not to be confused with the space measurement sign
						 * which is a member of this symbol.
						 *
						 * @param space_measurement The space measurement sign.
						 * @param dynamics (optional) The dynamics sign.
						 */
						space_symbol(std::shared_ptr<space_measurement> space_measurement, std::shared_ptr<i_dynamics_sign> dynamics = nullptr);
						virtual ~space_symbol();

						/**
						 * Returns the dynamics sign if any. Returns null otherwise.
						 *
						 * @return A shared pointer to the dynamics sign.
						 */
						std::shared_ptr<i_dynamics_sign> get_dynamics() const;

						/**
						 * Returns the space measurement sign.
						 *
						 * @return The space measurement.
						 */
						std::shared_ptr<space_measurement> get_space_measurement() const;

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
						 * Returns the SVG representation for this symbol.
						 *
						 * @param identifier The identifier of the svg object.
						 * @param rect The rect to fill.
						 * @param left True if left side.
						 * @param style The svg style.
						 * @return The SVG.
						 */
						virtual std::string svg(std::string identifier, draw_rect rect, bool left = false, svg_style style = svg_style()) const;

						/**
						 * Returns the string representation for this element.
						 *
						 * @return The string.
						 */
						virtual std::string str() const;

						friend std::ostream& operator<<(std::ostream& os, const space_symbol& obj)
						{
							os << obj.str();
							return os;
						}

						friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<space_symbol>& obj)
						{
							os << obj->str();
							return os;
						}


					private:
						std::shared_ptr<i_dynamics_sign> dynamics_;
						std::shared_ptr<space_measurement> space_measurement_;

				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_MV_SPACE_SYMBOL_HPP_
