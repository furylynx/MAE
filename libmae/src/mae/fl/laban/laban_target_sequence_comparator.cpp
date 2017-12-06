//
// Created on 06.11.17.
//

#include "laban_target_sequence_comparator.hpp"

namespace mae
{
    namespace fl
    {
        namespace laban
        {

            laban_target_sequence_comparator::laban_target_sequence_comparator(std::shared_ptr<laban_sequence_comparator> laban_sequence_comparator, bool fixed_end, double cut_steps, double min_length_factor, double max_length_factor)
            {
                laban_sequence_comparator_ = laban_sequence_comparator;
                fixed_end_ = fixed_end;
                cut_steps_ = cut_steps;
                min_length_factor_ = min_length_factor;
                max_length_factor_ = max_length_factor;
            }

            laban_target_sequence_comparator::~laban_target_sequence_comparator()
            {

            }

            double laban_target_sequence_comparator::similarity(std::shared_ptr<laban_sequence> target_sequence, std::shared_ptr<laban_sequence> actual_sequence) const
            {
                return similarity_details(target_sequence, actual_sequence).get_similarity();
            }

            mae::math::subsequence_similarity_details laban_target_sequence_comparator::similarity_details(std::shared_ptr<laban_sequence> target_sequence, std::shared_ptr<laban_sequence> actual_sequence) const
            {
                std::shared_ptr<laban_subsequence_mapper> mapper = std::make_shared<laban_subsequence_mapper>(target_sequence, actual_sequence);

                double cut_steps = cut_steps_;

                if (0 == cut_steps)
                {
                    cut_steps = 1;
                }

                unsigned int actual_sequence_length = actual_sequence->get_beats() * (actual_sequence->get_measures() + 1);
                double actual_sequence_sliced_length = actual_sequence_length / cut_steps;

                unsigned int target_sequence_length = target_sequence->get_beats() * (target_sequence->get_measures() + 1);
                double target_sequence_sliced_length = target_sequence_length / cut_steps;

                //define min length to limit comparison
                std::size_t min_length = 1;
                std::size_t max_length = std::max(target_sequence_sliced_length,actual_sequence_sliced_length);

                if (min_length_factor_ > 0)
                {
                    min_length = min_length_factor_ * target_sequence_sliced_length;
                }

                if (max_length_factor_ > 0)
                {
                    max_length = max_length_factor_ * target_sequence_sliced_length;
                }

                double max_similarity = 0;
                double max_similarity_startpos = 0;
                double max_similarity_endpos = 0;

                if (min_length >= actual_sequence_sliced_length)
                {
                    max_similarity = laban_sequence_comparator_->similarity(target_sequence, actual_sequence, mapper);
                }
                else
                {
                    if (!fixed_end_)
                    {
                        //vary in start and end position
                        for (std::size_t startpos = 0; startpos < actual_sequence_sliced_length; startpos++)
                        {
                            double startpos_beats = startpos * cut_steps;

                            //when no fixed end is defined, iterate end position too to find optimal subsequence
                            for (std::size_t  endpos = startpos + min_length; endpos <= actual_sequence_sliced_length && endpos - startpos <= max_length; endpos++)
                            {
                                double endpos_beats = endpos * cut_steps;

                                double similarity = laban_sequence_comparator_->similarity(target_sequence, cut_sequence(actual_sequence, startpos_beats, endpos_beats), mapper);

                                if (similarity > max_similarity)
                                {
                                    max_similarity = similarity;
                                    max_similarity_startpos = startpos_beats;
                                    max_similarity_endpos = endpos_beats;
                                }
                            }
                        }
                    }
                    else
                    {
                        //fixed end is defined, only start position will be iterated

                        //vary in start and end position
                        std::size_t startpos = 0;

                        if (actual_sequence_sliced_length - max_length > 0)
                        {
                            startpos = actual_sequence_sliced_length - max_length;
                        }

                        for (; startpos < actual_sequence_sliced_length - min_length + 1; startpos++)
                        {
                            double startpos_beats = startpos * cut_steps;

                            double similarity = laban_sequence_comparator_->similarity(target_sequence, cut_sequence(actual_sequence, startpos_beats, actual_sequence_length), mapper);

                            if (similarity > max_similarity)
                            {
                                max_similarity = similarity;
                                max_similarity_startpos = startpos_beats;
                                max_similarity_endpos = actual_sequence_length;
                            }
                        }
                    }
                }

                return mae::math::subsequence_similarity_details(max_similarity_startpos, max_similarity_endpos, max_similarity);
            }

            std::shared_ptr<laban_sequence> laban_target_sequence_comparator::cut_sequence(std::shared_ptr<laban_sequence> sequence, double startpos, double endpos) const
            {
                std::shared_ptr<laban_sequence> result = std::make_shared<laban_sequence>(sequence->get_title(), "anonymous", sequence->get_measures(), sequence->get_time_unit(), sequence->get_beat_duration(), sequence->get_beats());

                result->set_authors(sequence->get_authors());
                result->set_column_definitions(sequence->get_column_definitions());
                result->set_description(sequence->get_description());

                //set movements
                unsigned int beats_per_measure = sequence->get_beats();

                for (int column_id : sequence->get_columns())
                {
                    bool startpose = false;

                    std::vector<std::shared_ptr<i_movement> > cut_column_movements;

                    for (std::shared_ptr<i_movement> i_mov : sequence->get_column_movements(column_id))
                    {
                        //column movements are ordered ascendingly in time

                        double current_position = i_mov->get_measure()*beats_per_measure + i_mov->get_beat();
                        double current_duration = i_mov->get_duration();

                        double cut_position = current_position - startpos;
                        double cut_duration = current_duration;

                        if (cut_position < beats_per_measure)
                        {
//                            if (current_duration + cut_position >= 0)
//                            {
                                if (startpose)
                                {
                                    //already a startpose defined, but we have another now. hence, clear the buffer
                                    cut_column_movements.clear();
                                }

                                //create start pose
                                cut_column_movements.push_back(i_mov->recreate(std::map<int, int>(), 0, 0, 1));

                                //set flag for a startpose
                                startpose = true;
//                            }
//                            else
//                            {
//                                //movement is out of scope, don't add
//                            }
                        }
                        else if (cut_position > endpos)
                        {
                            //don't add
                            //break since following elements will be out of range too
                            break;
                        }
                        else
                        {
                            if (cut_position + cut_duration > endpos)
                            {
                                //cut duration
                                cut_duration = endpos - cut_position;
                            }

                            unsigned int measure = (unsigned int)(cut_position / beats_per_measure);
                            double beat = cut_position - (measure * beats_per_measure);
                            double duration = cut_duration;

                            cut_column_movements.push_back(i_mov->recreate(std::map<int, int>(), measure, beat, duration));
                        }
                    }

                    //add newly created movements
                    for (std::shared_ptr<i_movement> i_mov : cut_column_movements)
                    {
                        result->add_movement(i_mov);
                    }
                }

                return result;
            }



        } // namespace laban
    } // namespace fl
} // namespace mae
