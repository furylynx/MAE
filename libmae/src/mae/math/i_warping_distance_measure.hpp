//
// Created on 2018-02-11
//

#ifndef MAE_MATH_I_WARPING_DISTANCE_MEASURE_HPP
#define MAE_MATH_I_WARPING_DISTANCE_MEASURE_HPP

//custom includes
#include "i_distance_measure.hpp"

//global includes
#include <vector>

namespace mae
{
        namespace math
        {
                /**
                 * Warping distance measure interface.
                 */
                template<typename T>
                class i_warping_distance_measure : public i_distance_measure<T>
                {
                    public:
                        virtual ~i_warping_distance_measure(){}

                        /**
                         * Returns the warping matrix between the two elements.
                         *
                         * @param element1 The first element to compare.
                         * @param element2 The second element to compare.
                         * @return Returns the warping matrix (with warping for startpositions as third dimension). Can be used to find the optimal alignment.
                         */
                        virtual std::vector<std::vector<std::vector<double> > > warping_matrix(T element1, T element2) const = 0;
                };

        }
}
#endif //MAE_MATH_I_WARPING_DISTANCE_MEASURE_HPP
