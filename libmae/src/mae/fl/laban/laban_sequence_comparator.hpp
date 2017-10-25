//
// Created by furylynx on 2017-10-23
//

#ifndef MAE_LABAN_SEQUENCE_COMPARATOR_HPP
#define MAE_LABAN_SEQUENCE_COMPARATOR_HPP

//custom includes
#include "laban_sequence.hpp"
#include "mv/i_symbol.hpp"
#include "movement_comparator.hpp"
#include "../../math/i_distance_measure.hpp"


//global includes
#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>


namespace mae {
    namespace fl {
        namespace laban {

            class laban_sequence_comparator : public mae::math::i_distance_measure<std::shared_ptr<laban_sequence> >
            {
                public:

                    /**
                     * Creates a new comparator for laban sequences used to get the similarity between two scores.
                     *
                     * @param distance_measure The distance measure for single movement symbols ignoring the length.
                     * @param steps_per_beat The number of frames to be used for each beat. Zero for no time slicing.
                     */
                    laban_sequence_comparator(std::shared_ptr<mae::math::i_distance_measure<std::vector<std::shared_ptr<i_movement> > > > distance_measure = std::make_shared<mae::math::dtw<std::shared_ptr<i_movement> > >(std::make_shared<movement_comparator>()), unsigned int steps_per_beat = 6);
                    virtual ~laban_sequence_comparator();

                    /**
                     * Returns the distance between the two elements.
                     *
                     * @param element1 The first element to compare.
                     * @param element2 The second element to compare.
                     * @return The distance.
                     */
                    double distance(std::shared_ptr<laban_sequence> element1, std::shared_ptr<laban_sequence> element2) const;

                private:
                    std::shared_ptr<mae::math::i_distance_measure<std::vector<std::shared_ptr<i_movement> > > > distance_measure_;
                    unsigned int steps_per_beat_;

                    std::vector<std::shared_ptr<column_definition> > default_definitions_;

            };


        } // namespace laban
    } // namespace fl
} // namespace mae



#endif //MAE_LABAN_SEQUENCE_COMPARATOR_HPP
