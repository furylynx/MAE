//
// Created by furylynx on 2017-10-27
//

#ifndef MAE_MATH_COSINE_SIMILARITY_HPP
#define MAE_MATH_COSINE_SIMILARITY_HPP

//custom includes
#include "i_similarity_measure.hpp"
#include "cosine_distance.hpp"
#include "math.hpp"

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
        class cosine_similarity : public mae::math::i_similarity_measure<std::vector<double> > {

        public:
            cosine_similarity();
            virtual ~cosine_similarity();

            virtual double similarity(std::vector<double> element1, std::vector<double> element2) const;

        private:
            std::shared_ptr<cosine_distance> cosine_distance_;
        };

    } // namespace math
} // namespace mae

#endif //MAE_MATH_COSINE_SIMILARITY_HPP
