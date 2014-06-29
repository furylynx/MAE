/*
 * sdl_controller.hpp
 *
 *  Created on: 29.06.2014
 *      Author: keks
 */

#ifndef SDL_CONTROLLER_HPP_
#define SDL_CONTROLLER_HPP_

//eclipse indexer fix

//custom includes
//...

//global includes
#include <thread>

#include <SDL2/SDL.h>

namespace lni
{

	class sdl_controller
	{
		public:
			static bool initialize_sdl();
			static bool close_sdl();

			static void add_event_callback(void * callback);

		private:
			static std::thread* t_;
			static bool running_;
			static bool initialized_;

			static void run_thread();
	};

} // namespace lni

#endif // SDL_CONTROLLER_HPP_
