//
// Created by furylynx on 2018-07-26
//

#ifndef MAE_MATH_ANGULAR_DISTANCE_HPP
#define MAE_MATH_ANGULAR_DISTANCE_HPP

//custom includes
#include "i_distance_measure.hpp"

//global includes
#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>
#include <algorithm>

//defines
#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif


namespace mae
{
    namespace math
    {
        class angular_distance : public mae::math::i_distance_measure<std::vector<double> > {

        public:
            angular_distance();
            virtual ~angular_distance();

            virtual double distance(std::vector<double> element1, std::vector<double> element2) const;

        private:
            unsigned int p_;
        };

    } // namespace math
} // namespace mae

#endif //MAE_MATH_ANGULAR_DISTANCE_HPP
