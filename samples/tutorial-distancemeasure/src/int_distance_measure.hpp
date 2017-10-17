//
// Created by keks on 17.10.17.
//

#ifndef TUTORIAL_DISTANCEMEASURE_INT_DISTANCE_MEASURE_H
#define TUTORIAL_DISTANCEMEASURE_INT_DISTANCE_MEASURE_H

#include <mae/mae.hpp>


class int_distance_measure : public mae::math::i_distance_measure<int> {

public:
    int_distance_measure();
    ~int_distance_measure();

    virtual double distance(int element1, int element2) const;
};


#endif //TUTORIAL_DISTANCEMEASURE_INT_DISTANCE_MEASURE_H
