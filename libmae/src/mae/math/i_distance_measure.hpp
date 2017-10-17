//
// Created on 17.10.17.
//

#ifndef MAE_MATH_I_DISTANCE_MEASURE_HPP
#define MAE_MATH_I_DISTANCE_MEASURE_HPP

//custom includes
//...

//global includes
//...

namespace mae
{
        namespace math
        {
                /**
                 * Distance measure interface.
                 */
                template<typename T>
                class i_distance_measure
                {
                    public:
                        virtual ~i_distance_measure(){}

                        /**
                         * Returns the distance between the two elements.
                         *
                         * @param element1 The first element to compare.
                         * @param element2 The second element to compare.
                         */
                        virtual double distance(T element1, T element2) const = 0;
                };

        }
}
#endif //MAE_MATH_I_DISTANCE_MEASURE_HPP
