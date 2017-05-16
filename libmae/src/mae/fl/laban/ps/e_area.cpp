#include "e_area.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{
				std::string e_area_c::str(e_area area)
				{
					switch (area)
					{
					case e_area::NONE_AREA 		: return "none";
					case e_area::HEAD 		: return "head";
					case e_area::CHEST		: return "chest";
					case e_area::WAIST		: return "waist";
					case e_area::PELVIS		: return "pelvis";
					case e_area::TORSO 		: return "torso";
					}

					throw std::invalid_argument("Enum value not listed in the str() method");
				}

				std::vector<e_area> e_area_c::vec()
				{
					std::vector<e_area> result;
					result.push_back(e_area::NONE_AREA 		);
					result.push_back(e_area::HEAD 	  	);
					result.push_back(e_area::CHEST	 	);
					result.push_back(e_area::WAIST	  	);
					result.push_back(e_area::PELVIS		);
					result.push_back(e_area::TORSO 		);

					return result;
				}

				e_area e_area_c::parse(std::string str)
				{
					std::string str_l = mstr::to_lower(str);

					std::vector<e_area> v = e_area_c::vec();

					for (unsigned int i = 0; i < v.size(); i++)
					{
						std::string t = e_area_c::str(v.at(i));
						if (str_l == mstr::to_lower(t))
						{
							return v.at(i);
						}
					}

					throw std::invalid_argument("Could not parse the given value since no match was found.");
				}


			} // namespace ps
		} // namespace laban
	} // namespace fl
} // namespace mae
