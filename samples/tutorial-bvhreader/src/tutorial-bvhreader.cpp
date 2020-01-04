//============================================================================
// Name        : tutorial-bvhreader.cpp
// Author      : furylynx
// Description : Tutorial for reading BVH files
//============================================================================

#include <iostream>

#include <mae/mae.hpp>

int main()
{
	// print message - program started
	std::cout << "tutorial - bvh reader " << std::endl;

	//create a bvh controller for bvh file reading
	mae::fl::bvh_controller reader = mae::fl::bvh_controller();

	//read the bvh file 'file.bvh' present in the current directory
	std::shared_ptr<mae::fl::bvh_data> data = reader.read_bvh_file("/home/keks/Downloads/2019-11-21_11-10-49.bvh", mae::fl::bvh_spec::motion_builder_spec());
//	std::shared_ptr<mae::fl::bvh_data> data = reader.read_bvh_file("file.bvh", mae::fl::bvh_spec::default_spec());

	//get the skeleton data from the bvh data
	std::vector<std::shared_ptr<mae::general_skeleton> > skeleton_data = data->get_skeleton_data();

//	//create a movement controller to handle the skeleton data
//	mae::fl::fl_movement_controller mcontroller = mae::fl::fl_movement_controller();
//
//	//iterate the frames of skeletons
//	for (std::size_t i = 0; i < skeleton_data.size(); i++)
//	{
//		//hand the skeleton data to the movement controller
//		mcontroller.next_frame(i, skeleton_data.at(i);
//	}
//
//	//get the produced laban sequence
//	std::shared_ptr<mae::fl::laban::laban_sequence> sequence = mcontroller.get_current_sequence();
//
//	//print the sequence in the xml format
//	sequence->xml_file("file.laban");
//
//	//print the sequence in the svg format (landscape format, 1920x1080)
//	sequence->svg_file("file.svg", 1080, 1920);

    std::cout << "framerate " << data->get_framerate() << std::endl;
//    std::cout << skeleton_data.at(0)->str() << std::endl;

//    reader.print_bvh_file(data->get_skeleton_data(), "file-out.bvh", 0.033333);
    reader.print_bvh_file(data->get_skeleton_data(), "/home/keks/Downloads/2019-11-21_11-10-49-out.bvh", 0.03333);
    
    for (std::size_t i = 0; i < data->get_skeleton_data().size(); i++)
    {
        std::stringstream sstr;
        sstr << "/home/keks/Downloads/2019-11-21_11-10-49-out-" << i << ".ply";
        data->get_skeleton_data().at(i)->ply_file(sstr.str());
    }

	return 0;
}
