//
// Created on 06.11.17.
//

#ifndef MAE_FL_LABAN_TARGET_SEQUENCE_COMPARATOR_HPP
#define MAE_FL_LABAN_TARGET_SEQUENCE_COMPARATOR_HPP


//custom includes
#include "laban_sequence.hpp"
#include "mv/i_symbol.hpp"
#include "movement_comparator.hpp"
#include "laban_subsequence_mapper.hpp"
#include "laban_sequence_comparator.hpp"
#include "../../math/i_similarity_measure.hpp"


//global includes
#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>


namespace mae {
    namespace fl {
        namespace laban {

            class laban_target_sequence_comparator : public mae::math::i_similarity_measure<std::shared_ptr<laban_sequence> >
            {
            public:
                /**
                 * Creates a new target sequence comparator for laban sequences used to get the similarity between the target sequence and the closest subsequence of the .
                 *
                 * @param laban_sequence_comparator The comparator for laban sequences.
                 * @param fixed_end True for a fixed end. Just need to vary in start position.
                 * @param frames_per_beat The number of frames to be used for each beat. Zero for no time slicing (using the exact sequence without modifications).
                 */
                laban_target_sequence_comparator(std::shared_ptr<laban_sequence_comparator> laban_sequence_comparator, bool fixed_end = false, unsigned int frames_per_beat = 6 );

                virtual ~laban_target_sequence_comparator();


                /**
                 * Returns the similarity between the two elements taking the best matching subsequence into account.
                 *
                 * @param target_sequence The target sequence.
                 * @param actual_sequence The actual sequence.
                 * @return The similarity.
                 */
                double similarity(std::shared_ptr<laban_sequence> target_sequence, std::shared_ptr<laban_sequence> actual_sequence) const;

            private:
                std::shared_ptr<laban_sequence_comparator> laban_sequence_comparator_;
                bool fixed_end_;
                unsigned int frames_per_beat_;

                /**
                 * Cuts the given sequence returning a new instance being cut.
                 *
                 * @param sequence The sequence to be cut.
                 * @param startpos The startpos in beats.
                 * @param endpos The endpos in beats.
                 * @return The modified sequence.
                 */
                std::shared_ptr<laban_sequence> cut_sequence(std::shared_ptr<laban_sequence> sequence, double startpos, double endpos) const;
            };


        } // namespace laban
    } // namespace fl
} // namespace mae


#endif //MAE_FL_LABAN_TARGET_SEQUENCE_COMPARATOR_HPP
