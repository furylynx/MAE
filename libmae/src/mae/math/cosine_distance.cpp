//
// Created by furylynx on 2017-10-27
//

#include "cosine_distance.hpp"

namespace mae
{
    namespace math
    {
        cosine_distance::cosine_distance()
        {
        }

        cosine_distance::~cosine_distance()
        {

        }

        double cosine_distance::distance(std::vector<double> element1, std::vector<double> element2) const
        {
            if (element1.size() != element2.size())
            {
                throw std::invalid_argument(
                        "Vectors have different size.");
            }

            double sum = 0;
            double sum_a = 0;
            double sum_b = 0;

            for (std::size_t i = 0; i < element1.size(); i++)
            {
                sum += element1.at(i) * element2.at(i);
                sum_a += std::pow(element1.at(i), 2);
                sum_b += std::pow(element2.at(i), 2);
            }

            double cosine_distance = 0;
            if (0 != sum_a && 0 != sum_b)
            {
                cosine_distance = 1 - (sum/(std::pow(sum_a,1/(double)2) * std::pow(sum_b,1/(double)2)));
            }

            return cosine_distance;
        }

    } // namespace math
} // namespace mae