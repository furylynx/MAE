/*
 * nite_display.hpp
 *
 *  Created on: 26.06.2014
 *      Author: keks
 */

#ifndef NITE_DISPLAY_HPP_
#define NITE_DISPLAY_HPP_

//eclipse indexer fix


//custom includes
//...

//global includes
#include <model/pose_listener.hpp>
#include <model/general_skeleton.hpp>

#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


namespace lni
{

	class nite_display : public mae::pose_listener
	{
		public:
			nite_display();
			virtual ~nite_display();

			void on_pose(long timestamp, std::shared_ptr<mae::general_pose> pose);

		private:
			//The window we'll be rendering to
			SDL_Window* g_window_ = NULL;

			//The surface contained by the window
			SDL_Surface* g_screen_surface = NULL;

			//The image we will load and show on the screen
			SDL_Surface* g_background_ = NULL;

			//TODO other size?
			int SCREEN_WIDTH = 1024;
			int SCREEN_HEIGHT = 768;

			bool init_sdl();
			bool load_media_sdl();
			void close_sdl();
	};

} // namespace lni

#endif // NITE_DISPLAY_HPP_
