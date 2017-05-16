#ifndef MAE_FL_LABAN_MV_E_LEVEL_HPP_
#define MAE_FL_LABAN_MV_E_LEVEL_HPP_

//custom includes
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

				enum class e_level : int
				{
						NONE_LEVEL,
						HIGH,
						MIDDLE,
						LOW
				};

				class e_level_c
				{
					public:
						/**
						 * Returns the string representation for this enum value.
						 *
						 * @param level The element.
						 * @return The string representation.
						 */
						static std::string str(e_level level);

						/**
						 * Returns the corresponding level element.
						 *
						 * @param direction The direction+level enum value.
						 * @return The level.
						 */
						static e_level lvl(e_fl_direction direction);

						/**
						 * Returns a vector containing all possible enum values.
						 *
						 * @return A vector.
						 */
						static std::vector<e_level> vec();

						/**
						 * Parses the string and returns the corresponding element.
						 *
						 * @param str The string to be parsed.
						 * @return The element.
						 */
						static e_level parse(std::string str);
				};

			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_MV_E_LEVEL_HPP_
