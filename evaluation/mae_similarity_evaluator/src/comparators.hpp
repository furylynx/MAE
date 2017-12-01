//
// Created on 01.12.17.
//

#ifndef MAE_SIMILARITY_EVALUATOR_COMPARATORS_HPP_HPP
#define MAE_SIMILARITY_EVALUATOR_COMPARATORS_HPP_HPP

//custom includes
#include "convenience.hpp"

//global includes
//...



std::vector<comparator_info> initialize_comparators()
{
    std::vector<comparator_info> result;

    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > manhattan_distance = std::make_shared<mae::math::minkowski_distance>(1);
    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > euclidean_distance = std::make_shared<mae::math::minkowski_distance>(2);
    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > mahalan_distance = std::make_shared<mae::math::mahalanobis_distance>();
    std::shared_ptr<mae::math::i_distance_measure<std::vector<double> > > cosine_distance = std::make_shared<mae::math::cosine_distance>();

    //hierarchy distance
    std::shared_ptr<mae::math::i_type_distance_measure> sologub_distance = std::make_shared<mae::math::sologub_tree_type_distance>(2);
    std::shared_ptr<mae::math::i_type_distance_measure> direct_distance = std::make_shared<mae::math::direct_tree_type_distance>(1);

    //use the movement comparator to compare movements (labanotation symbols)
    double distance_for_nullptr_ = 2;
    std::shared_ptr<mae::fl::laban::movement_comparator> mc_m_s_n = std::make_shared<mae::fl::laban::movement_comparator>(manhattan_distance, sologub_distance, -1);
    std::shared_ptr<mae::fl::laban::movement_comparator> mc_m_s_2 = std::make_shared<mae::fl::laban::movement_comparator>(manhattan_distance, sologub_distance, 2);
    std::shared_ptr<mae::fl::laban::movement_comparator> mc_m_d_n = std::make_shared<mae::fl::laban::movement_comparator>(manhattan_distance, direct_distance, -1);
    std::shared_ptr<mae::fl::laban::movement_comparator> mc_m_d_2 = std::make_shared<mae::fl::laban::movement_comparator>(manhattan_distance, direct_distance, 2);

    std::shared_ptr<mae::fl::laban::movement_comparator> mc_e_s_n = std::make_shared<mae::fl::laban::movement_comparator>(euclidean_distance, sologub_distance, -1);
    std::shared_ptr<mae::fl::laban::movement_comparator> mc_e_s_2 = std::make_shared<mae::fl::laban::movement_comparator>(euclidean_distance, sologub_distance, 2);
    std::shared_ptr<mae::fl::laban::movement_comparator> mc_e_d_n = std::make_shared<mae::fl::laban::movement_comparator>(euclidean_distance, direct_distance, -1);
    std::shared_ptr<mae::fl::laban::movement_comparator> mc_e_d_2 = std::make_shared<mae::fl::laban::movement_comparator>(euclidean_distance, direct_distance, 2);

    std::shared_ptr<mae::fl::laban::movement_comparator> mc_ml_s_n = std::make_shared<mae::fl::laban::movement_comparator>(mahalan_distance, sologub_distance, -1);
    std::shared_ptr<mae::fl::laban::movement_comparator> mc_ml_s_2 = std::make_shared<mae::fl::laban::movement_comparator>(mahalan_distance, sologub_distance, 2);
    std::shared_ptr<mae::fl::laban::movement_comparator> mc_ml_d_n = std::make_shared<mae::fl::laban::movement_comparator>(mahalan_distance, direct_distance, -1);
    std::shared_ptr<mae::fl::laban::movement_comparator> mc_ml_d_2 = std::make_shared<mae::fl::laban::movement_comparator>(mahalan_distance, direct_distance, 2);

    std::shared_ptr<mae::fl::laban::movement_comparator> mc_c_s_n = std::make_shared<mae::fl::laban::movement_comparator>(cosine_distance, sologub_distance, -1);
    std::shared_ptr<mae::fl::laban::movement_comparator> mc_c_s_2 = std::make_shared<mae::fl::laban::movement_comparator>(cosine_distance, sologub_distance, 2);
    std::shared_ptr<mae::fl::laban::movement_comparator> mc_c_d_n = std::make_shared<mae::fl::laban::movement_comparator>(cosine_distance, direct_distance, -1);
    std::shared_ptr<mae::fl::laban::movement_comparator> mc_c_d_2 = std::make_shared<mae::fl::laban::movement_comparator>(cosine_distance, direct_distance, 2);

    //set the window size, zero for no windowing
    std::size_t window = 0;
    double edr_epsilon = 0.5;
    std::shared_ptr<mae::math::i_distance_measure<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > > dtw_m_s_n_nw = std::make_shared<mae::math::dtw<std::shared_ptr<mae::fl::laban::i_movement> > >(mc_m_s_n, window);
    std::shared_ptr<mae::math::i_distance_measure<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > > dtw_m_s_2 = std::make_shared<mae::math::dtw<std::shared_ptr<mae::fl::laban::i_movement> > >(mc_m_s_2, window);
    std::shared_ptr<mae::math::i_distance_measure<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > > dtw_m_d_n = std::make_shared<mae::math::dtw<std::shared_ptr<mae::fl::laban::i_movement> > >(mc_m_d_n, window);
    std::shared_ptr<mae::math::i_distance_measure<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > > dtw_m_d_2 = std::make_shared<mae::math::dtw<std::shared_ptr<mae::fl::laban::i_movement> > >(mc_m_d_2, window);

    std::shared_ptr<mae::math::i_distance_measure<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > > dtw_e_s_n_nw = std::make_shared<mae::math::dtw<std::shared_ptr<mae::fl::laban::i_movement> > >(mc_e_s_n, window);
    std::shared_ptr<mae::math::i_distance_measure<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > > dtw_e_s_2 = std::make_shared<mae::math::dtw<std::shared_ptr<mae::fl::laban::i_movement> > >(mc_e_s_2, window);
    std::shared_ptr<mae::math::i_distance_measure<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > > dtw_e_d_n = std::make_shared<mae::math::dtw<std::shared_ptr<mae::fl::laban::i_movement> > >(mc_e_d_n, window);
    std::shared_ptr<mae::math::i_distance_measure<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > > dtw_e_d_2 = std::make_shared<mae::math::dtw<std::shared_ptr<mae::fl::laban::i_movement> > >(mc_e_d_2, window);

    std::shared_ptr<mae::math::i_distance_measure<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > > dtw_ml_s_n_nw = std::make_shared<mae::math::dtw<std::shared_ptr<mae::fl::laban::i_movement> > >(mc_ml_s_n, window);
    std::shared_ptr<mae::math::i_distance_measure<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > > dtw_ml_s_2 = std::make_shared<mae::math::dtw<std::shared_ptr<mae::fl::laban::i_movement> > >(mc_ml_s_2, window);
    std::shared_ptr<mae::math::i_distance_measure<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > > dtw_ml_d_n = std::make_shared<mae::math::dtw<std::shared_ptr<mae::fl::laban::i_movement> > >(mc_ml_d_n, window);
    std::shared_ptr<mae::math::i_distance_measure<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > > dtw_ml_d_2 = std::make_shared<mae::math::dtw<std::shared_ptr<mae::fl::laban::i_movement> > >(mc_ml_d_2, window);

    std::shared_ptr<mae::math::i_distance_measure<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > > dtw_c_s_n_nw = std::make_shared<mae::math::dtw<std::shared_ptr<mae::fl::laban::i_movement> > >(mc_c_s_n, window);
    std::shared_ptr<mae::math::i_distance_measure<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > > dtw_c_s_2 = std::make_shared<mae::math::dtw<std::shared_ptr<mae::fl::laban::i_movement> > >(mc_c_s_2, window);
    std::shared_ptr<mae::math::i_distance_measure<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > > dtw_c_d_n = std::make_shared<mae::math::dtw<std::shared_ptr<mae::fl::laban::i_movement> > >(mc_c_d_n, window);
    std::shared_ptr<mae::math::i_distance_measure<std::vector<std::shared_ptr<mae::fl::laban::i_movement> > > > dtw_c_d_2 = std::make_shared<mae::math::dtw<std::shared_ptr<mae::fl::laban::i_movement> > >(mc_c_d_2, window);

    // = std::make_shared<mae::math::dtw<std::shared_ptr<mae::fl::laban::i_movement> > >(movement_comparator, window);
    // = std::make_shared<mae::math::lcs_distance<std::shared_ptr<mae::fl::laban::i_movement> > >(movement_comparator);
    // = std::make_shared<mae::math::discrete_frechet_distance<std::shared_ptr<mae::fl::laban::i_movement> > >(movement_comparator);
    //= std::make_shared<mae::math::edr<std::shared_ptr<mae::fl::laban::i_movement> > >(movement_comparator, edr_epsilon);
    //= std::make_shared<mae::math::erp<std::shared_ptr<mae::fl::laban::i_movement> > >(movement_comparator, nullptr);

    bool ignore_empty_columns = true;
    unsigned int frames_per_beat = 1;
    double cut_steps = 2;
    double min_sequence_length_factor = 0.1;
    double max_sequence_length_factor = 2;

    result.push_back(initialize_comparator_info(-1, "dtw_m_s_n_nw", "", std::make_shared<mae::fl::laban::laban_target_sequence_comparator>(std::make_shared<mae::fl::laban::laban_sequence_comparator>(dtw_m_s_n_nw, ignore_empty_columns, frames_per_beat), false, cut_steps, min_sequence_length_factor, max_sequence_length_factor)));
    result.push_back(initialize_comparator_info(-1, "dtw_m_s_2", "", std::make_shared<mae::fl::laban::laban_target_sequence_comparator>(std::make_shared<mae::fl::laban::laban_sequence_comparator>(dtw_m_s_n_nw, ignore_empty_columns, frames_per_beat), false, cut_steps, min_sequence_length_factor, max_sequence_length_factor)));
    result.push_back(initialize_comparator_info(-1, "dtw_m_d_n", "", std::make_shared<mae::fl::laban::laban_target_sequence_comparator>(std::make_shared<mae::fl::laban::laban_sequence_comparator>(dtw_m_s_n_nw, ignore_empty_columns, frames_per_beat), false, cut_steps, min_sequence_length_factor, max_sequence_length_factor)));
    result.push_back(initialize_comparator_info(-1, "dtw_m_d_2", "", std::make_shared<mae::fl::laban::laban_target_sequence_comparator>(std::make_shared<mae::fl::laban::laban_sequence_comparator>(dtw_m_s_n_nw, ignore_empty_columns, frames_per_beat), false, cut_steps, min_sequence_length_factor, max_sequence_length_factor)));

    result.push_back(initialize_comparator_info(-1, "dtw_e_s_n_nw", "", std::make_shared<mae::fl::laban::laban_target_sequence_comparator>(std::make_shared<mae::fl::laban::laban_sequence_comparator>(dtw_m_s_n_nw, ignore_empty_columns, frames_per_beat), false, cut_steps, min_sequence_length_factor, max_sequence_length_factor)));
    result.push_back(initialize_comparator_info(-1, "dtw_e_s_2", "", std::make_shared<mae::fl::laban::laban_target_sequence_comparator>(std::make_shared<mae::fl::laban::laban_sequence_comparator>(dtw_e_s_2, ignore_empty_columns, frames_per_beat), false, cut_steps, min_sequence_length_factor, max_sequence_length_factor)));
    result.push_back(initialize_comparator_info(-1, "dtw_e_d_n", "", std::make_shared<mae::fl::laban::laban_target_sequence_comparator>(std::make_shared<mae::fl::laban::laban_sequence_comparator>(dtw_e_d_n, ignore_empty_columns, frames_per_beat), false, cut_steps, min_sequence_length_factor, max_sequence_length_factor)));
    result.push_back(initialize_comparator_info(-1, "dtw_e_d_2", "", std::make_shared<mae::fl::laban::laban_target_sequence_comparator>(std::make_shared<mae::fl::laban::laban_sequence_comparator>(dtw_e_d_2, ignore_empty_columns, frames_per_beat), false, cut_steps, min_sequence_length_factor, max_sequence_length_factor)));

    result.push_back(initialize_comparator_info(-1, "dtw_ml_s_n_nw", "", std::make_shared<mae::fl::laban::laban_target_sequence_comparator>(std::make_shared<mae::fl::laban::laban_sequence_comparator>(dtw_ml_s_n_nw, ignore_empty_columns, frames_per_beat), false, cut_steps, min_sequence_length_factor, max_sequence_length_factor)));
    result.push_back(initialize_comparator_info(-1, "dtw_ml_s_2", "", std::make_shared<mae::fl::laban::laban_target_sequence_comparator>(std::make_shared<mae::fl::laban::laban_sequence_comparator>(dtw_ml_s_2, ignore_empty_columns, frames_per_beat), false, cut_steps, min_sequence_length_factor, max_sequence_length_factor)));
    result.push_back(initialize_comparator_info(-1, "dtw_ml_d_n", "", std::make_shared<mae::fl::laban::laban_target_sequence_comparator>(std::make_shared<mae::fl::laban::laban_sequence_comparator>(dtw_ml_d_n, ignore_empty_columns, frames_per_beat), false, cut_steps, min_sequence_length_factor, max_sequence_length_factor)));
    result.push_back(initialize_comparator_info(-1, "dtw_ml_d_2", "", std::make_shared<mae::fl::laban::laban_target_sequence_comparator>(std::make_shared<mae::fl::laban::laban_sequence_comparator>(dtw_ml_d_2, ignore_empty_columns, frames_per_beat), false, cut_steps, min_sequence_length_factor, max_sequence_length_factor)));

    result.push_back(initialize_comparator_info(-1, "dtw_c_s_n_nw", "", std::make_shared<mae::fl::laban::laban_target_sequence_comparator>(std::make_shared<mae::fl::laban::laban_sequence_comparator>(dtw_m_s_n_nw, ignore_empty_columns, frames_per_beat), false, cut_steps, min_sequence_length_factor, max_sequence_length_factor)));
    result.push_back(initialize_comparator_info(-1, "dtw_c_s_2", "", std::make_shared<mae::fl::laban::laban_target_sequence_comparator>(std::make_shared<mae::fl::laban::laban_sequence_comparator>(dtw_c_s_2, ignore_empty_columns, frames_per_beat), false, cut_steps, min_sequence_length_factor, max_sequence_length_factor)));
    result.push_back(initialize_comparator_info(-1, "dtw_c_d_n", "", std::make_shared<mae::fl::laban::laban_target_sequence_comparator>(std::make_shared<mae::fl::laban::laban_sequence_comparator>(dtw_c_d_n, ignore_empty_columns, frames_per_beat), false, cut_steps, min_sequence_length_factor, max_sequence_length_factor)));
    result.push_back(initialize_comparator_info(-1, "dtw_c_d_2", "", std::make_shared<mae::fl::laban::laban_target_sequence_comparator>(std::make_shared<mae::fl::laban::laban_sequence_comparator>(dtw_c_d_2, ignore_empty_columns, frames_per_beat), false, cut_steps, min_sequence_length_factor, max_sequence_length_factor)));



    return result;
}

std::vector<comparator_info> map_comparator_ids(std::vector<comparator_info> comparators, std::unordered_map<std::string, int> comparator_id_map)
{
    for (comparator_info cinfo : comparators)
    {
        cinfo.id=comparator_id_map.at(cinfo.name);
    }

    return comparators;
}



#endif //MAE_SIMILARITY_EVALUATOR_COMPARATORS_HPP_HPP
