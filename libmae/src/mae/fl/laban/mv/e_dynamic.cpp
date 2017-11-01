#include "e_dynamic.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{
				std::string e_dynamic_c::str(e_dynamic dynamic)
				{
					switch (dynamic)
					{
					case e_dynamic::NONE_DYNAMIC 					: return "none";
					case e_dynamic::STRONG           		: return "strong";
					case e_dynamic::GENTLE           		: return "gentle";
					case e_dynamic::EMPHASIZED       		: return "emphasized";
					case e_dynamic::RELAXED          		: return "relaxed";
					case e_dynamic::LIMP            		: return "limp";
                    case e_dynamic::UNEMPHASIZED           	: return "unemphasized";
                    case e_dynamic::RESILIENT              	: return "resilient";
                    case e_dynamic::VERY_RESILIENT          : return "veryResilient";
					}

					throw std::invalid_argument("Enum value not listed in the str() method");

				}

				std::vector<e_dynamic> e_dynamic_c::vec()
				{
					std::vector<e_dynamic> result;
					result.push_back(e_dynamic::NONE_DYNAMIC 			);
					result.push_back(e_dynamic::STRONG         );
					result.push_back(e_dynamic::GENTLE         );
					result.push_back(e_dynamic::EMPHASIZED     );
					result.push_back(e_dynamic::RELAXED        );
					result.push_back(e_dynamic::LIMP           );
					result.push_back(e_dynamic::UNEMPHASIZED   );
					result.push_back(e_dynamic::RESILIENT      );
					result.push_back(e_dynamic::VERY_RESILIENT );

					return result;
				}

				int e_dynamic_c::to_int(e_dynamic edynamic)
				{
					return (int) edynamic;
				}

				int e_dynamic_c::max()
				{
					return (int) e_dynamic::VERY_RESILIENT;
				}

				e_dynamic e_dynamic_c::parse(std::string str)
				{
					std::string str_l = mstr::to_lower(str);

					std::vector<e_dynamic> v = e_dynamic_c::vec();

					for (unsigned int i = 0; i < v.size(); i++)
					{
						std::string t = e_dynamic_c::str(v.at(i));
						if (str_l == mstr::to_lower(t))
						{
							return v.at(i);
						}
					}

					throw std::invalid_argument("Could not parse the given value since no match was found.");
				}


			} // namespace mv
		} // namespace laban
	} // namespace fl
} // namespace mae
