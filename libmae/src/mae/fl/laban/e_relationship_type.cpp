/*
 * e_relationship_type.cpp
 *
 *  Created on: 22.08.2014
 *      Author: keks
 */

#include "e_relationship_type.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{


			std::string e_relationship_type_c::str(e_relationship_type type)
			{
				switch (type)
				{
				case e_relationship_type::NONE    			: return "none";
				case e_relationship_type::ADDRESS			: return "address";
				case e_relationship_type::NEAR   			: return "near";
                case e_relationship_type::TOUCH          	: return "touch";
                case e_relationship_type::SUPPORT         	: return "support";
				}

				throw std::invalid_argument("Enum value not listed in the str() method");
			}

			std::vector<e_relationship_type> e_relationship_type_c::vec()
			{
				std::vector<e_relationship_type> result;
				result.push_back(e_relationship_type::NONE    	);
				result.push_back(e_relationship_type::ADDRESS	);
				result.push_back(e_relationship_type::NEAR   	);
				result.push_back(e_relationship_type::TOUCH    );
				result.push_back(e_relationship_type::SUPPORT  );
				return result;
			}

			e_relationship_type e_relationship_type_c::parse(std::string str)
			{
				std::string str_l = mstr::to_lower(str);

				std::vector<e_relationship_type> v = e_relationship_type_c::vec();

				for (unsigned int i = 0; i < v.size(); i++)
				{
					std::string t = e_relationship_type_c::str(v.at(i));
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
