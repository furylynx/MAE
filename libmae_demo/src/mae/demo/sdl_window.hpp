/*
 * sdl_window.hpp
 *
 *  Created on: 19.09.2014
 *      Author: keks
 */

#ifndef SDL_WINDOW_HPP_
#define SDL_WINDOW_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes


//global includes
#include <memory>
#include <vector>
#include <string>
#include <thread>

#include <SDL2/SDL.h>

namespace mae
{
	namespace demo
	{

		class sdl_window
		{
			public:
				sdl_window(std::string title, int width, int height, int x_pos = SDL_WINDOWPOS_UNDEFINED, int y_pos = SDL_WINDOWPOS_UNDEFINED, Uint32 flags = SDL_WINDOW_SHOWN);
				virtual ~sdl_window();

				virtual void set_title(std::string title);
				virtual std::string get_title();

				virtual void set_width(int width);
				virtual int get_width();

				virtual void set_height(int height);
				virtual int get_height();

				void set_size(int width, int height);

				/**
				 * Returns the pointer to the SDL_WINDOW which remains valid until this object gets destroyed.
				 *
				 * @return A pointer to the window.
				 */
				virtual SDL_Window* get();

				virtual void repaint();

			protected:

				virtual void handle_event(SDL_Event& e);
				virtual void paint(SDL_Surface* graphics);

			private:

				std::string title_;
				SDL_Window* window_;


				//****************
				// static
				//****************
				static std::vector<sdl_window*> windows_;
				static std::thread thread_;
				static bool initialized_;

				static void remove_window(sdl_window* window);
				static void sdl_run();
		};

	} // namespace demo
} // namespace mae

#endif // SDL_WINDOW_HPP_
