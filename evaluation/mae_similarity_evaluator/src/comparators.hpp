//
// Created on 2017-12-01
//

#ifndef MAE_SIMILARITY_EVALUATOR_COMPARATORS_HPP
#define MAE_SIMILARITY_EVALUATOR_COMPARATORS_HPP

//custom includes
#include "convenience.hpp"

//global includes
//...


struct feature_vector_distance_measure { std::string name; std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure; };

feature_vector_distance_measure initialize_feature_vector_distance_measure(std::string name, std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > distance_measure)
{
feature_vector_distance_measure result;
result.name=name;
result.distance_measure = distance_measure;
return result;
}

struct type_distance_measure { std::string name; std::shared_ptr<mae::math::i_type_distance_measure> distance_measure; };

type_distance_measure initialize_type_distance_measure(std::string name, std::shared_ptr<mae::math::i_type_distance_measure> distance_measure)
{
    type_distance_measure result;
    result.name=name;
    result.distance_measure = distance_measure;
    return result;
}

struct movement_comparator_info { std::string name; std::shared_ptr<mae::fl::laban::movement_comparator> comparator; };

movement_comparator_info initialize_movement_comparator_info(std::string name, std::shared_ptr<mae::fl::laban::movement_comparator> comparator)
{
    movement_comparator_info result;
    result.name=name;
    result.comparator = comparator;
    return result;
}

struct symbol_sequence_comparator_info { std::string name; std::shared_ptr<mae::math::i_distance_measure<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > > comparator; };

symbol_sequence_comparator_info initialize_symbol_sequence_comparator_info(std::string name, std::shared_ptr<mae::math::i_distance_measure<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > > comparator)
{
symbol_sequence_comparator_info result;
result.name=name;
result.comparator = comparator;
return result;
}

struct symbol_warping_comparator_info { std::string name; std::shared_ptr<mae::math::i_warping_distance_measure<std::shared_ptr<mae::fl::laban::i_movement> > > comparator; };

symbol_warping_comparator_info initialize_symbol_warping_comparator_info(std::string name, std::shared_ptr<mae::math::i_warping_distance_measure<std::shared_ptr<mae::fl::laban::i_movement> > > comparator)
{
symbol_warping_comparator_info result;
result.name=name;
result.comparator = comparator;
return result;
}

std::vector<comparator_info> initialize_comparators()
{
    std::vector<comparator_info> result;

    //general settings
    bool ignore_empty_columns = true;
    unsigned int frames_per_beat = 6;
    double cut_steps = 2;
    double min_sequence_length_factor = 0.1;
    double max_sequence_length_factor = 3;

    //feature vector distance measures
    std::vector<feature_vector_distance_measure> feature_vector_measures;
//    feature_vector_measures.push_back(initialize_feature_vector_distance_measure("manhattan", std::make_shared<mae::math::minkowski_distance>(1)));
    feature_vector_measures.push_back(initialize_feature_vector_distance_measure("euclidean", std::make_shared<mae::math::minkowski_distance>(2)));
//    feature_vector_measures.push_back(initialize_feature_vector_distance_measure("mahalanobis", std::make_shared<mae::math::mahalanobis_distance>()));
//    feature_vector_measures.push_back(initialize_feature_vector_distance_measure("cosine", std::make_shared<mae::math::cosine_distance>()));

    //hierarchy distance
    std::vector<type_distance_measure> type_measures;
//    type_measures.push_back(initialize_type_distance_measure("sologub", std::make_shared<mae::math::sologub_tree_type_distance>(2)));
    type_measures.push_back(initialize_type_distance_measure("direct", std::make_shared<mae::math::direct_tree_type_distance>(1)));


    for (feature_vector_distance_measure fvdm : feature_vector_measures)
    {
        for (type_distance_measure tdm : type_measures)
        {
            //movement comparators
            std::vector<movement_comparator_info> mcs;
            mcs.push_back(initialize_movement_comparator_info("movementcomparator-null", std::make_shared<mae::fl::laban::movement_comparator>(fvdm.distance_measure, tdm.distance_measure, -1)));
            //mcs.push_back(initialize_movement_comparator_info("movementcomparator-dist2", std::make_shared<mae::fl::laban::movement_comparator>(fvdm.distance_measure, tdm.distance_measure, 2)));

            for (movement_comparator_info mci : mcs)
            {
                std::vector<symbol_warping_comparator_info> sscs;
                sscs.push_back(initialize_symbol_warping_comparator_info("dtw-nwin", std::make_shared<mae::math::dtw<std::shared_ptr<mae::fl::laban::i_movement> > >(mci.comparator,0,true)));

                for (std::size_t win = 2; win <= 6; win+=2)
                {
                    //6 frames per beat, 5 beats per measure -> 30 frames per measure

                    std::stringstream sstr;
                    sstr << "dtw-win" << win;
                    sscs.push_back(initialize_symbol_warping_comparator_info(sstr.str(), std::make_shared<mae::math::dtw<std::shared_ptr<mae::fl::laban::i_movement> > >(mci.comparator, win, true)));
                }

                sscs.push_back(initialize_symbol_warping_comparator_info("lcs", std::make_shared<mae::math::lcs_distance<std::shared_ptr<mae::fl::laban::i_movement> > >(mci.comparator, true, true)));
                sscs.push_back(initialize_symbol_warping_comparator_info("discretefrechet", std::make_shared<mae::math::discrete_frechet_distance<std::shared_ptr<mae::fl::laban::i_movement> > >(mci.comparator, true)));
                sscs.push_back(initialize_symbol_sequence_comparator_info("edr-eps0.5", std::make_shared<mae::math::edr<std::shared_ptr<mae::fl::laban::i_movement> > >(mci.comparator, 0.5)));

//                for (double eps = 0.2; eps <= 1.2; eps+=0.4)
//                {
//                    std::stringstream sstr;
//                    sstr << "edr-eps" << eps;
//                    sscs.push_back(initialize_symbol_sequence_comparator_info(sstr.str(), std::make_shared<mae::math::edr<std::shared_ptr<mae::fl::laban::i_movement> > >(mci.comparator, eps)));
//                }

                sscs.push_back(initialize_symbol_sequence_comparator_info("erp-gapnull", std::make_shared<mae::math::erp<std::shared_ptr<mae::fl::laban::i_movement> > >(mci.comparator, nullptr)));

                for (symbol_warping_comparator_info ssci : sscs)
                {
                    std::stringstream sstr;
                    sstr << "al-hold-" << ssci.name << "_" << mci.name << "_" << tdm.name << "_" << fvdm.name;

                    //hold strategy
                    double blur_strategy_beats = 0;

                    result.push_back(initialize_comparator_info(-1, sstr.str(), "", std::make_shared<mae::fl::laban::aligned_laban_sequence_comparator>(std::make_shared<mae::math::aligned_distance<std::shared_ptr<mae::fl::laban::i_movement> > >(ssci.comparator), ignore_empty_columns, frames_per_beat, blur_strategy_beats)));
                }
            }
        }
    }

    return result;
}

std::vector<comparator_info> map_comparator_ids(std::vector<comparator_info> comparators, std::unordered_map<std::string, int> comparator_id_map)
{
    for (comparator_info& cinfo : comparators)
    {
        cinfo.id=comparator_id_map.at(cinfo.name);
    }

    return comparators;
}



#endif //MAE_SIMILARITY_EVALUATOR_COMPARATORS_HPP
