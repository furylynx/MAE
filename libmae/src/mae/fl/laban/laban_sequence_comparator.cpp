//
// Created by furylynx on 2017-10-23
//

#include "laban_sequence_comparator.hpp"



namespace mae
{
    namespace fl
    {
        namespace laban
        {

            laban_sequence_comparator::laban_sequence_comparator(std::shared_ptr<mae::math::i_distance_measure<std::vector<std::shared_ptr<mv::i_symbol> > > > distance_measure, unsigned int steps_per_beat)
            {
                distance_measure_ = distance_measure;
                steps_per_beat_ = steps_per_beat;
            }

            laban_sequence_comparator::~laban_sequence_comparator()
            {

            }

            double laban_sequence_comparator::distance(std::shared_ptr<laban_sequence> element1, std::shared_ptr<laban_sequence> element2) const
            {

                //TODO

                //for each column: quantize symbol

                //map columns
                //dtw for column elements
                //distance to similarity

                //average similarities

                return 0;
            }


        } // namespace laban
    } // namespace fl
} // namespace mae
