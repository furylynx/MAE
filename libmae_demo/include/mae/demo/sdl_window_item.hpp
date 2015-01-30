/*
 * sdl_window_item.hpp
 *
 *  Created on: 04.11.2014
 *      Author: keks
 */

#ifndef SDL_WINDOW_ITEM_HPP_
#define SDL_WINDOW_ITEM_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

//custom includes
//...

//global includes
#include <string>

#include <SDL2/SDL.h>

namespace mae
{
	namespace demo
	{

				class sdl_window_item
				{
					public:
						sdl_window_item(std::string title, int width, int height, int x_pos, int y_pos, Uint32 flags);
						virtual ~sdl_window_item();

						virtual std::string get_title();
						virtual int get_width();
						virtual int get_height();
						virtual int get_x_pos();
						virtual int get_y_pos();
						virtual Uint32 get_flags();

						virtual bool created();
						virtual bool exception();

						virtual void set_exception(bool exception);
						virtual void set_created(bool created);

					private:
						std::string title_;
						int width_;
						int height_;
						int x_pos_;
						int y_pos_;
						Uint32 flags_;

						bool created_;
						bool exception_;

				};

	} // namespace demo
} // namespace mae

#endif // SDL_WINDOW_ITEM_HPP_
