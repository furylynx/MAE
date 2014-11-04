//============================================================================
// Name        : LabaNiTE-Client.cpp
// Author      : Børge
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================



//custom includes

//global includes
#include <cstddef>
#include <iostream>

#include <mae/indexer_fix.hpp>
#include <mae/eventing/eventing.hpp>
#include <mae/demo/demo.hpp>


int main()
{
	std::cout << "LabaNiTE-Client started." << std::endl;

	std::cout << "Setting up the client...";
	mae::eventing::fl::fl_client client("localhost", mae::eventing::cs_base::get_default_port(), "BarneyGumble", false);
	std::cout << "done." << std::endl;

	std::shared_ptr<mae::demo::fl::recognition_window> rwin = std::shared_ptr<mae::demo::fl::recognition_window>(new mae::demo::fl::recognition_window("LabaNiTE-Client - Recognition Window"));
	client.add_listener(rwin);

	//run while thread performs actions
	getchar();

	return 0;
}
