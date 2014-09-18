/*
 * sdl_window.cpp
 *
 *  Created on: 19.09.2014
 *      Author: keks
 */

#include "sdl_window.hpp"

namespace mae
{
	namespace demo
	{
		//static members
		std::vector<sdl_window*> sdl_window::windows_;
		std::thread sdl_window::thread_;
		bool sdl_window::initialized_ = false;

		//methods

		sdl_window::sdl_window(std::string title, int width, int height, int x_pos, int y_pos, Uint32 flags)
		{
			title_ = title;

			if (windows_.size() == 0)
			{
				windows_.push_back(this);

				thread_ = std::thread(sdl_run);

				//wait until SDL is initialized
				while(!initialized_);
			}

			window_ = SDL_CreateWindow(title.c_str(), x_pos, y_pos, width,
					height, flags);
		}

		sdl_window::~sdl_window()
		{
			remove_window(this);

			SDL_DestroyWindow(window_);
			window_ = nullptr;
		}

		void sdl_window::set_title(std::string title)
		{
			title_ = title;
			SDL_SetWindowTitle(window_, title_.c_str());
		}

		std::string sdl_window::get_title()
		{
			return title_;
		}

		void sdl_window::set_width(int width)
		{
			SDL_SetWindowSize(window_, width, get_height());
		}

		int sdl_window::get_width()
		{
			int width;
			int height;

			SDL_GetWindowSize(window_, &width, &height);

			return width;
		}

		void sdl_window::set_height(int height)
		{
			SDL_SetWindowSize(window_, get_width(), height);
		}

		int sdl_window::get_height()
		{
			int width;
			int height;

			SDL_GetWindowSize(window_, &width, &height);

			return width;
		}

		void sdl_window::set_size(int width, int height)
		{
			SDL_SetWindowSize(window_, width, height);
		}

		SDL_Window* sdl_window::get()
		{
			return window_;
		}

		void sdl_window::handle_event(SDL_Event& e)
		{
			//TODO handle event
		}

		void sdl_window::paint(SDL_Surface* graphics)
		{
			//TODO do painting in here...
		}

		void sdl_window::repaint()
		{
			SDL_Surface* screen_surface = SDL_GetWindowSurface(window_);

			//TODO if background defined, draw on surface here...

			paint(screen_surface);

			SDL_UpdateWindowSurface(window_);
		}


		void sdl_window::remove_window(sdl_window* window)
		{
			for (std::vector<sdl_window*>::iterator it = windows_.begin(); it != windows_.end(); it++)
			{
				if (*it == window)
				{
					windows_.erase(it);
				}
			}
		}

		void sdl_window::sdl_run()
		{
			if (!SDL_WasInit(SDL_INIT_VIDEO))
			{
				if (SDL_Init(SDL_INIT_VIDEO) == -1)
				{
					throw std::invalid_argument("Could not initialize SDL");
				}
			}

			initialized_ = true;

			while (windows_.size() > 0)
			{
				//poll events. this keeps the windows alive
				SDL_Event event;
				while (SDL_PollEvent(&event))
				{
					//notify windows
					for (unsigned int i= 0; i < windows_.size(); i++)
					{
						windows_.at(i)->handle_event(event);
					}
				}

				SDL_Delay(50);
			}

			SDL_Quit();
			initialized_ = false;
		}

	} // namespace demo
} // namespace mae
