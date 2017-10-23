//
// Created on 23.10.17.
//

#ifndef MAE_FL_LABAN_MV_SYMBOL_FL_DISTANCE_HPP
#define MAE_FL_LABAN_MV_SYMBOL_FL_DISTANCE_HPP


//custom includes
#include "../../../math/math.hpp"
#include "i_symbol.hpp"
#include "cancellation_symbol.hpp"
#include "direction_symbol.hpp"
#include "space_symbol.hpp"
#include "turn_symbol.hpp"
#include "vibration_symbol.hpp"

//global includes
#include <string>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <typeinfo>


namespace mae
{
    namespace fl
    {
        namespace laban
        {
            namespace mv
            {

                class symbol_fl_distance : public mae::math::i_distance_measure<std::shared_ptr<i_symbol> >
                {
                public:
                    /**
                     * Creates a distance measure for symbols using chosen distances for different symbols.
                     *
                     * @param distance_measure The distance measure to compare two vectors.
                     */
                    symbol_fl_distance(std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure = std::make_shared<mae::math::minkowski_distance>());
                    virtual ~symbol_fl_distance();


                    /**
                     * Returns the distance between the two elements.
                     *
                     * @param element1 The first element to compare.
                     * @param element2 The second element to compare.
                     */
                    virtual double distance(std::shared_ptr<i_symbol> element1, std::shared_ptr<i_symbol> element2) const;


                private:

                    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure_;

                };

            } // namespace mv
        } // namespace laban
    } // namespace fl
} // namespace mae
#endif //MAE_FL_LABAN_MV_SYMBOL_FL_DISTANCE_HPP
