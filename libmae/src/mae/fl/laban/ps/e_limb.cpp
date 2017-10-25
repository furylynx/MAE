#include "e_limb.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{
				std::string e_limb_c::str(e_limb limb)
				{
					switch (limb)
					{
					case e_limb::NONE_LIMB     		: return "none";
					case e_limb::ARM      		: return "arm";
					case e_limb::LEG      		: return "leg";
					case e_limb::NECK     		: return "neck";
					case e_limb::UPPER_ARM		: return "upper_arm";
					case e_limb::LOWER_ARM		: return "lower_arm";
					case e_limb::THIGH    		: return "thigh";
					case e_limb::LOWER_LEG 		: return "lower_leg";
					}

					throw std::invalid_argument("Enum value not listed in the str() method");
				}

				std::vector<e_limb> e_limb_c::vec()
				{
					std::vector<e_limb> result;
					result.push_back(e_limb::NONE_LIMB     		);
					result.push_back(e_limb::ARM      	 	);
					result.push_back(e_limb::LEG      		);
					result.push_back(e_limb::NECK     	 	);
					result.push_back(e_limb::UPPER_ARM		);
					result.push_back(e_limb::LOWER_ARM	 	);
					result.push_back(e_limb::THIGH    		);
					result.push_back(e_limb::LOWER_LEG 	 	);

					return result;
				}

				int e_limb_c::to_int(e_limb elimb)
				{
					return (int) elimb;
				}

				e_limb e_limb_c::parse(std::string str)
				{
					std::string str_l = mstr::to_lower(str);

					std::vector<e_limb> v = e_limb_c::vec();

					for (unsigned int i = 0; i < v.size(); i++)
					{
						std::string t = e_limb_c::str(v.at(i));
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
