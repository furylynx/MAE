#ifndef MAE_FL_LABAN_MV_E_DIRECTION_H_
#define MAE_FL_LABAN_MV_E_DIRECTION_H_

//custom includes
//#include "../../e_fl_direction.hpp"
#include "../../../mstr.hpp"
#include "../../e_fl_direction.hpp"

//global includes
#include <string>
#include <stdexcept>
#include <vector>

namespace mae
{
	namespace fl
	{
		enum class e_fl_direction;

		namespace laban
		{
			namespace mv
			{

				enum class e_direction : int
				{
						NONE_DIRECTION,
						PLACE,
						FORWARD,
						BACKWARD,
						LEFT,
						RIGHT,
						LEFT_FORWARD,
						LEFT_BACKWARD,
						RIGHT_FORWARD,
						RIGHT_BACKWARD
				};

				class e_direction_c
				{
					public:
						/**
						 * Returns the string representation for this enum value.
						 *
						 * @param direction The element.
						 * @return The string representation.
						 */
						static std::string str(e_direction direction);

						/**
						 * Returns the corresponding direction value.
						 *
						 * @param direction The direction+level enum value.
						 * @return The direction.
						 */
						static e_direction dir(e_fl_direction direction);

						/**
						 * Returns a vector containing all possible enum values.
						 *
						 * @return A vector.
						 */
						static std::vector<e_direction> vec();

						/**
						 * Parses the string and returns the corresponding element.
						 *
						 * @param str The string to be parsed.
						 * @return The element.
						 */
						static e_direction parse(std::string str);

				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_MV_E_DIRECTION_H_
