#include "e_path_type.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			std::string e_path_type_c::str(e_path_type type)
			{
				switch (type)
				{
				case e_path_type::NONE_PATH_TYPE           		: return "none";
				case e_path_type::STRAIGHT     			: return "straight";
				case e_path_type::CIRCULAR_LEFT 		: return "circularLeft";
                case e_path_type::CIRCULAR_RIGHT        : return "circularRight";
                case e_path_type::ANY                   : return "any";
				}

				throw std::invalid_argument("Enum value not listed in the str() method");
			}

			std::vector<e_path_type> e_path_type_c::vec()
			{
				std::vector<e_path_type> result;
				result.push_back(e_path_type::NONE_PATH_TYPE           	);
				result.push_back(e_path_type::STRAIGHT     		);
				result.push_back(e_path_type::CIRCULAR_LEFT 	);
				result.push_back(e_path_type::CIRCULAR_RIGHT 	);
				result.push_back(e_path_type::ANY            	);
				return result;
			}

			e_path_type e_path_type_c::parse(std::string str)
			{
				std::string str_l = mstr::to_lower(str);

				std::vector<e_path_type> v = e_path_type_c::vec();

				for (unsigned int i = 0; i < v.size(); i++)
				{
					std::string t = e_path_type_c::str(v.at(i));
					if (str_l == mstr::to_lower(t))
					{
						return v.at(i);
					}
				}

				throw std::invalid_argument("Could not parse the given value since no match was found.");
			}


		} // namespace laban
	} // namespace fl
} // namespace mae
