//
// Created on 2018-02-18
//

#include "aligned_distance_details.hpp"



namespace mae
{
    namespace math
    {

        aligned_distance_details::aligned_distance_details(double startpos, double endpos, double distance, std::vector<warping_path_element> warping_path)
        {
            startpos_ = startpos;
            endpos_ = endpos;
            distance_ = distance;
            warping_path_ = warping_path;
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

        std::vector<warping_path_element> aligned_distance_details::get_warping_path() const
        {
            return warping_path_;
        }

    } // namespace math
} // namespace mae