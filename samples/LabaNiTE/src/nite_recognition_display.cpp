/*
 * nite_recognition_display.cpp
 *
 *  Created on: 02.09.2014
 *      Author: keks
 */

#include "nite_recognition_display.hpp"

namespace lni
{

	nite_recognition_display::nite_recognition_display()
	{
	}

	nite_recognition_display::~nite_recognition_display()
	{
	}

	void nite_recognition_display::on_recognition(long timestamp, std::vector<std::shared_ptr<mae::fl::laban::laban_sequence> > sequences)
	{


		std::cout << "Recognition listener -- Recognized sequences at timestamp: " << timestamp << std::endl;
		for(unsigned int i = 0; i < sequences.size(); i++)
		{
			std::cout << ">> " << sequences.at(i)->get_title() << std::endl;
		}

		//TODO print to window if existing?!
	}

} // namespace lni
