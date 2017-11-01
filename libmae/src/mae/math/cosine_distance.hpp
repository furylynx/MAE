//
// Created by furylynx on 2017-10-27
//

#ifndef MAE_MATH_COSINE_DISTANCE_HPP
#define MAE_MATH_COSINE_DISTANCE_HPP

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
        class cosine_distance : public mae::math::i_distance_measure<std::vector<double> > {

        public:
            cosine_distance();
            virtual ~cosine_distance();

            virtual double distance(std::vector<double> element1, std::vector<double> element2) const;

        private:
            unsigned int p_;
        };

    } // namespace math
} // namespace mae

#endif //MAE_MATH_COSINE_DISTANCE_HPP
