#ifndef MAE_FL_LABAN_MV_I_DEGREE_SIGN_HPP_
#define MAE_FL_LABAN_MV_I_DEGREE_SIGN_HPP_

//custom includes
#include "../draw_rect.hpp"
#include "../svg_style.hpp"

//global includes
#include <string>
#include <memory>
#include <vector>
#include <typeindex>

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				class i_degree_sign
				{
					public:
						virtual ~i_degree_sign(){}

						/**
						 * Returns true if the signs are equal.
						 *
						 * @param a The sign to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<i_degree_sign> a) const = 0;

						/**
						 * Returns true if the symbols and all subelements have the same type making them comparable by feature vectors.
						 *
						 * @param a The sign to be compared to.
						 * @return True if types equal.
						 */
						virtual bool all_types_equal(std::shared_ptr<i_degree_sign> a) const = 0;

						/**
						 * Returns the feature vector for the symbol.
						 *
						 * @param hierarchy_factor The factor for subelements.
						 * @return The feature vector.
						 */
						virtual std::vector<double> feature_vector(double hierarchy_factor = 0.5) const = 0;

						/**
						 * Returns the path of the type hierarchy beginning with the i_degree_sign type. The path can be used to compare elements by their position in the hierarchy. Uses the shortest path if multiple paths are possible (diamond hierarchy).
						 *
						 * @return The path from the current type to the i_degree_sign type.
						 */
						virtual std::vector<std::type_index> get_type_path() const = 0;

						/**
						 * Returns the XML representation for this sign.
						 *
						 * @param indent The indent to be applied.
						 * @param namesp The namespace to be applied.
						 * @return The XML string.
						 */
						virtual std::string xml(unsigned int indent = 0, std::string namesp = "", bool print_type = false) const = 0;

						/**
						 * Returns the SVG representation for this symbol.
						 *
						 * @param identifier The identifier of the svg object.
						 * @param posx The x position.
						 * @param posy The y position.
						 * @param width The width.
						 * @param height The height.
						 * @param left True if left side.
						 * @return The SVG.
						 */
						virtual std::string svg(std::string identifier, double posx, double posy, double width, double height, bool left = false) const = 0;

                        /**
                         * Returns the SVG representation for this symbol.
                         *
                         * @param identifier The identifier of the svg object.
                         * @param rect The rect to fill.
                         * @param left True if left side.
                         * @param style The svg style.
                         * @return The SVG.
                         */
                        virtual std::string svg(std::string identifier, draw_rect rect, bool left = false, svg_style style = svg_style()) const = 0;

				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_MV_I_DEGREE_SIGN_HPP_
