//
// Created on 2018-02-18
//

#include "aligned_distances_details.hpp"


namespace mae
{
    namespace math
    {

        aligned_distances_details::aligned_distances_details(double startpos, double endpos, std::vector<double> distances, std::vector<std::vector<warping_path_element> > warping_paths)
        {
            startpos_ = startpos;
            endpos_ = endpos;
            distances_ = distances;
            warping_paths_ = warping_paths;
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

        std::vector<std::vector<warping_path_element> > aligned_distances_details::get_warping_paths() const
        {
            return warping_paths_;
        }

    } // namespace math
} // namespace mae