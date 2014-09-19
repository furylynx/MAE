/*
 * sequence_window.hpp
 *
 *  Created on: 19.09.2014
 *      Author: keks
 */

#ifndef SEQUENCE_WINDOW_HPP_
#define SEQUENCE_WINDOW_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
#include "../sdl_window.hpp"

//global includes
#include <string>
#include <memory>

#include <mae/mae.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace mae
{
	namespace demo
	{
		namespace fl
		{

			class sequence_window : public sdl_window, public mae::i_sequence_listener<mae::fl::laban::laban_sequence>
			{
				public:
					sequence_window(std::string title, std::string resources_dir, int width = 1024, int height = 576, int x_pos = SDL_WINDOWPOS_UNDEFINED, int y_pos = SDL_WINDOWPOS_UNDEFINED, Uint32 flags = SDL_WINDOW_SHOWN);
					virtual ~sequence_window();

				protected:
					virtual void paint(SDL_Surface* graphics);
					virtual void handle_event(SDL_Event& e);


				private:

					std::string resources_dir_;
					std::shared_ptr<mae::fl::laban::laban_sequence> current_sequence_;

					SDL_Surface* background_;
					std::vector<SDL_Surface*> directions_;

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

#endif // SEQUENCE_WINDOW_HPP_
