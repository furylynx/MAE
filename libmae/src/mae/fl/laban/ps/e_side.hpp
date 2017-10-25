#ifndef MAE_FL_LABAN_PS_E_SIDE_HPP_
#define MAE_FL_LABAN_PS_E_SIDE_HPP_

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

				enum class e_side : int
				{
						NONE_SIDE,
						LEFT,
						RIGHT
				};

				class e_side_c
				{
					public:
						/**
						 * Returns the string representation for this enum value.
						 *
						 * @param side The element.
						 * @return The string representation.
						 */
						static std::string str(e_side side);

						/**
						 * Returns a vector containing all possible enum values.
						 *
						 * @return A vector.
						 */
						static std::vector<e_side> vec();

						/**
						 * Returns the integer value corresponding to this element.
						 *
						 * @param eside The element.
						 * @return The integer ID.
						 */
						static int to_int(e_side eside);

						/**
						 * Parses the string and returns the corresponding element.
						 *
						 * @param str The string to be parsed.
						 * @return The element.
						 */
						static e_side parse(std::string vec);
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_PS_E_SIDE_HPP_
