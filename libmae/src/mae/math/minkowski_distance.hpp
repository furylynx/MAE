//
// Created by furylynx on 2017-10-23
//

#ifndef MAE_MATH_MINKOWSKI_DISTANCE_HPP
#define MAE_MATH_MINKOWSKI_DISTANCE_HPP

//custom includes
#include "i_distance_measure.hpp"

//global includes
#include <memory>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>


namespace mae
{
    namespace math
    {
        class minkowski_distance : public mae::math::i_distance_measure<std::vector<double> > {

        public:
            minkowski_distance(unsigned int p = 1);
            ~minkowski_distance();

            virtual double distance(std::vector<double> element1, std::vector<double> element2) const;

        private:
            unsigned int p_;
        };

    } // namespace math
} // namespace mae

#endif //MAE_MATH_MINKOWSKI_DISTANCE_HPP
