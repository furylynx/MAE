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
#include <SDL2/SDL_ttf.h>

namespace mae
{
	namespace demo
	{

		class sdl_window
		{
			public:
				/**
				 * Creates a new SDL window.
				 *
				 * @param title The window title.
				 * @param width The window's width.
				 * @param height The window's height.
				 * @param x_pos The window's x position.
				 * @param y_pos The window's y position.
				 * @param flags The window flags.
				 */
				sdl_window(std::string title, int width, int height, int x_pos = SDL_WINDOWPOS_UNDEFINED, int y_pos = SDL_WINDOWPOS_UNDEFINED, Uint32 flags = SDL_WINDOW_SHOWN);
				virtual ~sdl_window();

				/**
				 * Sets the window title.
				 *
				 * @param title The title.
				 */
				virtual void set_title(std::string title);

				/**
				 * Returns the window title.

				 * @return The title.
				 */
				virtual std::string get_title();

				/**
				 * Returns the window's width.
				 *
				 * @param width The width.
				 */
				virtual void set_width(int width);

				/**
				 * Returns the window's height.
				 *
				 * @return The height.
				 */
				virtual int get_width();

				/**
				 * Sets the window's height.
				 *
				 * @param height The height.
				 */
				virtual void set_height(int height);

				/**
				 * Returns the window's height.
				 *
				 * @return The height.
				 */
				virtual int get_height();

				/**
				 * Sets the window size.
				 *
				 * @param width The width to be applied.
				 * @param height The height to be applied.
				 */
				void set_size(int width, int height);

				/**
				 * Repaints the window's content. Invokes the paint method.
				 */
				virtual void repaint();

				/**
				 * Returns the pointer to the SDL_WINDOW which remains valid until this object gets destroyed.
				 *
				 * @return A pointer to the window.
				 */
				virtual SDL_Window* get();

				/**
				 * Returns the pointer to the window's surface.
				 * @return
				 */
				virtual SDL_Surface* get_surface();

			protected:
				/**
				 * Handles the given event.
				 *
				 * @param e The event.
				 */
				virtual void handle_event(SDL_Event& e);

				/**
				 * Paints content to the graphics element.
				 *
				 * @param graphics The graphics element.
				 */
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
				static bool exception_;

				/**
				 * Clears the window.
				 *
				 * @param window The window.
				 */
				static void remove_window(sdl_window* window);

				/**
				 * The window thread.
				 */
				static void sdl_run();
		};

	} // namespace demo
} // namespace mae

#endif // SDL_WINDOW_HPP_
