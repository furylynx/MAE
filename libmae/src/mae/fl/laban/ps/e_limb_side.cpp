#include "e_limb_side.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{
				std::string e_limb_side_c::str(e_limb_side lside)
				{
					switch (lside)
					{
					case e_limb_side::NONE_LIMB_SIDE             		: return "none";
					case e_limb_side::INNER            		: return "inner";
					case e_limb_side::OUTER            		: return "outer";
					case e_limb_side::LITTLEFINGER     		: return "littleFinger";
					case e_limb_side::THUMB            		: return "thumb";
					case e_limb_side::OUTERLITTLEFINGER		: return "outer-littleFinger";
					case e_limb_side::INNERLITTLEFINGER		: return "inner-littleFinger";
					case e_limb_side::OUTERTHUMB       		: return "outer-thumb";
					case e_limb_side::INNERTHUMB        	: return "inner-thumb";
					}

					throw std::invalid_argument("Enum value not listed in the str() method");
				}


				std::vector<e_limb_side> e_limb_side_c::vec()
				{
					std::vector<e_limb_side> result;
					result.push_back(e_limb_side::NONE_LIMB_SIDE             );
					result.push_back(e_limb_side::INNER            );
					result.push_back(e_limb_side::OUTER            );
					result.push_back(e_limb_side::LITTLEFINGER     );
					result.push_back(e_limb_side::THUMB            );
					result.push_back(e_limb_side::OUTERLITTLEFINGER);
					result.push_back(e_limb_side::INNERLITTLEFINGER);
					result.push_back(e_limb_side::OUTERTHUMB       );
					result.push_back(e_limb_side::INNERTHUMB       );
					return result;
				}

				int e_limb_side_c::to_int(e_limb_side elimbside)
				{
					return (int) elimbside;
				}

				e_limb_side e_limb_side_c::parse(std::string str)
				{
					std::string str_l = mstr::to_lower(str);

					std::vector<e_limb_side> v = e_limb_side_c::vec();

					for (unsigned int i = 0; i < v.size(); i++)
					{
						std::string t = e_limb_side_c::str(v.at(i));
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
