#include "e_space_direction.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{
				std::string e_space_direction_c::str(e_space_direction space_direction)
				{
					switch (space_direction)
					{
					case e_space_direction::NONE_SPACE_DIRECTION       		: return "none";
					case e_space_direction::LEFT 			: return "left";
					case e_space_direction::FRONT_LEFT 		: return "frontLeft";
					case e_space_direction::FRONT      		: return "front";
					case e_space_direction::FRONT_RIGHT		: return "frontRight";
					case e_space_direction::RIGHT      		: return "right";
					case e_space_direction::BACK_RIGHT 		: return "backRight";
                    case e_space_direction::BACK          	: return "back";
                    case e_space_direction::BACK_LEFT     	: return "backLeft";
					}

					throw std::invalid_argument("Enum value not listed in the str() method");
				}

				std::vector<e_space_direction> e_space_direction_c::vec()
				{
					std::vector<e_space_direction> result;
					result.push_back(e_space_direction::NONE_SPACE_DIRECTION       	);
					result.push_back(e_space_direction::LEFT 		);
					result.push_back(e_space_direction::FRONT_LEFT 	);
					result.push_back(e_space_direction::FRONT      	);
					result.push_back(e_space_direction::FRONT_RIGHT	);
					result.push_back(e_space_direction::RIGHT      	);
					result.push_back(e_space_direction::BACK_RIGHT 	);
					result.push_back(e_space_direction::BACK        );
					result.push_back(e_space_direction::BACK_LEFT   );

					return result;
				}

				int e_space_direction_c::to_int(e_space_direction espacedirection)
				{
					return (int) espacedirection;
				}

				e_space_direction e_space_direction_c::parse(std::string str)
				{
					std::string str_l = mstr::to_lower(str);

					std::vector<e_space_direction> v = e_space_direction_c::vec();

					for (unsigned int i = 0; i < v.size(); i++)
					{
						std::string t = e_space_direction_c::str(v.at(i));
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
