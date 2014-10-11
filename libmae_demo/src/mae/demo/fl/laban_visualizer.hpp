/*
 * laban_visualizer.hpp
 *
 *  Created on: 20.09.2014
 *      Author: keks
 */

#ifndef LABAN_VISUALIZER_HPP_
#define LABAN_VISUALIZER_HPP_

//eclipse indexer fix
#include "../../indexer_fix.hpp"

//custom includes
#include "res/res.hpp"

//global includes
#include <memory>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <mae/mae.hpp>


namespace mae
{
	namespace demo
	{
		namespace fl
		{

			class laban_visualizer
			{
				public:
					/**
					 * Creates a new visualizer for laban sequences.
					 *
					 * @param resources_dir The resources directory containing images for dir+lvl of laban.
					 * @param format The pixel format to be applied.
					 */
					laban_visualizer(SDL_PixelFormat* format);
					virtual ~laban_visualizer();

					/**
					 * Paints the sequence to the graphics surface.
					 *
					 * @param graphics The surface to be drawn on.
					 * @param sequence The sequence to be drawn.
					 * @param window_width The window's width.
					 * @param window_height The window's height.
					 */
					virtual void paint_sequence(SDL_Surface* graphics, std::shared_ptr<mae::fl::laban::laban_sequence> sequence, int window_width, int window_height);

				private:
					std::shared_ptr<res::directions_handler> directions_handler_;
					SDL_PixelFormat* format_;

			};

		} // namespace fl
	} // namespace demo
} // namespace mae

#endif // LABAN_VISUALIZER_HPP_
