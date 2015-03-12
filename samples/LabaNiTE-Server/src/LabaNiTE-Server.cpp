//============================================================================
// Name        : LabaNiTE-Server.cpp
// Author      : Børge
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#define SDL_MAIN_HANDLED

#include <cstddef>
#include <iostream>

#include <mae/indexer_fix.hpp>

#include <mae/nite/nite.hpp>
#include <mae/eventing/eventing.hpp>
#include <mae/demo/demo.hpp>
#include <mae/mae.hpp>

#include <boost/filesystem.hpp>



int main()
{
//	try
//	{
		std::cout << "LabaNiTE-Server started." << std::endl;

		//-----------------------
		//load configuration
		//-----------------------

		std::string sequences_dir = "sequences/";
		std::string tolerance_str = "0.5";
		double tolerance = 0.5;
		std::string bones = "RIGHT_WHOLE_ARM,LEFT_WHOLE_ARM";
		std::string debug_str = "false";
		bool debug = false;

		std::string config_path = "SamplesConfig.xml";
		std::string max_users_str = "15";
		int max_users = 15;

		std::string sequence_window_str = "false";
		bool sequence_window = false;
		std::string pose_window_str = "false";
		bool pose_window = false;
		std::string recognition_window_str = "false";
		bool recognition_window = false;


		std::string port_str = "1300";
		uint16_t port = 49337;//mae::eventing::cs_base::get_default_port();
		std::string password = "";

		std::cout << "Loading the configuration...";
		mae::ini_reader ini_reader = mae::ini_reader("config.ini");

		ini_reader.get_value_nex("mae", "sequences_dir", &sequences_dir);

		if (ini_reader.get_value_nex("mae", "tolerance", &tolerance_str))
		{
			tolerance = std::atof(tolerance_str.c_str());
		}

		if (ini_reader.get_value_nex("mae", "debug", &debug_str))
		{
			debug = mae::mbool::parse(debug_str);
		}

		ini_reader.get_value_nex("mae", "bones", &bones);


		ini_reader.get_value_nex("nite", "config_path", &config_path);
		if (ini_reader.get_value_nex("nite", "max_users", &max_users_str))
		{
			max_users = std::atol(max_users_str.c_str());
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

		if (ini_reader.get_value_nex("socket", "port", &port_str))
		{
			port = std::atol(port_str.c_str());
		}
		ini_reader.get_value_nex("socket", "password", &password);

		std::cout << "done." << std::endl;

		std::cout << "NiTE config path " << config_path << std::endl;
		std::cout << "max users " << max_users << std::endl;

		//-----------------------
		//set up the controller
		//-----------------------

		//body parts to be regarded
		std::vector<std::string> bones_split = mae::mstr::split(bones, ',');
		std::vector<mae::bone> body_parts;
		std::vector<std::shared_ptr<mae::fl::laban::column_definition> > column_definitions;

		std::cout << "body parts to be regarded:" << std::endl;
		for (unsigned int i = 0; i < bones_split.size(); i++)
		{
			mae::e_bone eb = mae::e_bone_c::parse(mae::mstr::trim(bones_split.at(i)));
			mae::bone b = mae::bone(eb);
			body_parts.push_back(b);
			std::cout << " - " << mae::e_bone_c::str(eb) << std::endl;

			if (std::abs(b.get_id()) != 1 && std::abs(b.get_id()) != 2 && std::abs(b.get_id()) != 4)
			{
				//generate column definition for the bone
				column_definitions.push_back(std::shared_ptr<mae::fl::laban::column_definition>(new mae::fl::laban::column_definition(eb)));
			}
		}

		//create the movement controller
		std::cout << "initialize fl movement controller" << std::endl;
		std::cout << "tolerance: " << tolerance << std::endl;

		mae::fl::fl_movement_controller movement_controller = mae::fl::fl_movement_controller(body_parts,
				column_definitions, 0, mae::fl::laban::laban_sequence::default_beats_per_measure(),
				mae::fl::laban::laban_sequence::default_beat_duration(),
				mae::fl::laban::laban_sequence::default_time_unit(), 1.0 / 30.0, debug);
		movement_controller.set_recognition_tolerance(tolerance);

		std::cout << "parse sequences to be registered" << std::endl;

		//read all sequences in the directory and register them to the controller
		mae::fl::laban::laban_sequence_reader s_reader = mae::fl::laban::laban_sequence_reader();

		try
		{
			if (boost::filesystem::is_directory(boost::filesystem::path(sequences_dir)))
			{
				boost::filesystem::path pp = boost::filesystem::path(sequences_dir);

				std::cout << "registering files..." << std::endl;

				for (boost::filesystem::directory_iterator it = boost::filesystem::directory_iterator(pp);
						it != boost::filesystem::directory_iterator(); it++)
				{
					boost::filesystem::directory_entry entry = *it;
					if (boost::filesystem::is_regular_file(entry.status()))
					{
						std::string file_path = entry.path().string();
						std::string file_name = entry.path().filename().string();

						if (file_name.rfind(".laban") == file_name.length() - 6)
						{
							try
							{
								std::shared_ptr<mae::fl::laban::laban_sequence> sequence = s_reader.read_sequence_file(
										file_path);
								if (sequence != nullptr)
								{
									std::cout << "registering \"" << sequence->get_title() << "\" from file '" << file_name
											<< "'" << std::endl;
									movement_controller.register_sequence(sequence);
								}
								else
								{
									std::cout << "!! Could not parse file '" << file_name << "'" << std::endl;
								}
							} catch (std::exception& e)
							{
								std::cout << "!! Could not parse file '" << file_name << "'" << std::endl;
							} catch (...)
							{
								std::cout << "!! Could not parse file '" << file_name << "'" << std::endl;
							}
						}
					}
				}
			}
			else
			{
				std::cout << "Directory '" << sequences_dir << "' does not exist! Quit program." << std::endl;
				return 0;
			}
		}
		catch (std::exception& e)
		{
			std::cout << "Exception on sequence registration: " << e.what() << std::endl;
		}
		catch (...)
		{
			std::cerr << "unknown exception" << std::endl;
		}

		//add sequence window for demo purposes
		std::shared_ptr<mae::demo::fl::sequence_window> swin = nullptr;
		if (sequence_window)
		{
			swin = std::shared_ptr<mae::demo::fl::sequence_window>(
					new mae::demo::fl::sequence_window("LabaNiTE-Server"));
			movement_controller.add_listener(swin);
		}

		std::shared_ptr<mae::demo::fl::pose_window> pwin = nullptr;
		if (pose_window)
		{
			pwin = std::shared_ptr<mae::demo::fl::pose_window>(
					new mae::demo::fl::pose_window("LabaNiTE-Server"));
			movement_controller.add_listener(pwin);
		}

		std::shared_ptr<mae::demo::fl::recognition_window> rwin = nullptr;
		if (recognition_window)
		{
			rwin = std::shared_ptr<mae::demo::fl::recognition_window>(
							new mae::demo::fl::recognition_window("LabaNiTE-Server"));
			movement_controller.add_listener(rwin);
		}

		//-----------------------
		//set up the driver
		//-----------------------

		std::cout << "Setting up the OpenNI/NiTE driver...";

		mae::nite::nite_farm nitef = mae::nite::nite_farm(config_path, max_users, true);

		std::cout << "done." << std::endl;

		//set up the server

		std::cout << "Setting up the server...";

		std::shared_ptr<mae::eventing::fl::fl_server> server = std::shared_ptr<mae::eventing::fl::fl_server>(
				new mae::eventing::fl::fl_server(&movement_controller, port, password, debug));
		movement_controller.add_listener(server);

		std::cout << "done." << std::endl;

		//-----------------------
		//process frames
		//-----------------------
		std::cout << "started processing..." << std::endl;
		while (!nitef.was_keyboard_hit() && (swin == nullptr || !swin->is_closed()) && (pwin == nullptr || !pwin->is_closed()) && (rwin == nullptr || !rwin->is_closed()))
		{
			//update the windows (includes polling events and repainting)
			mae::demo::sdl_window::update();

			std::vector<std::shared_ptr<mae::general_skeleton> > skeletons = nitef.wait_for_update();
			if (skeletons.size() > 0 && skeletons.at(0) != nullptr)
			{
				//std::cout << "LNiTE: next frame" << std::endl;
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

//	} catch (std::exception &e)
//	{
//		std::cerr << "An exception has occurred: " << e.what() << std::endl;
//	} catch (...)
//	{
//		std::cerr << "unknown exception" << std::endl;
//	}

	return 0;
}
