/*
 * recognition_window.hpp
 *
 *  Created on: 20.09.2014
 *      Author: keks
 */

#ifndef RECOGNITION_WINDOW_HPP_
#define RECOGNITION_WINDOW_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
#include "laban_visualizer.hpp"

#include "res/res.hpp"

#include "../sdl_window.hpp"

//global includes
#include <string>
#include <memory>

#include <mae/mae.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace mae
{
	namespace demo
	{
		namespace fl
		{

			class recognition_window: public sdl_window, public mae::i_recognition_listener<
					mae::fl::laban::laban_sequence>
			{
				public:
					/**
					 * Creates a new SDL window for recognized laban_sequences with the given parameters.
					 *
					 * @param title The window title.
					 * @param backgroundimage True if background image is desired.
					 * @param width The window width.
					 * @param height The window height.
					 * @param x_pos The window's x position.
					 * @param y_pos The window's y position.
					 * @param flags The window flags.
					 */
					recognition_window(std::string title, bool backgroundimage = false, int width = 1024, int height = 576,
							int x_pos = SDL_WINDOWPOS_UNDEFINED, int y_pos = SDL_WINDOWPOS_UNDEFINED, Uint32 flags =
									SDL_WINDOW_SHOWN);
					virtual ~recognition_window();

					/**
					 * Is invoked each time sequences were recognized and the sequences are present.
					 *
					 * @param timestamp The associated timestamp.
					 * @param sequences The recognized sequences.
					 */
					virtual void on_recognition(long timestamp, std::vector<std::shared_ptr<mae::fl::laban::laban_sequence> > sequences);

					/**
					 * Is invoked each time sequences were recognized and only titles of the sequences are present.
					 *
					 * @param timestamp The associated timestamp.
					 * @param sequences The recognized sequences.
					 */
					virtual void on_recognition(long timestamp, std::vector<std::string> title);

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
					std::shared_ptr<laban_visualizer> visualizer_;

					std::shared_ptr<mae::fl::laban::laban_sequence> current_sequence_;
					std::string current_sequence_title_;

					SDL_Surface* background_;
					bool backgroundimage_;

					const SDL_Color TEXTCOLOR = {0xe1, 0x71, 0x00, 0xff};

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

#endif // RECOGNITION_WINDOW_HPP_
