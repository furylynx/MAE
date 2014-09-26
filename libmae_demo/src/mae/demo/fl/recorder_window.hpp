/*
 * recorder_window.hpp
 *
 *  Created on: 28.09.2014
 *      Author: keks
 */

#ifndef RECORDER_WINDOW_HPP_
#define RECORDER_WINDOW_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
#include "../sdl_window.hpp"
#include "laban_visualizer.hpp"

//global includes
#include <mae/mae.hpp>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace mae
{
	namespace demo
	{
		namespace fl
		{

			class recorder_window : public sdl_window, public i_sequence_listener<mae::fl::laban::laban_sequence>
			{
				public:
					/**
					 * Creates a new recorder window to print countdowns and the currently recorded sequence.
					 *
					 * @param title The window title.
					 * @param resources_dir The resources path.
					 * @param font_path The font path.
					 * @param width The width.
					 * @param height The height.
					 * @param x_pos The x pos.
					 * @param y_pos The y pos.
					 * @param flags The flags to be applied.
					 */
					recorder_window(std::string title, std::string resources_dir, std::string font_path, int width = 1024, int height = 576, int x_pos = SDL_WINDOWPOS_UNDEFINED, int y_pos = SDL_WINDOWPOS_UNDEFINED, Uint32 flags = SDL_WINDOW_SHOWN);
					virtual ~recorder_window();

					/**
					 * Updates the countdown. If the countdown is -1 the drawing will be cleared.
					 * @param time_left
					 */
					virtual void update_countdown(int time_left);

					/**
					 * Clears the graphics and removes the current sequence.
					 *
					 */
					virtual void clear_paint();

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

					std::string resources_dir_;
					std::shared_ptr<mae::fl::laban::laban_sequence> current_sequence_;

					int countdown_;

					SDL_Surface* background_;
					TTF_Font* small_font_;
					TTF_Font* big_font_;
					std::string font_str_;

					const char* wait_str = "Waiting for user...";
					const SDL_Color text_color = {0xe1, 0x71, 0x00, 0xff};

					/**
					 * Initializes all required surfaces. May fail with an exception, but will release all surface before this.
					 */
					virtual void initialize();

					/**
					 * Runs a cleanup which frees all allocated surfaces.
					 */
					virtual void cleanup();

					/**
					 * Is invoked each time a sequence was generated (which occurs on every frame).
					 *
					 * @param timestamp The associated timestamp.
					 * @param sequence The generated sequence.
					 */
					virtual void on_sequence(long timestamp, std::shared_ptr<mae::fl::laban::laban_sequence> sequence);
			};

		} // namespace fl
	} // namespace demo
} // namespace mae

#endif // RECORDER_WINDOW_HPP_
