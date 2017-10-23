//
// Created by furylynx on 2017-10-23
//

#include "minkowski_distance.hpp"

namespace mae
{
    namespace math
    {
        minkowski_distance::minkowski_distance(unsigned int p)
        {
            p_ = p;
        }

        minkowski_distance::~minkowski_distance()
        {

        }

        double minkowski_distance::distance(std::vector<double> element1, std::vector<double> element2) const
        {
            if (element1.size() != element2.size())
            {
                throw std::invalid_argument(
                        "Vectors have different size.");
            }

            double sum = 0;
            for (std::size_t i = 0; i < element1.size(); i++)
            {
                sum += std::pow(std::abs(element1.at(i) - element2.at(i)), p_);
            }

            return std::pow(sum, 1/(double)p_);
        }

    } // namespace math
} // namespace mae