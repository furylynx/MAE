//============================================================================
// Name        : minimal-libmae_demo.cpp
// Author      : furylynx
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#define SDL_MAIN_HANDLED

#include <mae/demo/demo.hpp>

int main()
{
	std::cout << "Hello libmae_demo!" << std::endl;

	mae::demo::sdl_window window = mae::demo::sdl_window("minimal-libmae_demo", 300, 160);


	while (!window.is_closed())
	{
		mae::demo::sdl_window::update();
	}


	return 0;
}
