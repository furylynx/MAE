#ifndef MAE_FL_LABAN_MV_I_DYNAMICS_SIGN_HPP_
#define MAE_FL_LABAN_MV_I_DYNAMICS_SIGN_HPP_

//custom includes
//...

//global includes
#include <string>
#include <memory>

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
						 * Returns the xml string representation for the sign.
						 *
						 * @param indent The applied indent.
						 * @param namesp The namespace if any.
						 * @return The xml string.
						 */
						virtual std::string xml(unsigned int indent = 0, std::string namesp = "") const = 0;
				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_MV_I_DYNAMICS_SIGN_HPP_
