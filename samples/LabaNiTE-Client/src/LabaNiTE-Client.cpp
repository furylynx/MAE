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

	//-----------------------
	//load configuration
	//-----------------------

	std::string debug_str = "false";
	bool debug = false;

	std::string recognition_window_str = "false";
	bool recognition_window = false;

	std::string address = "localhost";
	std::string port_str = "1300";
	uint16_t port = mae::eventing::cs_base::get_default_port();
	std::string password = "";

	std::cout << "Loading the configuration...";
	mae::ini_reader ini_reader = mae::ini_reader("config.ini");

	if (ini_reader.get_value_nex("mae", "debug", &debug_str))
	{
		debug = mae::mbool::parse(debug_str);
	}

	if (ini_reader.get_value_nex("demo", "recognition_window", &recognition_window_str))
	{
		recognition_window = mae::mbool::parse(recognition_window_str);
	}

	ini_reader.get_value_nex("socket", "address", &address);

	if (ini_reader.get_value_nex("socket", "port", &port_str))
	{
		port = std::stoul(port_str);
	}
	ini_reader.get_value_nex("socket", "password", &password);


	std::cout << "done." << std::endl;


	//-----------------------
	//set up the client
	//-----------------------

	std::cout << "Trying to connect to " << address << ":" << port << " with the specified password." << std::endl;

	std::cout << "Setting up the client...";
	try
	{
		mae::eventing::fl::fl_client client(address, mae::eventing::cs_base::get_default_port(), "BarneyGumble", false);
		std::cout << "done." << std::endl;

		if (recognition_window)
		{
			std::shared_ptr<mae::demo::fl::recognition_window> rwin = std::shared_ptr<mae::demo::fl::recognition_window>(new mae::demo::fl::recognition_window("LabaNiTE-Client - Recognition Window"));
			client.add_listener(rwin);
		}
	}
	catch(...)
	{
		std::cerr << "failed." << std::endl;
		return 1;
	}


	//run while thread performs actions
	while(true)
	{
		//update the windows (includes polling events and repainting)
		mae::demo::sdl_window::update();
	}

	return 0;
}
