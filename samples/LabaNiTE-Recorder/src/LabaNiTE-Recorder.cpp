//============================================================================
// Name        : LabaNiTE-Recorder.cpp
// Author      : Børge
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include <mae/indexer_fix.hpp>

#include <mae/nite/nite.hpp>
#include <mae/demo/demo.hpp>
#include <mae/mae.hpp>


int main()
{
	std::cout << "LabaNiTE-Recorder started." << std::endl;

	//-----------------------
	//load configuration
	//-----------------------

	std::string sequence_length_str = "10";
	unsigned int sequence_length = 10;
	std::string start_after_str = "3";
	unsigned int start_after = 3;

	std::string stop_record_on_key_str = "false";
	bool stop_record_on_key = false;

	std::string sequence_name = "new_sequence.laban";
	std::string sequences_dir = "sequences/";
	std::string config_path = "SamplesConfig.xml";

	//users are restricted to one
	int max_users = 1;

	std::string window_str = "false";
	bool window = false;

	std::string resources_dir = "resources";


	std::cout << "Loading the configuration...";
	mae::ini_reader ini_reader = mae::ini_reader("config.ini");

	if (ini_reader.get_value_nex("recorder", "sequence_length", &sequence_length_str))
	{
		sequence_length = std::stoul(sequence_length_str);
	}
	if (ini_reader.get_value_nex("recorder", "start_after", &start_after_str))
	{
		start_after = std::stoul(start_after_str);
	}
	if (ini_reader.get_value_nex("recorder", "stop_recording_on_key", &stop_record_on_key_str))
	{
		stop_record_on_key = mae::mbool::parse(stop_record_on_key_str);
	}

	ini_reader.get_value_nex("mae", "sequence_name", &sequence_name);
	ini_reader.get_value_nex("mae", "sequences_dir", &sequences_dir);

	ini_reader.get_value_nex("nite", "config_path", &config_path);

	if (ini_reader.get_value_nex("demo", "window", &window_str))
	{
		window = mae::mbool::parse(window_str);
	}

	ini_reader.get_value_nex("demo", "resources_dir", &resources_dir);

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

	mae::fl::fl_movement_controller movement_controller = mae::fl::fl_movement_controller(body_parts, column_definitions, sequence_length*30+1);

	//add window for demo purposes
	if (window)
	{
		//TODO generate window to visualize the countdowns, etc...
		std::shared_ptr<mae::demo::fl::sequence_window> swin = std::shared_ptr<mae::demo::fl::sequence_window>(new mae::demo::fl::sequence_window("LabaNiTE-Server", resources_dir));
		movement_controller.add_listener(swin);
	}

	std::cout << "Setting up the OpenNI/NiTE driver...";

	mae::nite::nite_controller nitec = mae::nite::nite_controller(config_path, max_users, true);

	std::cout << "done" << std::endl;

	//-----------------------
	//process frames
	//-----------------------
	std::cout << "started processing..." << std::endl;

	int wait_counter = 30*start_after;
	int lenght_counter = 30*sequence_length;
	while (!nitec.was_keyboard_hit())
	{
		if (wait_counter > 0)
		{
			wait_counter--;
		}
		else
		{
			if (lenght_counter > 0)
			{
				std::vector<std::shared_ptr<mae::general_skeleton> > skeletons = nitec.wait_for_update();
				if (skeletons.size() > 0 && skeletons.at(0) != nullptr)
				{
					movement_controller.next_frame(0, skeletons.at(0));
				}
			}
			else
			{
				//stop
				break;
			}
		}

	}

	return 0;
}
