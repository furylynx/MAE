//
// Created on 2018-03-09
//

#ifndef MAE_MATH_I_ALIGNED_SIMILARITY_MEASURE_HPP
#define MAE_MATH_I_ALIGNED_SIMILARITY_MEASURE_HPP

//custom includes
#include "i_similarity_measure.hpp"
#include "aligned_similarity_details.hpp"

//global includes
//...

namespace mae
{
        namespace math
        {
                /**
                 * Similarity measure interface.
                 */
                template<typename T>
                class i_aligned_similarity_measure : public i_similarity_measure<T>
                {
                    public:
                        virtual ~i_aligned_similarity_measure(){}

                        /**
                         * Returns the similarity details between the two elements. Zero represents no similarity and one represents identity.
                         *
                         * @param element1 The first element to compare.
                         * @param element2 The second element to compare.
                         * @return The similarity details.
                         */
                        virtual mae::math::aligned_similarity_details similarity_details(T element1, T element2) const = 0;
                };

        }
}
#endif //MAE_MATH_I_ALIGNED_SIMILARITY_MEASURE_HPP
