//
// Created on 2017-11-29
//

#include "sologub_tree_type_distance.hpp"

namespace mae
{
    namespace math
    {
        sologub_tree_type_distance::sologub_tree_type_distance(double distance_offset)
        {
            distance_offset_ = distance_offset;
        }

        sologub_tree_type_distance::~sologub_tree_type_distance()
        {

        }

        double sologub_tree_type_distance::distance(std::vector<std::type_index> element1, std::vector<std::type_index> element2) const
        {

            for (std::size_t i = 1 ; i <= element1.size() ; i++)
            {
                for (std::size_t j = 1; j <= element2.size(); j++)
                {
                    if (element1.at(element1.size()-i) == element2.at(element2.size()-j))
                    {
                        //found lowest common ancestor at element1.size()-i, element2.size()-j

                        //direct distance between nodes
                        double direct = i+j;
                        double lcadist = std::min(element1.size()-i, element2.size()-j);

                        return (direct/(1+lcadist+direct)) + distance_offset_;
                    }
                }
            }

            //no common ancestor

            return std::numeric_limits<double>::infinity();
        }

    } // namespace math
} // namespace mae