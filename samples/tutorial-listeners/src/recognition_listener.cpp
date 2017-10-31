/*
 * recognition_listener.cpp
 *
 *  Created on: 2017-10-31
 *      Author: furylynx
 */

#include "recognition_listener.hpp"

recognition_listener::recognition_listener()
{
}

recognition_listener::~recognition_listener()
{
}

void recognition_listener::on_recognition(uint64_t timestamp,
		std::vector<std::shared_ptr<mae::fl::laban::laban_sequence> > sequences)
{
	//simply print the gesture's title for each recognized sequence
	for (std::shared_ptr<mae::fl::laban::laban_sequence> sequence : sequences)
	{
		std::cout << "A sequence was recognized: '" << sequence->get_title() << "' at " << timestamp << std::endl;
	}
}

void recognition_listener::on_recognition(uint64_t timestamp, std::vector<std::string> titles)
{
	//simply print the given title for each recognized sequence
	for (std::string title : titles)
	{
		std::cout << "A sequence was recognized (title only): '" << title << "' at " << timestamp << std::endl;
	}
}

