#ifndef MAE_FL_LABAN_PS_I_PRE_SIGN_HPP_
#define MAE_FL_LABAN_PS_I_PRE_SIGN_HPP_

//custom includes
//...

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

				class i_pre_sign
				{
					public:
						virtual ~i_pre_sign(){}

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
						 * Returns the SVG representation for this symbol.
						 *
						 * @param posx The x position.
						 * @param posy The y position.
						 * @param width The width.
						 * @param height The height.
						 * @return The SVG.
						 */
						virtual std::string svg(std::string identifier, double posx, double posy, double width, double height, bool left = false) const = 0;

						/**
						 * Returns true if elements are equal.
						 *
						 * @param a The element to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<i_pre_sign> a) const = 0;

						/**
						 * Returns true if the pre-sign and all subelements have the same type making them comparable by feature vectors.
						 *
						 * @param a The pre-sign to be compared to.
						 * @return True if types equal.
						 */
						virtual bool all_types_equal(std::shared_ptr<i_pre_sign> a) const = 0;

						/**
						 * Returns the feature vector for the pre sign.
						 *
						 * @return The feature vector.
						 */
						virtual std::vector<double> feature_vector() const = 0;
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_PS_I_PRE_SIGN_HPP_
