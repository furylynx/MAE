//
// Created on 2017-11-08
//

#include "subsequence_similarity_details.hpp"

namespace mae
{
    namespace math
    {

        subsequence_similarity_details::subsequence_similarity_details(double startpos, double endpos, double similarity)
        {
            startpos_ = startpos;
            endpos_ = endpos;
            similarity_ = similarity;
        }

        subsequence_similarity_details::~subsequence_similarity_details()
        {

        }

        double subsequence_similarity_details::get_startpos() const
        {
            return startpos_;
        }

        double subsequence_similarity_details::get_endpos() const
        {
            return endpos_;
        }

        double subsequence_similarity_details::get_similarity() const
        {
            return similarity_;
        }

    } // namespace math
} // namespace mae