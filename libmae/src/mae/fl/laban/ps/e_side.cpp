#include "e_side.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace ps
			{

				std::string e_side_c::str(e_side e_side_)
				{
					switch (e_side_)
					{
					case e_side::NONE_SIDE:
						return "none";
					case e_side::LEFT:
						return "left";
					case e_side::RIGHT:
						return "right";
					}

					throw std::invalid_argument("Enum value not listed in the str() method");
				}

				std::vector<e_side> e_side_c::vec()
				{
					std::vector<e_side> result;
					result.push_back(e_side::NONE_SIDE 		);
					result.push_back(e_side::LEFT 	  	);
					result.push_back(e_side::RIGHT	 	);

					return result;
				}

				int e_side_c::to_int(e_side eside)
				{
					return (int) eside;
				}

				int e_side_c::max()
				{
					return (int) e_side::RIGHT;
				}

				e_side e_side_c::parse(std::string str)
				{
					std::string str_l = mstr::to_lower(str);

					std::vector<e_side> v = e_side_c::vec();

					for (unsigned int i = 0; i < v.size(); i++)
					{
						std::string t = e_side_c::str(v.at(i));
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
