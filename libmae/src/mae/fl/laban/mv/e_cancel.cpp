#include "e_cancel.hpp"

namespace mae
{
	namespace fl
	{
		namespace laban
		{
			namespace mv
			{

				std::string e_cancel_c::str(e_cancel cancel)
				{
					switch (cancel)
					{
					case e_cancel::NONE_CANCEL           		: return "none";
					case e_cancel::BACK_NORMAL    		: return "back-normal";
					case e_cancel::RELEASE_CONTACT 		: return "release-contact";
					}

					throw std::invalid_argument("Enum value not listed in the str() method");
				}

				std::vector<e_cancel> e_cancel_c::vec()
				{
					std::vector<e_cancel> result;
					result.push_back(e_cancel::NONE_CANCEL           	);
					result.push_back(e_cancel::BACK_NORMAL      );
					result.push_back(e_cancel::RELEASE_CONTACT 	);

					return result;
				}

				e_cancel e_cancel_c::parse(std::string str)
				{
					std::string str_l = mstr::to_lower(str);

					std::vector<e_cancel> v = e_cancel_c::vec();

					for (unsigned int i = 0; i < v.size(); i++)
					{
						std::string t = e_cancel_c::str(v.at(i));
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
