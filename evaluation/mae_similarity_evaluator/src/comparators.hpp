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

    //TODO initialize
    result.push_back(initialize_comparator_info(-1, "dtw-mink1-dtree-nwin", "dtw with manhattan,direct tree and no window", nullptr));



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
