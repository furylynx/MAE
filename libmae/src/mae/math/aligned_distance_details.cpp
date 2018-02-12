//
// Created on 2018-02-18
//

#include "aligned_distance_details.hpp"



namespace mae
{
    namespace math
    {

        aligned_distance_details::aligned_distance_details(double startpos, double endpos, double distance)
        {
            startpos_ = startpos;
            endpos_ = endpos;
            distance_ = distance;
        }

        aligned_distance_details::~aligned_distance_details()
        {

        }

        double aligned_distance_details::get_startpos() const
        {
            return startpos_;
        }

        double aligned_distance_details::get_endpos() const
        {
            return endpos_;
        }

        double aligned_distance_details::get_distance() const
        {
            return distance_;
        }

    } // namespace math
} // namespace mae