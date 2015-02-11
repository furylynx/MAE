//============================================================================
// Name        : minimal-libmae_eventing.cpp
// Author      : furylynx
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include <mae/eventing/eventing.hpp>


int main()
{
	std::cout << "Hello libmae_eventing!" << std::endl; // prints Hello libmae_eventing!

	std::shared_ptr<mae::fl::laban::laban_sequence> seq = std::shared_ptr<mae::fl::laban::laban_sequence>(new mae::fl::laban::laban_sequence("MySequence", "Anonymous", 2, mae::fl::laban::e_time_unit::MILLISECOND, 100, 5));

	mae::eventing::fl::laban_serializer ls = mae::eventing::fl::laban_serializer();

	std::cout << "Sequence title: " << ls.get_title(seq) << std::endl;

	return 0;
}
