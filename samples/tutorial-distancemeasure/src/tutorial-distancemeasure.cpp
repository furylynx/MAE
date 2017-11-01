
//custom includes
#include "int_distance_measure.hpp"

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
        std::shared_ptr<mae::fl::laban::laban_sequence> sequence2 = lreader.read_sequence_file("clap.laban");

        if (nullptr != sequence1 && nullptr != sequence2)
        {

            //set the p for minkowski distance (p=1 is manhattan distance, p=2 is euclidean distance)
            int minkowski_p = 1;
            std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure_feature_vectors = std::make_shared<mae::math::minkowski_distance>(minkowski_p);

            //use the movement comparator to compare movements (labanotation symbols)
            std::shared_ptr<mae::fl::laban::movement_comparator> movement_comparator = std::make_shared<mae::fl::laban::movement_comparator>(distance_measure_feature_vectors);

            //set the window size, zero for no windowing
            std::size_t window = 0;
            std::shared_ptr<mae::math::i_distance_measure<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > > distance_measure = std::make_shared<mae::math::dtw<std::shared_ptr<mae::fl::laban::i_movement> > >(movement_comparator, window);

            bool ignore_empty_columns = false;
            unsigned int frames_per_beat = 6;
            mae::fl::laban::laban_sequence_comparator comparator (distance_measure, ignore_empty_columns, frames_per_beat);

            std::cout << "ff" << std::endl;

            double similarity = comparator.similarity(sequence1, sequence2);

            std::cout << "Similarity: " << similarity << std::endl;
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
