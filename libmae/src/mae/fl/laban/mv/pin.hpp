#ifndef MAE_FL_LABAN_MV_PIN_HPP_
#define MAE_FL_LABAN_MV_PIN_HPP_

//custom includes
#include "i_degree_sign.hpp"
#include "e_level.hpp"

//global includes
#include <string>
#include <sstream>
#include <stdexcept>
#include <cmath>

//defines
#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				class pin: public i_degree_sign
				{
					public:
						/**
						 * Creates a pin. The horizontal direction must be a value between -1 and 360.
						 *
						 * @param level The level type.
						 * @param horizontal The horizontal direction which must be a value between -1
						 * 						and 360. -1 represents at place whereas a value between
						 * 						0 and 360 represents the degree relative to the
						 * 						forward direction (e.g. 90 represents "right").
						 */
						pin(e_level level, int horizontal);
						virtual ~pin();

						/**
						 * Returns the level.
						 *
						 * @return The level.
						 */
						e_level get_level() const;

						/**
						 * Returns the (horizontal) direction which is a value between -1 and 360.
						 * -1 represents at place whereas a value between 0 and 360 represents a
						 * the degree relative to the forward direction (e.g. 90 represents
						 * "right").
						 *
						 * @return The direction.
						 */
						int get_horizontal() const;

						/**
						 * Returns true if signs are equal.
						 *
						 * @param a The sign to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<i_degree_sign> a) const;

						/**
						 * Returns true if the signs and all subelements have the same type making them comparable by feature vectors.
						 *
						 * @param a The signs to be compared to.
						 * @return True if types equal.
						 */
						virtual bool all_types_equal(std::shared_ptr<i_degree_sign> a) const;

						/**
						 * Returns the feature vector for the symbol.
						 *
						 * @param hierarchy_factor The factor for subelements.
						 * @return The feature vector.
						 */
						virtual std::vector<double> feature_vector(double hierarchy_factor = 0.5) const;

						/**
						 * Returns the path of the type hierarchy beginning with the i_degree_sign type. The path can be used to compare elements by their position in the hierarchy. Uses the shortest path if multiple paths are possible (diamond hierarchy).
						 *
						 * @return The path from the current type to the i_degree_sign type.
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
						virtual std::string xml(unsigned int indent = 0, std::string namesp = "", bool print_type = false) const;

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

					private:
						e_level level_;
						int horizontal_;
				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_MV_PIN_HPP_
