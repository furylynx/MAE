#ifndef MAE_FL_LABAN_MV_DIRECTION_SYMBOL_HPP_
#define MAE_FL_LABAN_MV_DIRECTION_SYMBOL_HPP_

//custom includes
#include "i_symbol.hpp"
#include "e_level.hpp"
#include "e_direction.hpp"
#include "e_contact_hook.hpp"
#include "i_dynamics_sign.hpp"
#include "space_measurement.hpp"
#include "pin.hpp"

#include "../../fl_direction_map.hpp"

//global includes
#include <string>
#include <sstream>
#include <stdexcept>
#include <memory>


namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				class direction_symbol: public i_symbol
				{
					public:
						/**
						 * Creates a direction symbol. This element corresponds to a direction symbol of a Labanotation
						 * score. It has a vertical direction (high, mid or low) and a horizontal direction.
						 *
						 * If the 45-degree resolution offered through the combination of the vertical and horizontal
						 * element is not enough to notate a movement adequately, a relationship-pin can be defined in
						 * the mod-pin element to modify the direction by 1/3 into the direction of the pin. By using
						 * the space elements it is possible to add a space measurement sign to this direction symbol.
						 *
						 * The contactHook element can be used to add a contact hook to this symbol if it is placed in a
						 * support column.
						 *
						 * @param vertical The level of this symbol.
						 * @param horizontal The (horizontal) direction of this symbol.
						 * @param modification_pin (optional) A modification pin.
						 * @param relationship_pin (optional) A relationship pin.
						 * @param dynamics (optional) A dynamics sign.
						 * @param space_measurement (optional) A space measurement sign.
						 * @param contact_hook (optional) The contact hook.
						 */
						direction_symbol(e_level vertical, e_direction horizontal, std::shared_ptr<pin> modification_pin = nullptr, std::shared_ptr<pin> relationship_pin = nullptr, std::shared_ptr<i_dynamics_sign> dynamics = nullptr, std::shared_ptr<space_measurement> space_measurement = nullptr, e_contact_hook contact_hook = e_contact_hook::NONE_CONTACT_HOOK);
						virtual ~direction_symbol();

						/**
						 * Returns the level of this symbol.
						 *
						 * @return The level.
						 */
						e_level get_vertical() const;

						/**
						 * Returns the (horizontal) direction of this symbol.
						 *
						 * @return The direction.
						 */
						e_direction get_horizontal() const;

						/**
						 * Returns the applied modification pin if any. Returns null otherwise.
						 *
						 * @return A shared pointer to the pin.
						 */
						std::shared_ptr<pin> get_modification_pin() const;

						/**
						 * Returns the relationship pin if any. Returns null otherwise.
						 *
						 * @return A shared pointer to the pin.
						 */
						std::shared_ptr<pin> get_relationship_pin() const;

						/**
						 * Returns the dynamics sign if any. Returns null otherwise.
						 *
						 * @return A shared pointer to the dynamics sign.
						 */
						std::shared_ptr<i_dynamics_sign> get_dynamics() const;

						/**
						 * Returns the space measurement sign if any. Returns null otherwise.
						 *
						 * @return A shared pointer to the space measurement.
						 */
						std::shared_ptr<space_measurement> get_space_measurement() const;

						/**
						 * Returns the contact hook. Contact hook is set to NONE if unused.
						 *
						 * @return The contact hook.
						 */
						e_contact_hook get_contact_hook() const;

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
						 * Returns the SVG representation for the contact hook symbol.
						 *
						 * @param identifier The identifier of the svg object.
						 * @param rect The rect to fill.
						 * @param left True if left side.
						 * @param style The svg style.
						 * @return The SVG.
						 */
						virtual std::string contact_hook_svg(std::string identifier, draw_rect rect, bool left = false, svg_style style = svg_style()) const;

						/**
						 * Returns the string representation for this element.
						 *
						 * @return The string.
						 */
						virtual std::string str() const;

						friend std::ostream& operator<<(std::ostream& os, const direction_symbol& obj)
						{
							os << obj.str();
							return os;
						}

						friend std::ostream& operator<<(std::ostream& os, const std::shared_ptr<direction_symbol>& obj)
						{
							os << obj->str();
							return os;
						}

					private:
						e_level vertical_;
						e_direction horizontal_;
						std::shared_ptr<pin> modification_pin_;
						std::shared_ptr<pin> relationship_pin_;
						std::shared_ptr<i_dynamics_sign> dynamics_;
						std::shared_ptr<space_measurement> space_measurement_;
						e_contact_hook contact_hook_;


				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_MV_DIRECTION_SYMBOL_HPP_
