#include "e_turn_direction.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{
				std::string e_turn_direction_c::str(e_turn_direction turn)
				{
					switch (turn)
					{
					case e_turn_direction::NONE_TURN_DIRECTION 				: return "none";
					case e_turn_direction::COUNTER_CLOCKWISE	: return "counterClockwise";
					case e_turn_direction::CLOCKWISE        	: return "clockwise";
					case e_turn_direction::ANY               	: return "any";
					}

					throw std::invalid_argument("Enum value not listed in the str() method");
				}

				std::vector<e_turn_direction> e_turn_direction_c::vec()
				{
					std::vector<e_turn_direction> result;
					result.push_back(e_turn_direction::NONE_TURN_DIRECTION 			);
					result.push_back(e_turn_direction::COUNTER_CLOCKWISE);
					result.push_back(e_turn_direction::CLOCKWISE        );
					result.push_back(e_turn_direction::ANY              );

					return result;
				}

				int e_turn_direction_c::to_int(e_turn_direction eturndirection)
				{
					return (int) eturndirection;
				}

				e_turn_direction e_turn_direction_c::parse(std::string str)
				{
					std::string str_l = mstr::to_lower(str);

					std::vector<e_turn_direction> v = e_turn_direction_c::vec();

					for (unsigned int i = 0; i < v.size(); i++)
					{
						std::string t = e_turn_direction_c::str(v.at(i));
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
