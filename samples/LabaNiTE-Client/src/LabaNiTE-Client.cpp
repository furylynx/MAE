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

#include <mae/indexer_fix.hpp>
#include <mae/eventing/eventing.hpp>


int main()
{
	std::cout << "LabaNiTE-Client started." << std::endl;

	std::cout << "Setting up the client...";
	mae::eventing::fl::fl_client client("localhost", mae::eventing::cs_base::get_default_port(), "BarneyGumble");
	std::cout << "done." << std::endl;

	//run while thread performs actions
	while(true)
		;

	return 0;
}
