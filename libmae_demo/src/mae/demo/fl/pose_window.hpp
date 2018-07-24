/*
 * pose_window.hpp
 *
 *  Created on: 12.10.2014
 *      Author: furylynx
 */

#ifndef POSE_WINDOW_HPP_
#define POSE_WINDOW_HPP_

//custom includes
#include "../sdl_window.hpp"

#include "res/res.hpp"

//global includes
#include <string>
#include <memory>

#include <mae/mae.hpp>


#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

namespace mae
{
	namespace demo
	{
		namespace fl
		{

		class pose_window: public sdl_window, public mae::i_pose_listener
		{
			public:
				/**
				 * Creates a window which shows poses for the input stream.
				 *
				 * @param title The window title.
				 * @param backgroundimage True if background image is desired.
				 * @param width The window's width.
				 * @param height The window's height.
				 * @param x_pos The x position.
				 * @param y_pos The y position.
				 * @param flags The window flags.
				 */
				pose_window(std::string title, bool backgroundimage = false, int width = 1024, int height = 576, int x_pos = SDL_WINDOWPOS_UNDEFINED, int y_pos = SDL_WINDOWPOS_UNDEFINED, Uint32 flags = SDL_WINDOW_SHOWN);
				virtual ~pose_window();

				/**
				 * Is invoked each time a pose was quantized (which occurs on every frame).
				 *
				 * @param timestamp The associated timestamp.
				 * @param pose The quantized pose.
				 */
				virtual void on_pose(uint64_t timestamp, std::shared_ptr<general_pose> pose);

			protected:
				/**
				 * Handles the given event.
				 *
				 * @param e The event.
				 */
				virtual void paint(SDL_Surface* graphics);

				/**
				 * Paints content to the graphics element.
				 *
				 * @param graphics The graphics element.
				 */
				virtual void handle_event(SDL_Event& e);

			private:
				std::shared_ptr<res::directions_handler> directions_handler_;
				std::shared_ptr<mae::general_pose> current_pose_;

				SDL_Surface* background_;
				bool backgroundimage_;


				/**
				 * Initializes all required surfaces. May fail with an exception, but will release all surface before this.
				 */
				virtual void initialize();

				/**
				 * Runs a cleanup which frees all allocated surfaces.
				 */
				virtual void cleanup();

		};

		} // namespace fl
	} // namespace demo
} // namespace mae

#endif // POSE_WINDOW_HPP_
