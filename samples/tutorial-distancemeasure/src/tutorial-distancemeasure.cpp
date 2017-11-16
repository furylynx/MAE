
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

        std::shared_ptr<mae::fl::laban::laban_sequence> sequence1 = lreader.read_sequence_file("ah_clap1.bvh.laban");
        std::shared_ptr<mae::fl::laban::laban_sequence> sequence2 = lreader.read_sequence_file("de_wave8.bvh.laban");

        std::shared_ptr<mae::fl::laban::laban_sequence> target_sequence = lreader.read_sequence_file("clap.laban");

        if (nullptr != sequence2 && nullptr != sequence1 && nullptr != target_sequence)
        {

            //set the p for minkowski distance (p=1 is manhattan distance, p=2 is euclidean distance)
            int minkowski_p = 1;
            std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure_feature_vectors = std::make_shared<mae::math::minkowski_distance>(minkowski_p);//std::make_shared<mae::math::mahalanobis_distance>();//


            //use the movement comparator to compare movements (labanotation symbols)
            std::shared_ptr<mae::fl::laban::movement_comparator> movement_comparator = std::make_shared<mae::fl::laban::movement_comparator>(distance_measure_feature_vectors);

            //set the window size, zero for no windowing
            std::size_t window = 0;
            std::shared_ptr<mae::math::i_distance_measure<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > > distance_measure = std::make_shared<mae::math::lcs_distance<std::shared_ptr<mae::fl::laban::i_movement> > >(movement_comparator);
            // = std::make_shared<mae::math::dtw<std::shared_ptr<mae::fl::laban::i_movement> > >(movement_comparator, window);
            // = std::make_shared<mae::math::lcs_distance<std::shared_ptr<mae::fl::laban::i_movement> > >(movement_comparator);
            // = std::make_shared<mae::math::discrete_frechet_distance<std::shared_ptr<mae::fl::laban::i_movement> > >(movement_comparator);

            bool ignore_empty_columns = true;
            unsigned int frames_per_beat = 0;
            std::shared_ptr<mae::fl::laban::laban_sequence_comparator> comparator = std::make_shared<mae::fl::laban::laban_sequence_comparator>(distance_measure, ignore_empty_columns, frames_per_beat);

            double cut_steps = 2;
            double min_sequence_length_factor = 0.1;
            double max_sequence_length_factor = 2;
            mae::fl::laban::laban_target_sequence_comparator target_comparator (comparator, false, cut_steps, min_sequence_length_factor, max_sequence_length_factor);

            uint64_t starttime = mae::mos::current_time_millis();

            double similarity = target_comparator.similarity(target_sequence, sequence2);//comparator->similarity(target_sequence, sequence1);//

            uint64_t endtime = mae::mos::current_time_millis();

            std::cout << "Similarity: " << similarity << std::endl;
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
