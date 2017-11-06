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

            laban_target_sequence_comparator::laban_target_sequence_comparator(std::shared_ptr<laban_sequence_comparator> laban_sequence_comparator, bool fixed_end, unsigned int frames_per_beat)
            {
                laban_sequence_comparator_ = laban_sequence_comparator;
                fixed_end_ = fixed_end;
                frames_per_beat_ = frames_per_beat;
            }

            laban_target_sequence_comparator::~laban_target_sequence_comparator()
            {

            }

            double laban_target_sequence_comparator::similarity(std::shared_ptr<laban_sequence> target_sequence, std::shared_ptr<laban_sequence> actual_sequence) const
            {
                std::shared_ptr<laban_subsequence_mapper> mapper = std::make_shared<laban_subsequence_mapper>(target_sequence, actual_sequence);

                unsigned int length = actual_sequence->get_beats() * actual_sequence->get_measures();
                unsigned int sliced_length = length * frames_per_beat_;

                double max_similarity = 0;

                //vary in start and end position
                for (int startpos = 0; startpos < sliced_length; startpos++)
                {
                    double startpos_beats = startpos / (double)frames_per_beat_;

                    if (!fixed_end_)
                    {
                        //when no fixed end is defined, iterate end position too to find optimal subsequence
                        for (int endpos = startpos+1; endpos < sliced_length; endpos++)
                        {
                            double endpos_beats = endpos / (double)frames_per_beat_;

                            double similarity = laban_sequence_comparator_->similarity(target_sequence, cut_sequence(actual_sequence, startpos_beats, endpos_beats), mapper);

                            if (similarity > max_similarity)
                            {
                                max_similarity = similarity;
                            }
                        }
                    }
                    else
                    {
                        //fixed end is defined, only start position will be iterated

                        double similarity = laban_sequence_comparator_->similarity(target_sequence, cut_sequence(actual_sequence, startpos_beats, length), mapper);

                        if (similarity > max_similarity)
                        {
                            max_similarity = similarity;
                        }
                    }
                }

                return max_similarity;
            }

            std::shared_ptr<laban_sequence> cut_sequence(std::shared_ptr<laban_sequence> sequence, double startpos, double endpos) const
            {
                std::shared_ptr<laban_sequence> result = std::make_shared<laban_sequence>(sequence->get_title(), "anonymous", sequence->get_measures(), sequence->get_time_unit(), sequence->get_beat_duration(), sequence->get_beats());

                result->set_authors(sequence->get_authors());
                result->set_column_definitions(sequence->get_column_definitions());
                result->set_description(sequence->get_description());

                //set movements
                unsigned int beats_per_measure = sequence->get_beats();

                for (int col_id : sequence->get_columns())
                {
                    bool startpose = false;

                    std::vector<std::shared_ptr<i_movement> > colmovs;

                    for (std::shared_ptr<i_movement> i_mov : sequence->get_column_movements(col_id))
                    {
                        double curpos = i_mov->get_measure()*beats_per_measure + i_mov->get_beat();
                        double curdur = i_mov->get_duration();

                        double cutpos = curpos - startpos;
                        double cutdur = curdur;

                        if (cutpos < beats_per_measure)
                        {
                            if (curdur + cutpos >= 0)
                            {
                                if (startpose)
                                {
                                    //already a startpose defined, but we have another now. hence, clear the buffer
                                    colmovs.clear();
                                }

                                //create start pose
                                colmovs.push_back(i_mov->recreate(std::map<int, int>(), 0, 0, 1));
                                startpose = true;
                            }
                            else
                            {
                                //movement is out of scope, don't add
                            }
                        }
                        else if (cutpos > endpos)
                        {
                            //don't add, break since following elements will be out of range too
                            break;
                        }
                        else
                        {
                            if (cutpos + cutdur > endpos)
                            {
                                //cut duration
                                cutdur = endpos - cutpos;
                            }

                            unsigned int measure = (int)(cutpos / beats_per_measure);
                            double beat = cutpos - (measure * beats_per_measure);
                            double duration = cutdur;

                            colmovs.push_back(i_mov->recreate(std::map<int, int>(), measure, beat, duration));
                        }
                    }

                    for (std::shared_ptr<i_movement> i_mov : colmovs)
                    {
                        result->add_movement(i_mov);
                    }
                }

                return result;
            }



        } // namespace laban
    } // namespace fl
} // namespace mae
