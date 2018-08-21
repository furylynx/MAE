#include "e_blur_strategy.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{

			std::string e_blur_strategy_c::str(e_blur_strategy type)
			{
				switch (type)
				{
					case e_blur_strategy::NONE_BLUR_STRATEGY	: return "none";
					case e_blur_strategy::HOLD     				: return "hold";
					case e_blur_strategy::BLUR 					: return "blur";
				}

				throw std::invalid_argument("Enum value not listed in the str() method");
			}

			std::vector<e_blur_strategy> e_blur_strategy_c::vec()
			{
				std::vector<e_blur_strategy> result;
				result.push_back(e_blur_strategy::NONE_BLUR_STRATEGY);
				result.push_back(e_blur_strategy::HOLD);
				result.push_back(e_blur_strategy::BLUR);
				return result;
			}

			int e_blur_strategy_c::to_int(e_blur_strategy eblurstrategy)
			{
				return (int) eblurstrategy;
			}

			int e_blur_strategy_c::max()
			{
				return (int) e_blur_strategy::BLUR;
			}

			e_blur_strategy e_blur_strategy_c::parse(std::string str)
			{
				std::string str_l = mstr::to_lower(str);

				std::vector<e_blur_strategy> v = e_blur_strategy_c::vec();

				for (unsigned int i = 0; i < v.size(); i++)
				{
					std::string t = e_blur_strategy_c::str(v.at(i));
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
