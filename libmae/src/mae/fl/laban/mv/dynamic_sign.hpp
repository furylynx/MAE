#ifndef MAE_FL_LABAN_MV_DYNAMIC_SIGN_HPP_
#define MAE_FL_LABAN_MV_DYNAMIC_SIGN_HPP_

//custom includes
#include "i_dynamics_sign.hpp"
#include "e_dynamic.hpp"

//global includes
#include <string>
#include <sstream>
#include <stdexcept>

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				class dynamic_sign: public i_dynamics_sign
				{
					public:
						/**
						 * Creates a new dynamics sign.
						 *
						 * @param dynamic The dynamic type.
						 */
						dynamic_sign(e_dynamic dynamic);
						virtual ~dynamic_sign();

						/**
						 * Returns the dynamic type.
						 *
						 * @return The type.
						 */
						e_dynamic get_dynamic() const;

						/**
						 * Returns true if signs are equal.
						 *
						 * @param a The sign to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<i_dynamics_sign> a) const;

						/**
						 * Returns true if the signs and all subelements have the same type making them comparable by feature vectors.
						 *
						 * @param a The signs to be compared to.
						 * @return True if types equal.
						 */
						virtual bool all_types_equal(std::shared_ptr<i_dynamics_sign> a) const;

						/**
						 * Returns the feature vector for the symbol.
						 *
						 * @param hierarchy_factor The factor for subelements.
						 * @return The feature vector.
						 */
						virtual std::vector<double> feature_vector(double hierarchy_factor = 0.5) const;

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

					private:
						e_dynamic dynamic_;
				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_MV_DYNAMICS_SIGN_HPP_
