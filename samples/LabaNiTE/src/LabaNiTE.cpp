////============================================================================
//// Name        : LabaNiTE.cpp
//// Author      : Børge
////============================================================================

//custom includes
#include "nitecontroller.hpp"
#include "nite_display.hpp"
#include "sequence_printer.hpp"
#include "nite_recognition_display.hpp"

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
#include <mae/fl/laban/laban_sequence_reader.hpp>
#include <mae/fl/bvh_controller.hpp>
#include <mae/general_skeleton.hpp>

using namespace lni;


//---------------------------------------------------------------------------
// MAIN
//---------------------------------------------------------------------------

int main()
{
	std::cout << "LabaNiTe started" << std::endl;

	//trigger for bvh export
	bool bvh_export = true;
	unsigned int bvh_frames = 300; //30fps openni => 10 sec

	bool print_sequence = false;
	unsigned int sequence_frames = 300; //30fps openni => 10 sec
	std::string sequence_name = "mae_seq2.laban";

	//trigger for demo screen
	bool show_demo = false;

	bool read_stored_data = true;

	bool try_recognition = true;

	//bvh controller
	mae::fl::bvh_controller bvh_ctrl = mae::fl::bvh_controller();
	std::vector<std::shared_ptr<mae::general_skeleton> > wb_skels;

	try
	{
		//movement controller
		mae::fl::fl_movement_controller move = mae::fl::fl_movement_controller(sequence_frames + 50);

		if (show_demo)
		{
			//create and add listener
			std::shared_ptr<nite_display> ndisp = std::shared_ptr<nite_display>(new nite_display());
			move.add_listener(ndisp);
		}

		if (print_sequence)
		{
			std::shared_ptr<sequence_printer> nseq = std::shared_ptr<sequence_printer>(
					new sequence_printer(sequence_frames, sequence_name));
			move.add_listener(nseq);
		}

		if (try_recognition)
		{
			//register sequence
			move.register_sequence(mae::fl::laban::laban_sequence_reader().read_sequence_file(sequence_name));

			//register listener
			std::shared_ptr<nite_recognition_display> nrec = std::shared_ptr<nite_recognition_display>(
					new nite_recognition_display());
			move.add_listener(nrec);
		}

		if (read_stored_data)
		{
			try
			{

				std::pair<std::vector<std::shared_ptr<mae::general_skeleton> >, double> bvh_data =
						bvh_ctrl.read_bvh_file("/home/keks/whole_sequence.bvh", mae::fl::bvh_spec::default_spec());

				std::vector<std::shared_ptr<mae::general_skeleton> > skeletons = bvh_data.first;

				for (unsigned int i = 0; i < skeletons.size(); i++)
				{
					move.next_frame(i, skeletons.at(i));
				}

				std::cout << "-- done" << std::endl;

			} catch (std::exception& e)
			{
				std::cout << "exception: " << e.what() << std::endl;
				return -1;
			} catch (...)
			{
				std::cout << "Unknown exception or error occured" << std::endl;
				return -1;
			}

			return 0;
		}

		unsigned int k = 0;
		bool quit = false;

		while (!xnOSWasKeyboardHit() && !quit)
		{
			std::vector<std::shared_ptr<mae::general_skeleton> > skeletons = nite_controller::wait_for_update();

			if (skeletons.size() > 0)
			{

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

				if (bvh_export)
				{
					wb_skels.push_back(skeletons.at(0));

					if (wb_skels.size() > bvh_frames)
					{
						try
						{

							bvh_ctrl.print_bvh_file(wb_skels, "/home/keks/whole_sequence.bvh");
							std::cout << ">>  BVH EXPORT DONE" << std::endl;
							return 0;

						} catch (...)
						{
							std::cout << "unknown exception occured" << std::endl;
							return -1;
						}
					}
				}

				if (print_sequence && !bvh_export)
				{
					if (k > sequence_frames)
					{
						return 0;
					}
				}

				k++;
			}
		}
	}
	catch (std::exception &e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
		std::cout << "-- Aborted" << std::endl;
	}
	catch (...)
	{
		std::cerr << "Exception! " << std::endl;
		std::cout << "-- Aborted" << std::endl;
	}

	nite_controller::close();
}
