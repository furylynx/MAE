//============================================================================
// Name        : LabaNiTE-Server.cpp
// Author      : Børge
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include <mae/nite/nite.hpp>
#include <mae/eventing/eventing.hpp>
#include <mae/mae.hpp>


int main()
{
	std::cout << "LabaNiTE started." << std::endl; // prints Hello

	std::string sequences_dir = "sequences/";


	//load configuration
	std::string config_path = "SamplesConfig.xml";
	std::string max_users_str = "15";
	int max_users = 15;

	std::string port_str = "1300";
	uint16_t port = mae::eventing::cs_base::get_default_port();
	std::string password = "";

	std::cout << "Setting up the OpenNI/NiTE driver...";
	mae::ini_reader ini_reader = mae::ini_reader("config.ini");

	ini_reader.get_value_nex("mae", "sequences_dir", &sequences_dir);

	ini_reader.get_value_nex("nite", "config_path", &config_path);
	ini_reader.get_value_nex("nite", "max_users", &max_users_str);
	max_users = std::stoul(max_users_str);

	ini_reader.get_value_nex("socket", "port", &port_str);
	port = std::stoul(port_str);
	ini_reader.get_value_nex("socket", "password", &password);

	std::cout << "done." << std::endl;

	std::cout << "NiTE config path " << config_path << std::endl;
	std::cout << "max users " << max_users << std::endl;


	//set up the driver


	std::cout << "Setting up the OpenNI/NiTE driver...";

	mae::nite::nite_controller nitec = mae::nite::nite_controller(config_path, max_users, true);

	std::cout << "done." << std::endl;


	while (!nitec.was_keyboard_hit())
	{
		std::vector<std::shared_ptr<mae::general_skeleton> > skeletons = nitec.wait_for_update(15);

		if (skeletons.size() > 0 && skeletons.at(0) != nullptr)
		{
			std::cout << skeletons.at(0)->get_joint(mae::e_joint_c::to_int(mae::e_joint::RIGHT_HAND))->get_confidence() << std::endl;
		}

	}

	//set up the controller

	//TODO read all sequences in the directory

	//set up the server

//	std::cout << "Setting up the server...";
//
//	mae::eventing::fl::fl_server server = mae::eventing::fl::fl_server();
//
//	std::cout << "done." << std::endl;


	return 0;
}
