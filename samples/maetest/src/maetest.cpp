//============================================================================
// Name        : maetest.cpp
// Author      : fury lynx
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <mae/fl/math.hpp>

int main() {

	// prints Hello
	std::cout << "Hello" << std::endl;

	cv::Vec3d a = cv::Vec3d(1,0,0);
	cv::Vec3d b = cv::Vec3d(-1,-1,0);
	cv::Vec3d normal = cv::Vec3d(0,0,1);
	double result = mae::fl::math::calc_angle_half_deg(a, b);

	std::cout << "result: " << result << std::endl;

	return 0;
}
