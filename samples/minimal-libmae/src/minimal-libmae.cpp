//============================================================================
// Name        : minimal-libmae.cpp
// Author      : fury lynx
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include <mae/mae.hpp>

int main()
{
	std::cout << ">> Hello libmae <<" << std::endl;

	mae::math::vec3d vec = mae::math::vec3d(1,2,3);
	std::cout << vec << std::endl;

	return 0;
}
