/*
 * sdl_window.hpp
 *
 *  Created on: 19.09.2014
 *      Author: keks
 */

#ifndef SDL_WINDOW_HPP_
#define SDL_WINDOW_HPP_

//eclipse indexer fix
#include "indexer_fix.hpp"

//custom includes
#include "sdl_window_item.hpp"

//global includes
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <thread>
#include <mutex>

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
				 * Must be invoked from the main thread.
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
				virtual std::string get_title() const;

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
				virtual int get_width() const;

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
				virtual int get_height() const;

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
				 * Returns true if a repaint was requested recently.
				 *
				 * @return True if repaint was requested.
				 */
				virtual bool is_repaint_requested() const;

				/**
				 * Returns the pointer to the SDL_WINDOW which remains valid until this object gets destroyed.
				 *
				 * @return A pointer to the window.
				 */
				virtual SDL_Window* get() const;

				/**
				 * Returns the pointer to the window's surface.
				 * @return
				 */
				virtual SDL_Surface* get_surface() const;

				/**
				 * Closes the window.
				 */
				virtual void close();

				/**
				 * Returns true if the window is closed.
				 *
				 * @return True if closed
				 */
				virtual bool is_closed() const;

				/**
				 * Updates all living windows. This includes polling events as well as repaint jobs.
				 *
				 * This method must be invoked from the main thread of the program.
				 *
				 */
				static void update();

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


				/**
				 * Does the actual repainting job.
				 *
				 */
				virtual void do_repaint();

			private:
				std::string title_;
				SDL_Window* window_;

				bool repaint_requested_;


				//****************
				// static
				//****************
				static std::vector<sdl_window*> windows_;
				static bool initialized_;

				/**
				 * Clears the window.
				 *
				 * @param window The window.
				 */
				static void remove_window(sdl_window* window);

		};

	} // namespace demo
} // namespace mae

#endif // SDL_WINDOW_HPP_
