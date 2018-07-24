/*
 * sdl_window_item.cpp
 *
 *  Created on: 04.11.2014
 *      Author: furylynx
 */

#include "sdl_window_item.hpp"

namespace mae
{
	namespace demo
	{

		sdl_window_item::sdl_window_item(std::string title, int width, int height, int x_pos, int y_pos, Uint32 flags)
		{
			title_ = title;
			width_ = width;
			height_ = height;
			x_pos_ = x_pos;
			y_pos_ = y_pos;
			flags_ = flags;

			created_ = false;
			exception_ = false;
		}

		sdl_window_item::~sdl_window_item()
		{

		}

		std::string sdl_window_item::get_title()
		{
			return title_;
		}

		int sdl_window_item::get_width()
		{
			return width_;
		}

		int sdl_window_item::get_height()
		{
			return height_;
		}

		int sdl_window_item::get_x_pos()
		{
			return x_pos_;
		}

		int sdl_window_item::get_y_pos()
		{
			return y_pos_;
		}

		Uint32 sdl_window_item::get_flags()
		{
			return flags_;
		}

		bool sdl_window_item::created()
		{
			return created_;
		}

		bool sdl_window_item::exception()
		{
			return exception_;
		}

		void sdl_window_item::set_exception(bool exception)
		{
			exception_ = exception;
		}

		void sdl_window_item::set_created(bool created)
		{
			created_ = created;
		}

	} // namespace demo
} // namespace mae
