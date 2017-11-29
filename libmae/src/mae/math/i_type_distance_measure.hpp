//
// Created on 2017-11-29
//

#ifndef MAE_MATH_I_TYPE_DISTANCE_MEASURE_HPP
#define MAE_MATH_I_TYPE_DISTANCE_MEASURE_HPP

//custom includes
#include "i_distance_measure.hpp"

//global includes
#include <vector>
#include <typeindex>

namespace mae
{
        namespace math
        {
                /**
                 * Type distance measure interface.
                 */
                class i_type_distance_measure : public i_distance_measure<std::vector<std::type_index> >
                {
                    public:
                        virtual ~i_type_distance_measure(){}

                        /**
                         * Returns the type distance between the two elements.
                         *
                         * @param element1 The first element to compare.
                         * @param element2 The second element to compare.
                         */
                        virtual double distance(std::vector<std::type_index> element1, std::vector<std::type_index> element2) const = 0;
                };

        }
}
#endif //MAE_MATH_I_TYPE_DISTANCE_MEASURE_HPP
