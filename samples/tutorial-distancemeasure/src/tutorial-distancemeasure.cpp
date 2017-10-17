//============================================================================
// Name        : tutorial-bvhreader.cpp
// Author      : furylynx
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include <mae/mae.hpp>

int main()
{
	// print message - program started
	std::cout << "tutorial - distance measure " << std::endl;

	std::vector<int> seq1 = {1, 2, 3, 4};
	std::vector<int> seq2 = {1, 1, 2, 3, 4};


	//create a bvh controller for bvh file reading
	mae::math::dtw<int> cc (nullptr);

	double d = cc.distance(seq1, seq2);

	std::cout << "Distance: " << d << std::endl;

	return 0;
}
