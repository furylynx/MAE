//
// Created on 23.10.17.
//

#ifndef MAE_FL_LABAN_MV_SYMBOL_FL_DISTANCE_HPP
#define MAE_FL_LABAN_MV_SYMBOL_FL_DISTANCE_HPP


//custom includes
#include "../../math/math.hpp"
#include "i_movement.hpp"

//global includes
#include <string>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <typeinfo>
#include <limits>


namespace mae
{
    namespace fl
    {
        namespace laban
        {

            class movement_comparator : public mae::math::i_distance_measure<std::shared_ptr<i_movement> >
            {
            public:
                /**
                 * Creates a distance measure for symbols using chosen distances for different symbols.
                 *
                 * @param distance_measure The distance measure to compare two vectors.
                 */
                movement_comparator(std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure = std::make_shared<mae::math::minkowski_distance>());
                virtual ~movement_comparator();


                /**
                 * Returns the distance between the two elements.
                 *
                 * @param element1 The first element to compare.
                 * @param element2 The second element to compare.
                 * @return The distance.
                 */
                virtual double distance(std::shared_ptr<i_movement> element1, std::shared_ptr<i_movement> element2) const;


            private:

                std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure_;

            };

        } // namespace laban
    } // namespace fl
} // namespace mae
#endif //MAE_FL_LABAN_MV_SYMBOL_FL_DISTANCE_HPP
