//
// Created by keks on 17.10.17.
//

#include "int_distance_measure.hpp"

int_distance_measure::int_distance_measure()
{

}


int_distance_measure::~int_distance_measure()
{

}

double int_distance_measure::distance(int element1, int element2) const
{
    return std::abs(element1-element2);
}
