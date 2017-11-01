#ifndef MAE_FL_LABAN_MV_E_CANCEL_HPP_
#define MAE_FL_LABAN_MV_E_CANCEL_HPP_

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
			namespace mv
			{

				enum class e_cancel : int
				{
						NONE_CANCEL,
						BACK_NORMAL,
						RELEASE_CONTACT
				};

				class e_cancel_c
				{
					public:
						/**
						 * Returns the string representation for this enum value.
						 *
						 * @param cancel The element.
						 * @return The string representation.
						 */
						static std::string str(e_cancel cancel);

						/**
						 * Returns the integer value corresponding to this element.
						 *
						 * @param ecancel The element.
						 * @return The integer ID.
						 */
						static int to_int(e_cancel ecancel);

						/**
						 * Returns the int value corresponding to the last element making it the maximum int.
						 *
						 * @return The maximum.
						 */
						static int max();

						/**
						 * Returns a vector containing all possible enum values.
						 *
						 * @return A vector.
						 */
						static std::vector<e_cancel> vec();

						/**
						 * Parses the string and returns the corresponding element.
						 *
						 * @param str The string to be parsed.
						 * @return The element.
						 */
						static e_cancel parse(std::string str);

				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_MV_E_CANCEL_HPP_
