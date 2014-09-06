//============================================================================
// Name        : LabaNiTE-Client.cpp
// Author      : Børge
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

//custom includes

//global includes
#include <iostream>


#include <mae/eventing/fl/fl_client.hpp>


int main()
{
	std::cout << "Hello" << std::endl; // prints Hello

	mae::eventing::fl::fl_client client("localhost");


	//run while thread performs actions
	while(true)
		;

	return 0;
}
