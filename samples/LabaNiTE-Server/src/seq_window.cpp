/*
 * seq_window.cpp
 *
 *  Created on: 19.09.2014
 *      Author: keks
 */

#include "seq_window.hpp"

namespace lni
{

	seq_window::seq_window() : sdl_window("LabaNiTE-Server", 1024, 768)
	{
	}

	seq_window::~seq_window()
	{
	}

	void seq_window::paint(SDL_Surface* graphics)
	{
		//TODO repaint when
	}

	void seq_window::handle_event(SDL_Event& e)
	{
		//TODO handle event
	}

	void seq_window::on_recognition(long timestamp, std::vector<std::shared_ptr<mae::fl::laban::laban_sequence> > sequences)
	{
		repaint();
	}

	void seq_window::on_recognition(long timestamp, std::vector<std::string> title)
	{
		repaint();
	}

} // namespace lni
