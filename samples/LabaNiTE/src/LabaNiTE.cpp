////============================================================================
//// Name        : LabaNiTE.cpp
//// Author      : Børge
//// Version     :
//// Copyright   :
//// Description : Hello World in C++, Ansi-style
////============================================================================

//custom includes
#include "nitecontroller.hpp"
#include "nite_display.hpp"

//general includes
#include <memory>
#include <fstream>
#include <sstream>

#include <iostream>
#include <iomanip>
#include <ctime>

#include <XnCppWrapper.h>

#include <SDL2/SDL.h>

//fl : mae includes
#include <fl/fl_movement_controller.hpp>
#include <fl/bvh_controller.hpp>
#include <model/general_skeleton.hpp>
#include <model/general_joint.hpp>
#include <model/maej.hpp>

using namespace lni;

//---------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------

int main()
{
	std::cout << "LabaNiTe started" << std::endl;
	bool store_skels = false;

	mae::fl::fl_movement_controller move = mae::fl::fl_movement_controller();

	//create and add listener
	std::shared_ptr<nite_display> ndisp = std::shared_ptr<nite_display>(new nite_display());
	move.add_listener(ndisp);
	std::cout << "done" << std::endl;

	mae::fl::bvh_controller bvh_ctrl = mae::fl::bvh_controller();
	std::vector<std::shared_ptr<mae::general_skeleton> > wb_skels;

	unsigned int k = 0;
	bool quit = false;

	while (!xnOSWasKeyboardHit() && !quit)
	{
		//keep window alive
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		std::vector<std::shared_ptr<mae::general_skeleton> > skeletons = nite_controller::wait_for_update();

		if (skeletons.size() > 0)
		{
			//std::cout << "Generated general_skeleton for each user" << std::endl;
			wb_skels.push_back(skeletons.at(0));

			// ofstream def
			std::ofstream* a_file;

			if (store_skels)
			{
				// filename string
				std::ostringstream filename;
				filename << SKEL_STORE_PATH << "skeleton" << k << ".txt";

				// create file
				a_file = new std::ofstream(filename.str());

				// print header to file
				*a_file << "// OpenNi/NiTE Skeleton and MAE General Skeleton" << std::endl;

				//print date to file
				std::time_t now = std::time(nullptr);
				std::tm now_local = *std::localtime(&now);
				*a_file << "// " << (now_local.tm_year + 1900) << '-' << (now_local.tm_mon + 1) << '-'
						<< now_local.tm_mday << " " << now_local.tm_hour << ":" << now_local.tm_min << ":"
						<< now_local.tm_sec << std::endl << std::endl;

				//print skeleton initialization to file
				*a_file
						<< "std::shared_ptr<mae::model::GeneralSkeleton> skeleton = std::shared_ptr<mae::model::GeneralSkeleton>(new mae::model::GeneralSkeleton());"
						<< std::endl << std::endl;

				//print joint assignment to file (for later use)
//				*a_file << "// " << mae::maej_str[joint_ids_mae[j]] << " (" << xn_joint.position.position.X << ", "
//						<< xn_joint.position.position.Y << ", " << xn_joint.position.position.Z << ")" << std::endl;
//				*a_file << "skeleton->setJoint(" << (int) joint_ids_mae[j]
//						<< ", std::shared_ptr<mae::model::GeneralJoint>(new mae::model::GeneralJoint("
//						<< (double) xn_joint.position.position.X << ", " << (double) xn_joint.position.position.Y
//						<< ", " << (double) xn_joint.position.position.Z << ")));" << std::endl;

// Close the file stream explicitly
				a_file->close();
				delete a_file;
			}

//			try
//			{
//				if (wb_skels.size() > 120)
//				{
//					bvh_ctrl.bvh_file(wb_skels, "/home/keks/whole_sequence.bvh");
//					std::cout << "done" << std::endl;
//					return 0;
//				}
//			}
//			catch(...)
//			{
//				std::cout << "unknown exception occured" << std::endl;
//			}

			try
			{
				move.next_frame(0, skeletons.at(0));
			} catch (std::exception& e)
			{
				std::cout << "exception: " << e.what() << std::endl;
				return -1;
			} catch (...)
			{
				std::cout << "Unknown exception or error occured" << std::endl;
				return -1;
			}
			k++;
		}
	}

	nite_controller::close();
}
