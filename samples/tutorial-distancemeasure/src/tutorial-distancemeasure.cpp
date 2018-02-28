
//custom includes
//...

//global includes
#include <iostream>

#include <mae/mae.hpp>


int main()
{
    try
    {
        // print message - program started
        std::cout << "tutorial - distance measure " << std::endl;

        mae::fl::laban::laban_sequence_reader lreader;

        //sequences
        std::shared_ptr<mae::fl::laban::laban_sequence> sequence1 = lreader.read_sequence_file("../../evaluation/mae_evaluator/check/de_dontcare7.bvh.laban");
        std::shared_ptr<mae::fl::laban::laban_sequence> sequence2 = lreader.read_sequence_file("../../evaluation/mae_evaluator/check/ah_clap7.bvh.laban");
        std::shared_ptr<mae::fl::laban::laban_sequence> sequence3 = lreader.read_sequence_file("../../evaluation/mae_evaluator/check/to_clap3.bvh.laban");
        std::shared_ptr<mae::fl::laban::laban_sequence> sequence4 = lreader.read_sequence_file("../../evaluation/mae_evaluator/check/ang_dontcare5.bvh.laban");

        std::shared_ptr<mae::fl::laban::laban_sequence> possible_target_sequence1 = lreader.read_sequence_file("../../evaluation/mae_evaluator/evaluation_bvhs/dontcare/dontcare.laban");
        std::shared_ptr<mae::fl::laban::laban_sequence> possible_target_sequence2 = lreader.read_sequence_file("../../evaluation/mae_evaluator/evaluation_bvhs/clap/clap.laban");
        std::shared_ptr<mae::fl::laban::laban_sequence> possible_target_sequence3 = lreader.read_sequence_file("../../evaluation/mae_evaluator/evaluation_bvhs/throw/throw2.laban");
        std::shared_ptr<mae::fl::laban::laban_sequence> possible_target_sequence4 = lreader.read_sequence_file("../../evaluation/mae_evaluator/evaluation_bvhs/hammer/hammer.laban");

        //change here for different comparison
        std::shared_ptr<mae::fl::laban::laban_sequence> target_sequence = possible_target_sequence1;
        std::shared_ptr<mae::fl::laban::laban_sequence> real_sequence = sequence4;

        if (nullptr != real_sequence && nullptr != target_sequence)
        {
            //set the p for minkowski distance (p=1 is manhattan distance, p=2 is euclidean distance)
            int minkowski_p = 1;
            std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure_feature_vectors = std::make_shared<mae::math::minkowski_distance>(minkowski_p);//std::make_shared<mae::math::mahalanobis_distance>();//

            //hierarchy distance
            double distance_offset = 2;
            std::shared_ptr<mae::math::i_type_distance_measure> type_distance_measure = std::make_shared<mae::math::sologub_tree_type_distance>(distance_offset);
            // = std::make_shared<mae::math::sologub_tree_type_distance>(distance_offset);
            // = std::make_shared<mae::math::direct_tree_type_distance>(distance_offset);

            //use the movement comparator to compare movements (labanotation symbols)
            double distance_for_nullptr_ = 2;
            std::shared_ptr<mae::fl::laban::movement_comparator> movement_comparator = std::make_shared<mae::fl::laban::movement_comparator>(distance_measure_feature_vectors, type_distance_measure, distance_for_nullptr_);

            //set the window size, zero for no windowing
            std::size_t window = 0;
            double edr_epsilon = 0.5;
            std::shared_ptr<mae::math::i_distance_measure<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > > distance_measure = std::make_shared<mae::math::dtw<std::shared_ptr<mae::fl::laban::i_movement> > >(movement_comparator, window, false);
            // = std::make_shared<mae::math::dtw<std::shared_ptr<mae::fl::laban::i_movement> > >(movement_comparator, window);
            // = std::make_shared<mae::math::lcs_distance<std::shared_ptr<mae::fl::laban::i_movement> > >(movement_comparator);
            // = std::make_shared<mae::math::discrete_frechet_distance<std::shared_ptr<mae::fl::laban::i_movement> > >(movement_comparator);
            //= std::make_shared<mae::math::edr<std::shared_ptr<mae::fl::laban::i_movement> > >(movement_comparator, edr_epsilon);
            //= std::make_shared<mae::math::erp<std::shared_ptr<mae::fl::laban::i_movement> > >(movement_comparator, nullptr);

            bool ignore_empty_columns = true;
            unsigned int frames_per_beat = 6;
            std::shared_ptr<mae::fl::laban::laban_sequence_comparator> comparator = std::make_shared<mae::fl::laban::laban_sequence_comparator>(distance_measure, ignore_empty_columns, frames_per_beat);

            double cut_steps = 1;
            double min_sequence_length_factor = 0.1;//0.1;
            double max_sequence_length_factor = 2;//2;
            mae::fl::laban::laban_target_sequence_comparator target_comparator (comparator, false, cut_steps, min_sequence_length_factor, max_sequence_length_factor);

            uint64_t starttime = mae::mos::current_time_millis();

            //double similarity = comparator->similarity(target_sequence, sequence1);//

            //mae::math::aligned_similarity_details similarity_details = target_comparator.similarity_details(target_sequence, real_sequence);

            uint64_t endtime = mae::mos::current_time_millis();

//            std::cout << "Similarity: " << similarity_details.get_similarity() << std::endl;
//            std::cout << "Startpos: " << similarity_details.get_startpos() << std::endl;
//            std::cout << "Endpos: " << similarity_details.get_endpos() << std::endl;
            std::cout << "Calculation took " << endtime - starttime << " ms" << std::endl;


            //aligned distance
            double blur_strategy_beats = 0;
            std::shared_ptr<mae::math::i_warping_distance_measure<std::shared_ptr<mae::fl::laban::i_movement> > > warping_distance_measure = std::make_shared<mae::math::dtw<std::shared_ptr<mae::fl::laban::i_movement> > >(movement_comparator, window, true);
            // = std::make_shared<mae::math::dtw<std::shared_ptr<mae::fl::laban::i_movement> > >(movement_comparator, window, true);
            // = std::make_shared<mae::math::discrete_frechet_distance<std::shared_ptr<mae::fl::laban::i_movement> > >(movement_comparator, true);
            // = std::make_shared<mae::math::edr<std::shared_ptr<mae::fl::laban::i_movement> > >(movement_comparator, edr_epsilon, true);
            // = std::make_shared<mae::math::erp<std::shared_ptr<mae::fl::laban::i_movement> > >(movement_comparator, nullptr, true);
            mae::fl::laban::aligned_laban_sequence_comparator aligned_comparator = mae::fl::laban::aligned_laban_sequence_comparator(std::make_shared<mae::math::aligned_distance<std::shared_ptr<mae::fl::laban::i_movement> > >(warping_distance_measure), ignore_empty_columns, frames_per_beat, blur_strategy_beats);

            starttime = mae::mos::current_time_millis();

            mae::math::aligned_similarity_details aligned_similarity = aligned_comparator.similarity_details(target_sequence, real_sequence);

            endtime = mae::mos::current_time_millis();

            std::cout << "Similarity: " << aligned_similarity.get_similarity() << std::endl;
            std::cout << "Startpos: " << aligned_similarity.get_startpos() << std::endl;
            std::cout << "Endpos: " << aligned_similarity.get_endpos() << std::endl;
            std::cout << "Calculation took " << endtime - starttime << " ms" << std::endl;

        }
        else
        {
            std::cerr << "Could not find one of the given files." << std::endl;
        }



    }
    catch (std::exception &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    catch(...)
    {
        std::cout << "Unknown exception occurred." << std::endl;
    }

	return 0;
}
