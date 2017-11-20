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

            laban_sequence_comparator::laban_sequence_comparator(std::shared_ptr<mae::math::i_distance_measure<std::vector<std::shared_ptr<i_movement> > > > distance_measure,  bool ignore_empty_columns, unsigned int frames_per_beat)
            {
                distance_measure_ = distance_measure;
                ignore_empty_columns_ = ignore_empty_columns;
                frames_per_beat_ = frames_per_beat;
            }

            laban_sequence_comparator::~laban_sequence_comparator()
            {

            }

            double laban_sequence_comparator::similarity(std::shared_ptr<laban_sequence> element1, std::shared_ptr<laban_sequence> element2) const
            {
                return similarity(element1,element2, std::make_shared<laban_subsequence_mapper>(element1, element2));
            }

            double laban_sequence_comparator::similarity(std::shared_ptr<laban_sequence> element1, std::shared_ptr<laban_sequence> element2, std::shared_ptr<laban_subsequence_mapper> mapper) const
            {

                //similarities
                double similarities_sum = 0;
                std::size_t similarities_size = 0;;

                //punish unmappables
                similarities_size += mapper->get_unmappable_columns().size();

                for (std::pair<int,int> pair :  mapper->get_mapped_columns())
                {
                    int col1_id = pair.first;
                    int col2_id = pair.second;

                    //quantize symbol
                    std::vector<std::shared_ptr<i_movement> > movements1_steps = create_stretched(element1->get_column_movements(col1_id), element1->get_beats());
                    std::vector<std::shared_ptr<i_movement> > movements2_steps = create_stretched(element2->get_column_movements(col2_id), element2->get_beats());

                    //get distance using distance measure, distance = 0 if one sequence has no movements defined for the column and ignore flag is set (movement agnostic for that column)
                    double distance = 0;

                    if ((!movements1_steps.empty() && !movements2_steps.empty()) || !ignore_empty_columns_)
                    {
                        //TODO remove
                        uint64_t starttime = mos::current_time_millis();
                        distance = distance_measure_->distance(movements1_steps, movements2_steps);
                        uint64_t endtime = mos::current_time_millis();

                        //distance to similarity
                        double similarity = 0;

                        if (distance != std::numeric_limits<double>::infinity())
                        {
                            similarity = 1 / (1 + distance);
                        }

                        //TODO remove
                        std::cout << "similarity [" << col1_id << "," << col2_id << "] " << similarity << " for dist " << distance << " took " << (endtime-starttime) << " ms" << std::endl;

                        similarities_size++;
                        similarities_sum += similarity;
                    }


                }

                //average similarities
                return similarities_sum / (double) similarities_size;
            }


            std::vector<std::shared_ptr<i_movement> > laban_sequence_comparator::create_stretched(std::vector<std::shared_ptr<i_movement> > non_streched, unsigned int beats_per_measure) const
            {

                if (0 == frames_per_beat_)
                {
                    return non_streched;
                }

                std::vector<std::shared_ptr<i_movement> > result;

                double prev_end = 0;

                for (std::shared_ptr<i_movement> symbol : non_streched)
                {
                    // fill null for spaces without a symbol
                    double pos = symbol->get_measure() * beats_per_measure + symbol->get_beat();

                    int times_null = (int) (frames_per_beat_ * (pos - prev_end));

                    if (times_null > 0)
                    {
                        for (int i = 0; i < times_null; i++)
                        {
                            result.push_back(nullptr);
                        }
                    }

                    // fill symbol
                    int times = (int) (frames_per_beat_ * symbol->get_duration());

                    if (0 == symbol->get_beat() && 0 == symbol->get_measure() )
                    {
                        //start symbol only one frame
                        times = 1;
                    }

                    if (times < 1)
                    {
                        times = 1;
                    }

                    for (int i = 0; i < times; i++)
                    {
                        result.push_back(symbol);
                    }
                }

                return result;
            }


        } // namespace laban
    } // namespace fl
} // namespace mae
