//============================================================================
// Name        : LabaNiTE-Server.cpp
// Author      : Børge
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include <mae/indexer_fix.hpp>

#include <mae/nite/nite.hpp>
#include <mae/eventing/eventing.hpp>
#include <mae/demo/demo.hpp>
#include <mae/mae.hpp>


#include <boost/filesystem.hpp>


int main()
{
	std::cout << "LabaNiTE-Server started." << std::endl;


	//-----------------------
	//load configuration
	//-----------------------

	std::string sequences_dir = "sequences/";
	std::string config_path = "SamplesConfig.xml";
	std::string max_users_str = "15";
	int max_users = 15;

	std::string sequence_window_str = "false";
	bool sequence_window = false;
	std::string pose_window_str = "false";
	bool pose_window = false;
	std::string recognition_window_str = "false";
	bool recognition_window = false;

	std::string resources_dir = "resources";

	std::string port_str = "1300";
	uint16_t port = mae::eventing::cs_base::get_default_port();
	std::string password = "";

	std::cout << "Setting up the OpenNI/NiTE driver...";
	mae::ini_reader ini_reader = mae::ini_reader("config.ini");

	ini_reader.get_value_nex("mae", "sequences_dir", &sequences_dir);

	ini_reader.get_value_nex("nite", "config_path", &config_path);
	if (ini_reader.get_value_nex("nite", "max_users", &max_users_str))
	{
		max_users = std::stoul(max_users_str);
	}

	if (ini_reader.get_value_nex("demo", "sequence_window", &sequence_window_str))
	{
		sequence_window = mae::mbool::parse(sequence_window_str);
	}
	if (ini_reader.get_value_nex("demo", "pose_window", &pose_window_str))
	{
		pose_window = mae::mbool::parse(pose_window_str);
	}
	if (ini_reader.get_value_nex("demo", "recognition_window", &recognition_window_str))
	{
		recognition_window = mae::mbool::parse(recognition_window_str);
	}

	ini_reader.get_value_nex("demo", "resources_dir", &resources_dir);

	if (ini_reader.get_value_nex("socket", "port", &port_str))
	{
		port = std::stoul(port_str);
	}
	ini_reader.get_value_nex("socket", "password", &password);

	std::cout << "done." << std::endl;

	std::cout << "NiTE config path " << config_path << std::endl;
	std::cout << "max users " << max_users << std::endl;



	//-----------------------
	//set up the controller
	//-----------------------

	std::vector<mae::bone> body_parts;
	body_parts.push_back(mae::bone::create_bone(mae::e_bone::RIGHT_WHOLE_ARM));
	body_parts.push_back(mae::bone::create_bone(mae::e_bone::LEFT_WHOLE_ARM));

	std::vector<std::shared_ptr<mae::fl::laban::column_definition> > column_definitions;

	mae::fl::fl_movement_controller movement_controller = mae::fl::fl_movement_controller(body_parts, column_definitions, 150);

	//read all sequences in the directory and register them to the controller
	mae::fl::laban::laban_sequence_reader s_reader = mae::fl::laban::laban_sequence_reader();

	if (boost::filesystem::is_directory(boost::filesystem::path(sequences_dir)))
	{
		boost::filesystem::path pp = boost::filesystem::path(sequences_dir);

		std::cout << "registering files..." << std::endl;

		for (boost::filesystem::directory_iterator it = boost::filesystem::directory_iterator(pp); it != boost::filesystem::directory_iterator(); it++)
		{
			boost::filesystem::directory_entry entry = *it;
			if (boost::filesystem::is_regular_file(entry.status()))
			{
				std::string file_path = entry.path().string();
				std::string file_name = entry.path().filename().string();

				if (file_name.rfind(".laban") == file_name.length()-6)
				{
					try
					{
						std::shared_ptr<mae::fl::laban::laban_sequence> sequence = s_reader.read_sequence_file(file_path);
						if (sequence != nullptr)
						{
							std::cout << "registering \"" << sequence->get_title() << "\" from file '" << file_name << "'" << std::endl;
							movement_controller.register_sequence(sequence);
						}
						else
						{
							std::cout << "!! Could not parse file '" << file_name << "'" << std::endl;
						}
					}
					catch(std::exception& e)
					{
						std::cout << "!! Could not parse file '" << file_name << "'" << std::endl;
					}
					catch(...)
					{
						std::cout << "!! Could not parse file '" << file_name << "'" << std::endl;
					}
				}
			}
		}
	}
	else
	{
		std::cout << "Directory '" << sequences_dir <<  "' does not exist! Quit program." << std::endl;
		return 0;
	}

	//add sequence window for demo purposes
	if (sequence_window)
	{
		std::shared_ptr<mae::demo::fl::sequence_window> swin = std::shared_ptr<mae::demo::fl::sequence_window>(new mae::demo::fl::sequence_window("LabaNiTE-Server", resources_dir));
		movement_controller.add_listener(swin);
	}

	if (pose_window)
	{
		//TODO draw pose window
	}

	if (recognition_window)
	{
		std::shared_ptr<mae::demo::fl::recognition_window> rwin = std::shared_ptr<mae::demo::fl::recognition_window>(new mae::demo::fl::recognition_window("LabaNiTE-Server", resources_dir));
		movement_controller.add_listener(rwin);
	}

	//-----------------------
	//set up the driver
	//-----------------------

	std::cout << "Setting up the OpenNI/NiTE driver...";

	mae::nite::nite_controller nitec = mae::nite::nite_controller(config_path, max_users, true);

	std::cout << "done." << std::endl;


	//set up the server

	std::cout << "Setting up the server...";

	std::shared_ptr<mae::eventing::fl::fl_server> server = std::shared_ptr<mae::eventing::fl::fl_server>(new mae::eventing::fl::fl_server(&movement_controller, port, password));
	movement_controller.add_listener(server);

	std::cout << "done." << std::endl;


	//-----------------------
	//process frames configuration
	//-----------------------
	std::cout << "started processing..." << std::endl;
	while (!nitec.was_keyboard_hit())
	{
		std::vector<std::shared_ptr<mae::general_skeleton> > skeletons = nitec.wait_for_update();
		if (skeletons.size() > 0 && skeletons.at(0) != nullptr)
		{
			movement_controller.next_frame(0, skeletons.at(0));
		}
	}

//	long counter = 0;
//	while (true)
//	{
//		if (mae::nite::nite_controller::xn_was_keyboard_hit())
//		{
//			std::cout << "send message to clients..." << std::endl;
//			std::vector<std::shared_ptr<mae::fl::laban::laban_sequence> > sequences;
//			sequences.push_back(std::shared_ptr<mae::fl::laban::laban_sequence>(new mae::fl::laban::laban_sequence("test_title", "server", 2, mae::fl::laban::e_time_unit::MILLISECOND, 200, 5)));
//
//			server.notify_clients(counter, sequences);
//
//			while(true);
//		}
//		counter++;
//	}


	return 0;
}
