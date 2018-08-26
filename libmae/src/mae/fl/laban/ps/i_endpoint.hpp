#ifndef MAE_FL_LABAN_PS_I_ENDPOINT_HPP_
#define MAE_FL_LABAN_PS_I_ENDPOINT_HPP_

//custom includes
#include "i_part.hpp"
#include "../draw_rect.hpp"


//global includes
#include <string>
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

				class i_endpoint: public i_part
				{
					public:
						virtual ~i_endpoint(){}

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
						 * Returns the predecessor of the current endpoint (which is the default fixed endpoint). If the endpoint is the beginning of the extremity null is returned.
						 *
						 * @return The successor element.
						 */
						virtual std::shared_ptr<i_endpoint> get_fixed_end() const = 0;

						/**
						 * Returns true if elements are equal.
						 *
						 * @param a The element to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<i_part> a) const = 0;

						/**
						 * Returns true if elements are equal.
						 *
						 * @param a The element to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<i_endpoint> a) const  = 0;

						/**
						 * Returns true if the part and all subelements have the same type making them comparable by feature vectors.
						 *
						 * @param a The part to be compared to.
						 * @return True if types equal.
						 */
						virtual bool all_types_equal(std::shared_ptr<i_part> a) const = 0;

						/**
						 * Returns true if the part and all subelements have the same type making them comparable by feature vectors.
						 *
						 * @param a The part to be compared to.
						 * @return True if types equal.
						 */
						virtual bool all_types_equal(std::shared_ptr<i_endpoint> a) const = 0;

						/**
						 * Returns the feature vector for the part.
						 *
						 * @param hierarchy_factor The factor for subelements.
						 * @return The feature vector.
						 */
						virtual std::vector<double> feature_vector(double hierarchy_factor = 0.5) const = 0;

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

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_PS_I_ENDPOINT_HPP_
