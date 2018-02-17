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

            aligned_laban_sequence_comparator::aligned_laban_sequence_comparator(std::shared_ptr<mae::math::aligned_distance<std::shared_ptr<i_movement> > > distance_measure,  bool ignore_empty_columns, unsigned int frames_per_beat, double blur_strategy_beats)
            {
                distance_measure_ = distance_measure;
                ignore_empty_columns_ = ignore_empty_columns;
                frames_per_beat_ = frames_per_beat;
                blur_strategy_beats_ = blur_strategy_beats;
            }

            aligned_laban_sequence_comparator::~aligned_laban_sequence_comparator()
            {

            }

            double aligned_laban_sequence_comparator::similarity(std::shared_ptr<laban_sequence> element1, std::shared_ptr<laban_sequence> element2) const
            {
                return similarity_details(element1,element2, std::make_shared<laban_subsequence_mapper>(element1, element2)).get_similarity();
            }

            mae::math::aligned_similarity_details aligned_laban_sequence_comparator::similarity_details(std::shared_ptr<laban_sequence> element1, std::shared_ptr<laban_sequence> element2) const
            {
                return similarity_details(element1,element2, std::make_shared<laban_subsequence_mapper>(element1, element2));
            }

            mae::math::aligned_similarity_details aligned_laban_sequence_comparator::similarity_details(std::shared_ptr<laban_sequence> element1, std::shared_ptr<laban_sequence> element2, std::shared_ptr<laban_subsequence_mapper> mapper) const
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
                std::shared_ptr<i_movement> el1_lm = element1->get_last_movement();
                std::shared_ptr<i_movement> el2_lm = element2->get_last_movement();

                double el1_max = 1;
                if (0 != el1_lm->get_measure())
                {
                    el1_max = (el1_lm->get_measure()-1)*element1->get_beats() + el1_lm->get_beat() + el1_lm->get_duration() + 1;
                }

                double el2_max = 1;
                if (0 != el2_lm->get_measure())
                {
                    el2_max = (el2_lm->get_measure()-1)*element2->get_beats() + el2_lm->get_beat() + el2_lm->get_duration() + 1;
                }

                for (std::pair<int,int> pair :  mapper->get_mapped_columns())
                {
                    int col1_id = pair.first;
                    int col2_id = pair.second;

                    if ((!element1->get_column_movements(col1_id).empty()) || !ignore_empty_columns_)
                    {
                        //target sequence has no movements for that column or rule states not to ignore empty columns

                        //quantize symbols
                        std::vector<std::shared_ptr<i_movement> > movements1_steps = create_stretched(element1->get_column_movements(col1_id), element1->get_beats(), el1_max);
                        std::vector<std::shared_ptr<i_movement> > movements2_steps = create_stretched(element2->get_column_movements(col2_id), element2->get_beats(), el2_max);

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

                    similarities_size++;
                    similarities_sum += similarity;
                }

                //average similarities
                return mae::math::aligned_similarity_details(details.get_startpos(), details.get_endpos(), similarities_sum / (double) similarities_size);
            }


            std::vector<std::shared_ptr<i_movement> > aligned_laban_sequence_comparator::create_stretched(std::vector<std::shared_ptr<i_movement> > non_streched, unsigned int beats_per_measure, double max_sequence_size) const
            {
                if (0 == frames_per_beat_)
                {
                    return non_streched;
                }

                std::size_t result_size = std::floor(max_sequence_size*frames_per_beat_);

                std::vector<std::shared_ptr<i_movement> > result;
                result.assign (result_size, nullptr);

                //blur for the given number of beats if activated
                bool blur_symbol = blur_strategy_beats_ > 0;
                std::size_t blur_symbol_gap = blur_strategy_beats_*frames_per_beat_;

                for (std::shared_ptr<i_movement> symbol : non_streched)
                {
                    if (0 == symbol->get_measure() )
                    {
                        result.at(0) = symbol;
                    }
                    else
                    {
                        double start = (symbol->get_measure()-1) * beats_per_measure + symbol->get_beat()+1;
                        double end = start + symbol->get_duration();

                        std::size_t start_p = std::floor(start*frames_per_beat_);
                        std::size_t end_p = std::floor(end*frames_per_beat_);

                        for (std::size_t i = start_p; i < end_p; i++)
                        {
                            result.at(i) = symbol;
                        }

                        //blur symbol (close gap to next symbol if below threshold)
                        if (blur_symbol)
                        {
                            bool successor_found = false;
                            for (std::size_t i = 0; i < blur_symbol_gap && end_p + i < result_size; i++)
                            {
                                if (nullptr != result.at(i+end_p))
                                {
                                    successor_found = true;
                                }
                            }

                            if (successor_found)
                            {
                                for (std::size_t i = 0; i < blur_symbol_gap && end_p + i < result_size; i++)
                                {
                                    if (nullptr == result.at(i + end_p))
                                    {
                                        result.at(i + end_p) = symbol;
                                    }
                                }
                            }
                        }
                    }
                }

                result.push_back(nullptr);

                //hold strategy (blur with inifinite amount of beats)
                bool hold_symbol = (0 == blur_strategy_beats_);
                if (hold_symbol)
                {
                    //holds the last symbol until another arrives. starts with nullptr (no symbol) until first is found

                    std::shared_ptr<i_movement> prev_mov = nullptr;
                    for (std::size_t i = 0; i < result.size();i++)
                    {
                        if (nullptr == result.at(i))
                        {
                            result.at(i) = prev_mov;
                        }
                        else
                        {
                            prev_mov = result.at(i);
                        }
                    }
                }

                //TODO remove
//                std::cout << std::endl;
//                std::cout << "BEGIN SEQUENCE" << std::endl;
//                for (std::size_t i = 0; i < result.size(); i++)
//                {
//                    if (nullptr == result.at(i))
//                    {
//                        std::cout << "null" << std::endl;
//                    }
//                    else
//                    {
//                        std::cout << result.at(i)->str() << std::endl;
//                    }
//                }
//                std::cout << "END SEQUENCE" << std::endl;
//                std::cout << std::endl;

                return result;
            }


        } // namespace laban
    } // namespace fl
} // namespace mae
