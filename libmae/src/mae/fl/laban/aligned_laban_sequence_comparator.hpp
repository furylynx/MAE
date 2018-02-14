//
// Created by furylynx on 2018-02-13
//

#ifndef MAE_ALIGNED_LABAN_SEQUENCE_COMPARATOR_HPP
#define MAE_ALIGNED_LABAN_SEQUENCE_COMPARATOR_HPP

//custom includes
#include "laban_sequence.hpp"
#include "mv/i_symbol.hpp"
#include "movement_comparator.hpp"
#include "laban_subsequence_mapper.hpp"
#include "../../math/i_similarity_measure.hpp"
#include "../../math/aligned_distance.hpp"
#include "../../mos.hpp"


//global includes
#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>


namespace mae {
    namespace fl {
        namespace laban {

            class aligned_laban_sequence_comparator : public mae::math::i_similarity_measure<std::shared_ptr<laban_sequence> >
            {
                public:

                    /**
                     * Creates a new comparator for laban sequences used to get the similarity between two scores.
                     *
                     * @param distance_measure The distance measure for single movement symbols ignoring the length.
                     * @param ignore_empty_columns True to set distance for columns between two columns to zero if one column contains no elements (which by definition means any movements are allowed).
                     * @param frames_per_beat_ The number of frames to be used for each beat. Zero for no time slicing (using the exact sequence without modifications).
                     */
                    aligned_laban_sequence_comparator(std::shared_ptr<mae::math::aligned_distance<std::vector<std::shared_ptr<i_movement> > > > aligned_distance_measure = std::make_shared<mae::math::aligned_distance<std::shared_ptr<i_movement> >(std::make_shared<mae::math::dtw<std::shared_ptr<i_movement> > >(std::make_shared<movement_comparator>(), bool ignore_empty_columns = false, unsigned int frames_per_beat = 6 ));

                    virtual ~aligned_laban_sequence_comparator();

                    /**
                     * Returns the similarity between the two elements.
                     *
                     * @param element1 The first element to compare.
                     * @param element2 The second element to compare.
                     * @return The distance.
                     */
                    double similarity(std::shared_ptr<laban_sequence> element1, std::shared_ptr<laban_sequence> element2) const;

                    /**
                     * Returns the similarity between the two elements.
                     *
                     * @param element1 The first element to compare.
                     * @param element2 The second element to compare.
                     * @param mapper The mapper
                     * @return The distance.
                     */
                    double similarity(std::shared_ptr<laban_sequence> element1, std::shared_ptr<laban_sequence> element2, std::shared_ptr<laban_subsequence_mapper> mapper) const;

                private:
                    std::shared_ptr<mae::math::aligned_distance<std::shared_ptr<i_movement> > > distance_measure_;
                    unsigned int frames_per_beat_;
                    bool ignore_empty_columns_;
                    std::vector<std::shared_ptr<column_definition> > default_definitions_;

                    /**
                     * Creates the streched sequence using the frames per beat factor. If the factor is zero, the given sequence will just be returned. If the factor for one symbol is less than one, one symbol will be inserted instead of zero.
                     *
                     * @param non_streched The original sequence.
                     * @param beats_per_measure The number of beats per measure.
                     * @return The streched sequence.
                     *
                     */
                    virtual std::vector<std::shared_ptr<i_movement> > create_stretched(std::vector<std::shared_ptr<i_movement> > non_streched, unsigned int beats_per_measure) const;

            };


        } // namespace laban
    } // namespace fl
} // namespace mae



#endif //MAE_ALIGNED_LABAN_SEQUENCE_COMPARATOR_HPP
