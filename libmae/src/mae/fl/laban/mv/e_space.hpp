#ifndef MAE_FL_LABAN_MV_E_SPACE_HPP_
#define MAE_FL_LABAN_MV_E_SPACE_HPP_

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

				enum class e_space : int
				{
						NONE_SPACE,
						NARROW,
						WIDE,
						FOLDING,
						UNFOLDING,
						JOINING,
						SPREADING
				};

				class e_space_c
				{
					public:
						/**
						 * Returns the string representation for this enum value.
						 *
						 * @param space The element.
						 * @return The string representation.
						 */
						static std::string str(e_space space);

						/**
						 * Returns a vector containing all possible enum values.
						 *
						 * @return A vector.
						 */
						static std::vector<e_space> vec();

						/**
						 * Parses the string and returns the corresponding element.
						 *
						 * @param str The string to be parsed.
						 * @return The element.
						 */
						static e_space parse(std::string str);
				};


			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_MV_E_SPACE_HPP_
