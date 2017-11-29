//
// Created on 2017-11-29
//

#ifndef MAE_MATH_TYPE_HIERARCHY_DISTANCE_HPP
#define MAE_MATH_TYPE_HIERARCHY_DISTANCE_HPP


//custom includes
#include "i_distance_measure.hpp"

//global includes
#include <memory>
#include <vector>
#include <limits>
#include <typeindex>

namespace mae
{
    namespace math
    {
        class type_hierarchy_distance : public i_distance_measure<std::vector<std::type_index> >
        {
        public:
            /**
             * Creates a new distance measure for type hierarchies.
             *
             * @param distance_offset An offset for the distance (will be added to the distance).
             */
            type_hierarchy_distance(double distance_offset = 0);

            virtual ~type_hierarchy_distance();

            /**
             * Returns the type hierarchy distance between the two elements.
             *
             * @param element1 The first element to compare.
             * @param element2 The second element to compare.
             */
            virtual double distance(std::vector<std::type_index> element1, std::vector<std::type_index> element2) const;


        private:
            double distance_offset_;
        };

    } // namespace math
} // namespace mae

#endif //MAE_MATH_TYPE_HIERARCHY_DISTANCE_HPP
