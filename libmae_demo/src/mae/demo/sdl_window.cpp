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
		bool sdl_window::initialized_ = false;

		//methods

		sdl_window::sdl_window(std::string title, int width, int height, int x_pos, int y_pos, Uint32 flags)
		{
			repaint_requested_ = false;
			title_ = title;

			if (!initialized_)
			{
				if (!SDL_WasInit(SDL_INIT_VIDEO))
				{
					if (SDL_Init(SDL_INIT_VIDEO) != 0)
					{
						throw std::runtime_error("Could not initialize SDL.");
					}
				}

				if (!TTF_WasInit())
				{
					if (TTF_Init() != 0)
					{
						SDL_Quit();
						throw std::runtime_error("Could not initialize SDL_ttf.");
					}
				}

				initialized_ = true;
			}

			window_ = SDL_CreateWindow(title_.c_str(), x_pos, y_pos, width, height, flags);

			if (window_ == nullptr)
			{
				throw std::runtime_error("Could not initialize the window.");
			}

			windows_.push_back(this);

			//paint white background
			SDL_Surface* screen_surface = SDL_GetWindowSurface(window_);

			if (screen_surface != nullptr)
			{
				SDL_Rect bg_os;
				bg_os.x = 0;
				bg_os.y = 0;
				bg_os.w = get_width();
				bg_os.h = get_height();
				SDL_FillRect(screen_surface, &bg_os, 0xFFFFFFFF);

				SDL_UpdateWindowSurface(window_);
			}

			repaint();
		}

		sdl_window::~sdl_window()
		{
			if (!is_closed())
			{
				close();

				remove_window(this);
			}

			if (windows_.size() == 0)
			{
				TTF_Quit();
				SDL_Quit();
				initialized_ = false;
			}
		}

		void sdl_window::set_title(std::string title)
		{
			title_ = title;

			if (window_ != nullptr)
			{
				SDL_SetWindowTitle(window_, title_.c_str());
			}
		}

		std::string sdl_window::get_title() const
		{
			return title_;
		}

		void sdl_window::set_width(int width)
		{
			if (window_ != nullptr)
			{
				SDL_SetWindowSize(window_, width, get_height());
			}
		}

		int sdl_window::get_width() const
		{
			int width = 0;
			int height = 0;

			if (window_ != nullptr)
			{
				SDL_GetWindowSize(window_, &width, &height);
			}

			return width;
		}

		void sdl_window::set_height(int height)
		{
			if (window_ != nullptr)
			{
				SDL_SetWindowSize(window_, get_width(), height);
			}
		}

		int sdl_window::get_height() const
		{
			int width;
			int height;

			if (window_ != nullptr)
			{
				SDL_GetWindowSize(window_, &width, &height);
			}

			return height;
		}

		void sdl_window::set_size(int width, int height)
		{
			if (window_ != nullptr)
			{
				SDL_SetWindowSize(window_, width, height);
			}
		}

		SDL_Window* sdl_window::get() const
		{
			return window_;
		}

		SDL_Surface* sdl_window::get_surface() const
		{
			if (window_ != nullptr)
			{
				return SDL_GetWindowSurface(window_);
			}
			else
			{
				return nullptr;
			}
		}

		void sdl_window::handle_event(SDL_Event& e)
		{
			//handle event - override for functionality
		}

		void sdl_window::paint(SDL_Surface* graphics)
		{
			//do painting in here - override for functionality
		}

		void sdl_window::repaint()
		{
			repaint_requested_ = true;
		}

		bool sdl_window::is_repaint_requested() const
		{
			return repaint_requested_;
		}

		void sdl_window::do_repaint()
		{
			repaint_requested_ = false;

			if (window_ != nullptr)
			{
				SDL_Surface* screen_surface = SDL_GetWindowSurface(window_);

				if (screen_surface != nullptr)
				{
					paint(screen_surface);
					SDL_UpdateWindowSurface(window_);
				}
				else
				{
					repaint_requested_ = true;
				}
			}
		}

		void sdl_window::close()
		{
			SDL_DestroyWindow(window_);
			window_ = nullptr;
		}

		bool sdl_window::is_closed() const
		{
			return (window_ == nullptr);
		}

		void sdl_window::remove_window(sdl_window* window)
		{
			if (nullptr != window)
			{
				for (std::vector<sdl_window*>::iterator it = windows_.begin(); it != windows_.end();)
				{
					if (*it == window)
					{
						it = windows_.erase(it);
					}
					else
					{
						it++;
					}
				}
			}
		}

		void sdl_window::update()
		{
			if (windows_.size() > 0)
			{

				//poll events. this keeps the windows alive
				SDL_Event event;
				while (SDL_PollEvent(&event))
				{
					//notify windows
					for (unsigned int i = 0; i < windows_.size(); i++)
					{
						if (windows_.at(i) != nullptr)
						{
							windows_.at(i)->handle_event(event);
						}
					}

					if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)
					{
						for (unsigned int i = 0; i < windows_.size(); i++)
						{
							if (windows_.at(i) != nullptr && windows_.at(i)->get() != nullptr && event.window.windowID == SDL_GetWindowID(windows_.at(i)->get()))
							{
								windows_.at(i)->close();
							}
						}
					}
				}

				for (unsigned int i = 0; i < windows_.size(); i++)
				{
					if (windows_.at(i) != nullptr && windows_.at(i)->is_repaint_requested())
					{
						windows_.at(i)->do_repaint();
					}
				}
			}
		}

	} // namespace demo
} // namespace mae
