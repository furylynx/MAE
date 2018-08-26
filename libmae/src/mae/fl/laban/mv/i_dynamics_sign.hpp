#ifndef MAE_FL_LABAN_MV_I_DYNAMICS_SIGN_HPP_
#define MAE_FL_LABAN_MV_I_DYNAMICS_SIGN_HPP_

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
			namespace mv
			{

				class i_dynamics_sign
				{
					public:
						virtual ~i_dynamics_sign(){}

						/**
						 * Returns true if signs are equal.
						 *
						 * @param a The sign to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<i_dynamics_sign> a) const = 0;

						/**
						 * Returns true if the symbols and all subelements have the same type making them comparable by feature vectors.
						 *
						 * @param a The sign to be compared to.
						 * @return True if types equal.
						 */
						virtual bool all_types_equal(std::shared_ptr<i_dynamics_sign> a) const = 0;

						/**
						 * Returns the feature vector for the symbol.
						 *
						 * @param hierarchy_factor The factor for subelements.
						 * @return The feature vector.
						 */
						virtual std::vector<double> feature_vector(double hierarchy_factor = 0.5) const = 0;

						/**
						 * Returns the xml string representation for the sign.
						 *
						 * @param indent The applied indent.
						 * @param namesp The namespace if any.
						 * @return The xml string.
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
				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_MV_I_DYNAMICS_SIGN_HPP_
