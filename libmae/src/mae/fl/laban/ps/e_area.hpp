#ifndef MAE_FL_LABAN_PS_E_AREA_HPP_
#define MAE_FL_LABAN_PS_E_AREA_HPP_

//custom includes
#include "../../../mstr.hpp"

//global includes
#include <string>
#include <vector>
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

				enum class e_area : int
				{
						NONE_AREA,
						HEAD,
						CHEST,
						WAIST,
						PELVIS,
						TORSO
				};

				class e_area_c
				{
					public:
						/**
						 * Returns the string representation for this enum value.
						 *
						 * @param area The element.
						 * @return The string representation.
						 */
						static std::string str(e_area area);

						/**
						 * Returns a vector containing all possible enum values.
						 *
						 * @return A vector.
						 */
						static std::vector<e_area> vec();

						/**
						 * Returns the integer value corresponding to this element.
						 *
						 * @param earea The element.
						 * @return The integer ID.
						 */
						static int to_int(e_area earea);

						/**
						 * Returns the int value corresponding to the last element making it the maximum int.
						 *
						 * @return The maximum.
						 */
						static int max();

						/**
						 * Parses the string and returns the corresponding element.
						 *
						 * @param str The string to be parsed.
						 * @return The element.
						 */
						static e_area parse(std::string str);
				};

			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_PS_E_AREA_HPP_
