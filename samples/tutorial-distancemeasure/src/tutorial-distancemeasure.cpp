//============================================================================
// Name        : tutorial-distancemeasure.cpp
// Author      : furylynx
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//custom includes
#include "int_distance_measure.hpp"

//global includes
#include <iostream>

#include <mae/mae.hpp>


int main()
{
	// print message - program started
	std::cout << "tutorial - distance measure " << std::endl;

	std::vector<int> seq1 = {1, 2, 3, 4, 5};
	std::vector<int> seq2 = {1, 1, 1, 1, 2, 3, 3, 4, 5};


	//create a bvh controller for bvh file reading
	mae::math::dtw<int> cc (std::make_shared<int_distance_measure>());

	double d = cc.distance(seq1, seq2);

	std::cout << "Distance: " << d << std::endl;

	return 0;
}
