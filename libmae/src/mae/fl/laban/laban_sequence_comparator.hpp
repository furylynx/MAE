//
// Created by furylynx on 2017-10-23
//

#ifndef MAE_LABAN_SEQUENCE_COMPARATOR_HPP
#define MAE_LABAN_SEQUENCE_COMPARATOR_HPP

//custom includes
#include "laban_sequence.hpp"
#include "mv/i_symbol.hpp"
#include "mv/symbol_fl_distance.hpp"
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
                    laban_sequence_comparator(std::shared_ptr<mae::math::i_distance_measure<std::vector<std::shared_ptr<mv::i_symbol> > > > distance_measure = std::make_shared<mae::math::dtw<std::shared_ptr<mv::i_symbol> > >(std::make_shared<mv::symbol_fl_distance>()), unsigned int steps_per_beat = 6);
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
                    std::shared_ptr<mae::math::i_distance_measure<std::vector<std::shared_ptr<mv::i_symbol> > > > distance_measure_;
                    unsigned int steps_per_beat_;

            };


        } // namespace laban
    } // namespace fl
} // namespace mae



#endif //MAE_LABAN_SEQUENCE_COMPARATOR_HPP
