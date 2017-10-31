//============================================================================
// Name        : tutorial-bvhreader.cpp
// Author      : furylynx
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//custom includes
#include "recognition_listener.hpp"

//gobal includes
#include <iostream>

#include <mae/mae.hpp>

int main()
{
	// print message - program started
	std::cout << "tutorial - bvh reader " << std::endl;

	//create a bvh controller for bvh file reading
	mae::fl::bvh_controller reader;

	//read the bvh file 'file.bvh' present in the current directory
	std::shared_ptr<mae::fl::bvh_data> data = reader.read_bvh_file("file.bvh", mae::fl::bvh_spec::default_spec());

	//get the skeleton data from the bvh data
	std::vector<std::shared_ptr<mae::general_skeleton> > skeleton_data = data->get_skeleton_data();

	//create a movement controller to handle the skeleton data
	mae::fl::fl_movement_controller mcontroller = mae::fl::fl_movement_controller();

    //create a laban sequence reader
    mae::fl::laban::laban_sequence_reader laban_reader;

    //read the definition of a swipe gesture
    std::shared_ptr<mae::fl::laban::laban_sequence> swipe_sequence = laban_reader.read_sequence_file("swipe.laban");

    //register the gesture for recognition
    mcontroller.register_sequence(swipe_sequence);

    //create a recognition listener that listens to recognized sequences
    std::shared_ptr<recognition_listener> rec_listener = std::make_shared<recognition_listener>();

    //register the listener
    mcontroller.add_listener(rec_listener);

	//iterate the frames of skeletons
	for (std::size_t i = 0; i < skeleton_data.size(); i++)
	{
		//hand the skeleton data to the movement controller
		mcontroller.next_frame(mae::mos::current_time_millis(), skeleton_data.at(i));
	}

	return 0;
}
