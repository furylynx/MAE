#ifndef MAE_FL_LABAN_PS_CUSTOM_LIMB_HPP_
#define MAE_FL_LABAN_PS_CUSTOM_LIMB_HPP_

//custom includes
#include "i_limb.hpp"
#include "i_endpoint.hpp"

//global includes
#include <string>
#include <sstream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <cmath>

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{

				class custom_limb: public i_limb
				{
					public:
						/**
						 * Creates a custom limb pre-sign which is defined as the limb between two endpoints.
						 *
						 * @param fixed_end The fixed end of the limb.
						 * @param extremity (optional) The extremity end of the limb.
						 */
						custom_limb(std::shared_ptr<i_endpoint> extremity, std::shared_ptr<i_endpoint> fixed_end = nullptr);
						virtual ~custom_limb();

						/**
						 * Returns the fixed end of the limb.
						 *
						 * @return
						 */
						std::shared_ptr<i_endpoint> get_fixed_end() const;

						/**
						 * Returns the extremity end of the limb if set. Returns null otherwise.
						 *
						 * @return
						 */
						std::shared_ptr<i_endpoint> get_extremity() const;

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
						std::shared_ptr<i_endpoint> fixed_end_;
						std::shared_ptr<i_endpoint> extremity_;
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_PS_CUSTOM_LIMB_HPP_
