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
						e_dynamic dynamic_;
				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_MV_DYNAMICS_SIGN_HPP_
