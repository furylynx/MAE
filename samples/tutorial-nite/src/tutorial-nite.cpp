//============================================================================
// Name        : tutorial-nite.cpp
// Author      : furylynx
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include <mae/mae.hpp>
#include <mae/nite/nite.hpp>

int main()
{
	std::cout << "Hello tutorial-nite!" << std::endl;

	//create the nite controller which is used to get the skeleton data from the sensor
	mae::nite::nite_controller nitecontroller = mae::nite::nite_controller("SampleConfig.xml");

	//create a movement controller to handle the skeleton data
	mae::fl::fl_movement_controller mcontroller = mae::fl::fl_movement_controller();

	//loop until a key is pressed
	while (!nitecontroller.was_keyboard_hit())
	{
		//get the skeleton data from the stream. We get a skeleton for each user.
		std::vector<std::shared_ptr<mae::general_skeleton> > skeleton_data = nitecontroller.wait_for_update();

		//check whether the first user is listed in the vector and use it
		if (skeleton_data.size() > 0 && skeleton_data.at(0) != nullptr)
		{
			//hand the skeleton data for the first user to the movement controller
			mcontroller.next_frame(0, skeleton_data.at(0));
		}
	}

	//get the generated laban sequence
	std::shared_ptr<mae::fl::laban::laban_sequence> sequence = mcontroller.get_current_sequence();

	//print the sequence in the xml format
	sequence->xml_file("file-tutorial-nite.laban");

	//print the sequence in the svg format (landscape format, 1920x1080)
	sequence->svg_file("file-tutorial-nite.svg", 1080, 1920);


	return 0;
}
