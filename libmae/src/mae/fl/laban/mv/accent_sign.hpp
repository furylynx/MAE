#ifndef MAE_FL_LABAN_MV_ACCENT_SIGN_HPP_
#define MAE_FL_LABAN_MV_ACCENT_SIGN_HPP_

//custom includes
#include "i_dynamics_sign.hpp"

//global includes
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>



namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				class accent_sign: public i_dynamics_sign
				{
					public:
						/**
						 * Creates an accent sign. The accent must be a value between 1 and 5.
						 *
						 * @param accent The accent which must be an integer value between 1 and 5.
						 */
						accent_sign(unsigned int accent);
						virtual ~accent_sign();

						/**
						 * Returns the accent.
						 * @return
						 */
						unsigned int get_accent() const;

						/**
						 * Returns true if signs are equal.
						 *
						 * @param a The sign to be compared to.
						 * @return True if equal.
						 */
						virtual bool equals(std::shared_ptr<i_dynamics_sign> a) const;

						/**
						 * Returns the feature vector for the symbol.
						 *
						 * @return The feature vector.
						 */
						virtual std::vector<double> feature_vector() const;

						/**
						 * Returns the XML representation for this element.
						 *
						 * @param indent The applied indent.
						 * @param namesp The prefixed XML namespace.
						 *
						 * @return The XML string.
						 */
						virtual std::string xml(unsigned int indent = 0, std::string namesp = "") const;

					private:
						unsigned int accent_;
				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_MV_ACCENT_SIGN_HPP_
