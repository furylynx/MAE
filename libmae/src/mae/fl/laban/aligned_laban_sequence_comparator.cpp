//
// Created by furylynx on 2018-02-13
//

#include "aligned_laban_sequence_comparator.hpp"



namespace mae
{
    namespace fl
    {
        namespace laban
        {

            aligned_laban_sequence_comparator::aligned_laban_sequence_comparator(std::shared_ptr<mae::math::aligned_distance<std::shared_ptr<i_movement> > > distance_measure,  bool ignore_empty_columns, unsigned int frames_per_beat)
            {
                distance_measure_ = distance_measure;
                ignore_empty_columns_ = ignore_empty_columns;
                frames_per_beat_ = frames_per_beat;
            }

            aligned_laban_sequence_comparator::~aligned_laban_sequence_comparator()
            {

            }

            double aligned_laban_sequence_comparator::similarity(std::shared_ptr<laban_sequence> element1, std::shared_ptr<laban_sequence> element2) const
            {
                return similarity(element1,element2, std::make_shared<laban_subsequence_mapper>(element1, element2));
            }

            double aligned_laban_sequence_comparator::similarity(std::shared_ptr<laban_sequence> element1, std::shared_ptr<laban_sequence> element2, std::shared_ptr<laban_subsequence_mapper> mapper) const
            {

                //similarities
                double similarities_sum = 0;
                std::size_t similarities_size = 0;;

                //punish unmappables
                if (ignore_empty_columns_)
                {
                    for (std::pair<bool,std::shared_ptr<column_definition> > unmappable : mapper->get_unmappable_columns())
                    {
                        if (unmappable.first)
                        {
                            similarities_size ++;
                        }
                    }
                }
                else
                {
                    similarities_size += mapper->get_unmappable_columns().size();
                }

                std::vector<std::pair<std::vector<std::shared_ptr<i_movement> >, std::vector<std::shared_ptr<i_movement> > > > columns;

                //get sizes for the sequences
                double el1_max = element1->get_last_movement()->get_measure()*element1->get_beats() + element1->get_last_movement()->get_beat() + element1->get_last_movement()->get_duration();
                double el2_max = element2->get_last_movement()->get_measure()*element2->get_beats() + element2->get_last_movement()->get_beat() + element2->get_last_movement()->get_duration();

                for (std::pair<int,int> pair :  mapper->get_mapped_columns())
                {
                    int col1_id = pair.first;
                    int col2_id = pair.second;

                    //quantize symbol

                    //TODO all columns must have same size
                    std::vector<std::shared_ptr<i_movement> > movements1_steps = create_stretched(element1->get_column_movements(col1_id), element1->get_beats(), el1_max);
                    std::vector<std::shared_ptr<i_movement> > movements2_steps = create_stretched(element2->get_column_movements(col2_id), element2->get_beats(), el2_max);

                    if ((!movements1_steps.empty() && !movements2_steps.empty()) || !ignore_empty_columns_)
                    {
                        //add to comparison if both not empty or rule states not to ignore empty columns

                        columns.push_back(std::make_pair(movements1_steps, movements2_steps));
                    }
                }

                math::aligned_distances_details details = distance_measure_->distances_details(columns);


                for (double distance : details.get_distances())
                {
                    //distance to similarity
                    double similarity = 0;

                    if (distance != std::numeric_limits<double>::infinity())
                    {
                        similarity = 1 / (1 + distance);
                    }

                    //TODO remove
                    //std::cout << "similarity [" << col1_id << "," << col2_id << "] " << similarity << " for dist " << distance << " took " << (endtime-starttime) << " ms" << std::endl;

                    similarities_size++;
                    similarities_sum += similarity;
                }

                //average similarities
                return similarities_sum / (double) similarities_size;
            }


            std::vector<std::shared_ptr<i_movement> > aligned_laban_sequence_comparator::create_stretched(std::vector<std::shared_ptr<i_movement> > non_streched, unsigned int beats_per_measure, double max_sequence_size) const
            {

                if (0 == frames_per_beat_)
                {
                    return non_streched;
                }

                std::size_t result_size = std::static_cast<std::size_t>(std::floor(max_sequence_size*frames_per_beat_));

                std::vector<std::shared_ptr<i_movement> > result;
                result.assign (result_size, nullptr);

                for (std::shared_ptr<i_movement> symbol : non_streched)
                {
                    //TODO insert into result vector

                    if (0 == symbol->get_beat() && 0 == symbol->get_measure() )
                    {
                        //TODO start symbol only one frame
                    }
                    else
                    {
                        double start = symbol->get_measure() * beats_per_measure + symbol->get_beat();
                        double end = start + symbol->get_duration();

                        std::size_t start_p = std::static_cast<std::size_t>(std::floor(start*frames_per_beat_));
                        std::size_t end_p = std::static_cast<std::size_t>(std::floor(end*frames_per_beat_));


                        for (std::size_t i = start_p; i <= end_p; i++)
                        {
                            result.at(i) = symbol;
                        }
                    }
                }

//                double prev_end = 0;
//
//                for (std::shared_ptr<i_movement> symbol : non_streched)
//                {
//                    // fill null for spaces without a symbol
//                    double pos = symbol->get_measure() * beats_per_measure + symbol->get_beat();
//
//                    int times_null = (int) (frames_per_beat_ * (pos - prev_end));
//
//                    if (times_null > 0)
//                    {
//                        for (int i = 0; i < times_null; i++)
//                        {
//                            result.push_back(nullptr);
//                        }
//                    }
//
//                    // fill symbol
//                    int times = (int) (frames_per_beat_ * symbol->get_duration());
//
//                    if (0 == symbol->get_beat() && 0 == symbol->get_measure() )
//                    {
//                        //start symbol only one frame
//                        times = 1;
//                    }
//
//                    if (times < 1)
//                    {
//                        times = 1;
//                    }
//
//                    for (int i = 0; i < times; i++)
//                    {
//                        result.push_back(symbol);
//                    }
//                }

                return result;
            }


        } // namespace laban
    } // namespace fl
} // namespace mae
