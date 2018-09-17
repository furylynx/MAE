//
// Created on 2018-09-17
//

#ifndef MAE_MATH_I_ALIGNED_DISTANCE_MEASURE_HPP
#define MAE_MATH_I_ALIGNED_DISTANCE_MEASURE_HPP

//custom includes
#include "aligned_distance_details.hpp"

//global includes
#include <vector>

namespace mae
{
    namespace math
    {
        /**
         * Distance measure interface.
         */
        template<typename T>
        class i_aligned_distance_measure
        {
            public:
                virtual ~i_aligned_distance_measure()
                {}
                
                /**
                 * Returns the optimal alignment between the two elements.
                 *
                 * @param element1 The first element to compare.
                 * @param element2 The second element to compare.
                 */
                virtual aligned_distance_details optimal_alignment(std::vector<T> target_sequence, std::vector<T> actual_sequence) const = 0;
        };
    }
}
#endif //MAE_MATH_I_ALIGNED_DISTANCE_MEASURE_HPP
