//
// Created by furylynx on 2017-10-27
//

#include "cosine_similarity.hpp"

namespace mae
{
    namespace math
    {
        cosine_similarity::cosine_similarity()
        {
            cosine_distance_ = std::make_shared<cosine_distance>();
        }

        cosine_similarity::~cosine_similarity()
        {

        }

        double cosine_similarity::similarity(std::vector<double> element1, std::vector<double> element2) const
        {
            return 1 - cosine_distance_->distance(element1, element2);
        }

    } // namespace math
} // namespace mae