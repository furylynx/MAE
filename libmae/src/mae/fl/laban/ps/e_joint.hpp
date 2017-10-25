#ifndef MAE_FL_LABAN_PS_E_JOINT_H_
#define MAE_FL_LABAN_PS_E_JOINT_H_

//custom includes
#include "../../../mstr.hpp"

//global includes
#include <string>
#include <stdexcept>
#include <vector>

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{

				enum class e_joint : int
				{
						NONE_JOINT,
						SHOULDER,
						ELBOW,
						WRIST,
						HAND,
						FINGERS,
						HIP,
						KNEE,
						ANKLE,
						FOOT,
						TOES
				};

				class e_joint_c
				{
					public:
						/**
						 * Returns the string representation for this enum value.
						 *
						 * @param joint The element.
						 * @return The string representation.
						 */
						static std::string str(e_joint joint);

						/**
						 * Returns a vector containing all possible enum values.
						 *
						 * @return A vector.
						 */
						static std::vector<e_joint> vec();

						/**
						 * Returns the integer value corresponding to this element.
						 *
						 * @param ejoint The element.
						 * @return The integer ID.
						 */
						static int to_int(e_joint ejoint);

						/**
						 * Parses the string and returns the corresponding element.
						 *
						 * @param str The string to be parsed.
						 * @return The element.
						 */
						static e_joint parse(std::string str);
				};


			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_PS_E_JOINT_H_
