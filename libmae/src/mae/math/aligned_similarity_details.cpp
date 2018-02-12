//
// Created on 2017-11-08
//

#include "aligned_similarity_details.hpp"

namespace mae
{
    namespace math
    {

        aligned_similarity_details::aligned_similarity_details(double startpos, double endpos, double similarity)
        {
            startpos_ = startpos;
            endpos_ = endpos;
            similarity_ = similarity;
        }

        aligned_similarity_details::~aligned_similarity_details()
        {

        }

        double aligned_similarity_details::get_startpos() const
        {
            return startpos_;
        }

        double aligned_similarity_details::get_endpos() const
        {
            return endpos_;
        }

        double aligned_similarity_details::get_similarity() const
        {
            return similarity_;
        }

    } // namespace math
} // namespace mae