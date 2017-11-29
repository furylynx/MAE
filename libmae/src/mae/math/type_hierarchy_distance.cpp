//
// Created on 2017-11-29
//

#include "type_hierarchy_distance.hpp"

namespace mae
{
    namespace math
    {
        type_hierarchy_distance::type_hierarchy_distance(double distance_offset)
        {
            distance_offset_ = distance_offset;
        }

        type_hierarchy_distance::~type_hierarchy_distance()
        {

        }

        double type_hierarchy_distance::distance(std::vector<std::type_index> element1, std::vector<std::type_index> element2) const
        {
            for (std::size_t i = 1 ; i <= element1.size() ; i++)
            {
                for (std::size_t j = 1; j <= element2.size(); j++)
                {
                    if (element1.at(element1.size()-i) == element2.at(element2.size()-j))
                    {
                        return i+j + distance_offset_;
                    }
                }
            }

            return std::numeric_limits<double>::infinity();
        }

    } // namespace math
} // namespace mae