/*
 * directions_handler.hpp
 *
 *  Created on: 12.10.2014
 *      Author: keks
 */

#ifndef DIRECTIONS_HANDLER_HPP_
#define DIRECTIONS_HANDLER_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
#include "res.hpp"

//global includes
#include <mae/mae.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace mae
{
	namespace demo
	{
		namespace fl
		{
			namespace res
			{

				class directions_handler
				{
					public:
						/**
						 * Creates a new handler for the direction images.
						 *
						 * @param format The pixel format to be applied.
						 */
						directions_handler(SDL_PixelFormat* format);
						virtual ~directions_handler();

						/**
						 * Returns the image surface for the direction symbol for further processing.
						 *
						 * @param direction The direction.
						 * @return The surface.
						 */
						virtual SDL_Surface* get_direction_image(unsigned int direction);

						/**
						 * Returns the image surface for the direction symbol for further processing.
						 *
						 * @param direction The direction.
						 * @return The surface.
						 */
						virtual SDL_Surface* get_direction_image(mae::fl::e_fl_direction direction);

						/**
						 * Returns the number of images registered to the handler.
						 *
						 * @return The number of registered images.
						 */
						virtual unsigned int size();

					private:
						std::vector<SDL_Surface*> directions_;
						SDL_PixelFormat* format_;

						/**
						 * Loads the media for the visualizer.
						 */
						virtual void initialize();

						/**
						 * Performs a cleanup on the media.
						 */
						virtual void cleanup();

				};

			} // namespace res
		} // namespace fl
	} // namespace demo
} // namespace mae

#endif // DIRECTIONS_HANDLER_HPP_
