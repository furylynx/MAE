//============================================================================
// Name        : tutorial-bvhreader.cpp
// Author      : furylynx
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include <mae/mae.hpp>

int main()
{
	std::cout << "tutorial - bvh reader " << std::endl;

	mae::fl::bvh_controller reader = mae::fl::bvh_controller();
	std::shared_ptr<mae::fl::bvh_data> data = reader.read_bvh_file("file.bvh", mae::fl::bvh_spec::default_spec);

	std::vector<std::shared_ptr<mae::general_skeleton> > skeleton_data = data->get_skeleton_data();

	//TODO movement controller

	for (size_t i = 0; i < skeleton_data.size(); i++)
	{
		//TODO pass to movement controller
	}

	//do something - store to svg file or laban file or something

	return 0;
}
