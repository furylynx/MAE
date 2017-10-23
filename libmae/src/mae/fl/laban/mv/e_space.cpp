#include "e_space.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{
				std::string e_space_c::str(e_space space)
				{
					switch (space)
					{
					case e_space::NONE_SPACE    		: return "none";
					case e_space::NARROW  		: return "narrow";
					case e_space::WIDE    		: return "wide";
					case e_space::FOLDING 		: return "folding";
					case e_space::UNFOLDING		: return "unfolding";
					case e_space::JOINING 		: return "joining";
					case e_space::SPREADING		: return "spreading";
					}

					throw std::invalid_argument("Enum value not listed in the str() method");
				};

				std::vector<e_space> e_space_c::vec()
				{
					std::vector<e_space> result;
					result.push_back(e_space::NONE_SPACE    	);
					result.push_back(e_space::NARROW  	);
					result.push_back(e_space::WIDE    	);
					result.push_back(e_space::FOLDING 	);
					result.push_back(e_space::UNFOLDING );
					result.push_back(e_space::JOINING 	);
					result.push_back(e_space::SPREADING );

					return result;
				}

				int e_space_c::to_int(e_space espace)
				{
					return (int) espace;
				}

				e_space e_space_c::parse(std::string str)
				{
					std::string str_l = mstr::to_lower(str);

					std::vector<e_space> v = e_space_c::vec();

					for (unsigned int i = 0; i < v.size(); i++)
					{
						std::string t = e_space_c::str(v.at(i));
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
