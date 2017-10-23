#ifndef MAE_FL_LABAN_MV_E_TURN_DIRECTION_HPP_
#define MAE_FL_LABAN_MV_E_TURN_DIRECTION_HPP_

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

				enum class e_turn_direction : int
				{
						NONE_TURN_DIRECTION,
						COUNTER_CLOCKWISE,
						CLOCKWISE,
						ANY
				};

				class e_turn_direction_c
				{
					public:
						/**
						 * Returns the string representation for this enum value.
						 *
						 * @param turn The element.
						 * @return The string representation.
						 */
						static std::string str(e_turn_direction turn);

						/**
						 * Returns the integer value corresponding to this element.
						 *
						 * @param eturndirection The element.
						 * @return The integer ID.
						 */
						static int to_int(e_turn_direction eturndirection);

						/**
						 * Returns a vector containing all possible enum values.
						 *
						 * @return A vector.
						 */
						static std::vector<e_turn_direction> vec();

						/**
						 * Parses the string and returns the corresponding element.
						 *
						 * @param str The string to be parsed.
						 * @return The element.
						 */
						static e_turn_direction parse(std::string str);
				};


			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_MV_E_TURN_DIRECTION_HPP_
