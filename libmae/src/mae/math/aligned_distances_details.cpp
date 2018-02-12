//
// Created on 2018-02-18
//

#include "aligned_distances_details.hpp"


namespace mae
{
    namespace math
    {

        aligned_distances_details::aligned_distances_details(double startpos, double endpos, std::vector<double> distances)
        {
            startpos_ = startpos;
            endpos_ = endpos;
            distances_ = distances;
        }

        aligned_distances_details::~aligned_distances_details()
        {

        }

        double aligned_distances_details::get_startpos() const
        {
            return startpos_;
        }

        double aligned_distances_details::get_endpos() const
        {
            return endpos_;
        }

        std::vector<double> aligned_distances_details::get_distances() const
        {
            return distances_;
        }

    } // namespace math
} // namespace mae