////============================================================================
//// Name        : LabaNiTE.cpp
//// Author      : Børge
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
#include <mae/fl/fl_movement_controller.hpp>
#include <mae/fl/bvh_controller.hpp>
#include <mae/general_skeleton.hpp>

using namespace lni;

//---------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------

int main()
{
	std::cout << "LabaNiTe started" << std::endl;

	//not working currently
	bool store_skels = false;

	//trigger for bvh export
	bool bvh_export = false;
	unsigned int bvh_frames = 300; //30fps openni

	//trigger for demo screen
	bool show_demo = false;

	mae::fl::fl_movement_controller move = mae::fl::fl_movement_controller(true);

	if (show_demo)
	{
		//create and add listener
		std::shared_ptr<nite_display> ndisp = std::shared_ptr<nite_display>(new nite_display());
		move.add_listener(ndisp);
	}

	mae::fl::bvh_controller bvh_ctrl = mae::fl::bvh_controller();
	std::vector<std::shared_ptr<mae::general_skeleton> > wb_skels;

	unsigned int k = 0;
	bool quit = false;

	while (!xnOSWasKeyboardHit() && !quit)
	{
		std::vector<std::shared_ptr<mae::general_skeleton> > skeletons = nite_controller::wait_for_update();

		if (skeletons.size() > 0)
		{

			//std::cout << "Generated general_skeleton for each user" << std::endl;
			wb_skels.push_back(skeletons.at(0));

			// ofstream def
			std::ofstream* a_file;

			if (bvh_export)
			{
				if (wb_skels.size() > bvh_frames)
				{
					try
					{

						bvh_ctrl.bvh_file(wb_skels, "/home/keks/whole_sequence.bvh");
						std::cout << ">>  BVH EXPORT DONE" << std::endl;
						return 0;

					} catch (...)
					{
						std::cout << "unknown exception occured" << std::endl;
					}
				}
			}

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
