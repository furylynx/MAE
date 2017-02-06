/*
 * sdl_controller.cpp
 *
 *  Created on: 29.06.2014
 *      Author: keks
 */

#include "sdl_controller.hpp"

namespace lni
{
	//------
	//members
	//------
	bool sdl_controller::running_ = false;
	bool sdl_controller::initialized_ = false;
	std::thread* sdl_controller::t_ = nullptr;

	//------
	//methods
	//------
	bool sdl_controller::initialize_sdl()
	{
		if (!running_)
		{
			t_ = new std::thread(run_thread);

			//wait until thread has initialized the sdl
			while (!initialized_)
			{
				//do nothing
			}

			return true;
		}
		else
		{
			//already running
			return false;
		}
	}

	bool sdl_controller::close_sdl()
	{
		if (!running_)
		{
			running_ = false;

			//wait until thread has uninitialized the sdl
			while (initialized_)
			{
				//do nothing
			}

			//wait for thread to finish
			t_->join();
			delete t_;

			return true;
		}
		else
		{
			//not initialized before
			return false;
		}
	}

	void sdl_controller::add_event_callback(void * callback)
	{

	}

	void sdl_controller::run_thread()
	{
		running_ = true;

		if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		{
			throw std::invalid_argument("Could not initialize SDL");
		}

		initialized_ = true;

		while (running_)
		{
			//keep window alive
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				//notify listeners
//				if (event.type == SDL_QUIT)
//				{
//					quit = true;
//				}
			}

			SDL_Delay(50);
		}

		SDL_Quit();
		initialized_ = false;
	}

} // namespace lni
