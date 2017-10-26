//
// Created on 2017-10-26
//

#ifndef MAE_MATH_I_SIMILARITY_MEASURE_HPP
#define MAE_MATH_I_SIMILARITY_MEASURE_HPP

//custom includes
//...

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
                class i_similarity_measure
                {
                    public:
                        virtual ~i_similarity_measure(){}

                        /**
                         * Returns the similarity between the two elements. Zero represents no similarity while one represents identity.
                         *
                         * @param element1 The first element to compare.
                         * @param element2 The second element to compare.
                         * @return The similarity between the two elements.
                         */
                        virtual double similarity(T element1, T element2) const = 0;
                };

        }
}
#endif //MAE_MATH_I_SIMILARITY_MEASURE_HPP
