#ifndef MAE_FL_LABAN_PS_DEFAULT_LIMB_HPP_
#define MAE_FL_LABAN_PS_DEFAULT_LIMB_HPP_

//custom includes
#include "i_limb.hpp"
#include "e_limb.hpp"

//global includes
#include <string>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <vector>


namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{

				class default_limb: public i_limb
				{
					public:
						/**
						 * Creates a default limb pre-sign which uses one of the defined limbs.
						 *
						 * @param limb The limb type.
						 */
						default_limb(e_limb limb);
						virtual ~default_limb();

						/**
						 * Returns the limb type.
						 *
						 * @return
						 */
						e_limb get_limb() const;

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
						 * Returns true if elements are equal.
						 *
						 * @param a The element to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<i_part> a) const;

						/**
						 * Returns true if elements are equal.
						 *
						 * @param a The element to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<i_limb> a) const;

						/**
						 * Returns true if the part and all subelements have the same type making them comparable by feature vectors.
						 *
						 * @param a The part to be compared to.
						 * @return True if types equal.
						 */
						virtual bool all_types_equal(std::shared_ptr<i_part> a) const;

						/**
						 * Returns true if the part and all subelements have the same type making them comparable by feature vectors.
						 *
						 * @param a The part to be compared to.
						 * @return True if types equal.
						 */
						virtual bool all_types_equal(std::shared_ptr<i_limb> a) const;

						/**
						 * Returns the feature vector for the symbol.
						 *
						 * @param hierarchy_factor The factor for subelements.
						 * @return The feature vector.
						 */
						virtual std::vector<double> feature_vector(double hierarchy_factor = 0.5) const;

					private:
						e_limb limb_;
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_PS_
