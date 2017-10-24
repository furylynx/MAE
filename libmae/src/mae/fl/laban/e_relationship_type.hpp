#ifndef MAE_FL_LABAN_E_RELATIONSHIP_TYPE_HPP_
#define MAE_FL_LABAN_E_RELATIONSHIP_TYPE_HPP_

//custom includes
#include "../../mstr.hpp"

//global includes
#include <vector>
#include <string>
#include <stdexcept>

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			enum class e_relationship_type : int
			{
					NONE_RELATIONSHIP_TYPE,
					ADDRESS,
					NEAR_RELATIONSHIP_TYPE,
					TOUCH,
					SUPPORT
			};

			class e_relationship_type_c
			{
				public:
					/**
					 * Returns the string representation for this enum value.
					 *
					 * @param type The element.
					 * @return The string representation.
					 */
					static std::string str(e_relationship_type type);

					/**
					 * Returns a vector containing all possible enum values.
					 *
					 * @return A vector.
					 */
					static std::vector<e_relationship_type> vec();

					/**
					 * Returns the integer value corresponding to this element.
					 *
					 * @param erelationshiptype The element.
					 * @return The integer ID.
					 */
					static int to_int(e_relationship_type erelationshiptype);

					/**
					 * Parses the string and returns the corresponding element.
					 *
					 * @param str The string to be parsed.
					 * @return The element.
					 */
					static e_relationship_type parse(std::string str);
			};
		} // namespace laban
	} // namespace fl
} // namespace mae

#endif // MAE_FL_LABAN_E_RELATIONSHIP_TYPE_HPP_
