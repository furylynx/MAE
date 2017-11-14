//
// Created by furylynx on 2017-11-14
//

#ifndef MAE_MATH_MAHALANOBIS_DISTANCE_HPP
#define MAE_MATH_MAHALANOBIS_DISTANCE_HPP


//custom includes
#include "i_distance_measure.hpp"

//global includes
#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>

namespace mae
{
    namespace math
    {

        class mahalanobis_distance : public mae::math::i_distance_measure<std::vector<double> >
        {

        public:
            mahalanobis_distance();
            virtual ~mahalanobis_distance();

            virtual double distance(std::vector<double> element1, std::vector<double> element2) const;
        };

    } // namespace math
} // namespace mae


#endif //MAE_MATH_MAHALANOBIS_DISTANCE_HPP
