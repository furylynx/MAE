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
#include "sdl_controller.hpp"

//global includes
#include <mae/e_bone.hpp>
#include <mae/fl/e_fl_direction.hpp>

#include <mae/general_pose.hpp>
#include <mae/i_pose_listener.hpp>
#include <mae/i_recognition_listener.hpp>
#include <mae/fl/laban/laban_sequence.hpp>
//#include <model/general_skeleton.hpp>


#include <memory>
#include <sstream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


namespace lni
{

	class nite_display : public mae::i_pose_listener
	{
		public:
			nite_display();
			virtual ~nite_display();

			virtual void on_pose(long timestamp, std::shared_ptr<mae::general_pose> pose);

		private:
			static unsigned int ref_count_;
			static bool sdl_controller_;

			//The window we'll be rendering to
			SDL_Window* g_window_ = NULL;

			//The surface contained by the window
			SDL_Surface* g_screen_surface = NULL;

			//The image we will load and show on the screen
			SDL_Surface* g_background_ = NULL;

			std::vector<SDL_Surface*> g_directions;

			//TODO other size?
			const int SCREEN_WIDTH = 1024;
			const int SCREEN_HEIGHT = 768;

			bool init_sdl();
			bool load_media_sdl();
			void close_sdl();

	};

} // namespace lni

#endif // NITE_DISPLAY_HPP_
