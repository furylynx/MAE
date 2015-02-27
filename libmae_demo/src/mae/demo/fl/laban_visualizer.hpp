/*
 * laban_visualizer.hpp
 *
 *  Created on: 20.09.2014
 *      Author: keks
 */

#ifndef LABAN_VISUALIZER_HPP_
#define LABAN_VISUALIZER_HPP_

//eclipse indexer fix
#include "../indexer_fix.hpp"

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
					 * @param format The pixel format to be applied.
					 */
					laban_visualizer(SDL_PixelFormat* format);

					/**
					 * Creates a new visualizer for laban sequences with a default pixel format.
					 */
					laban_visualizer();

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

					/**
					 * Prints the sequence to the png file.
					 *
					 * @param file The file to be printed to.
					 * @param sequence The sequence to be printed.
					 * @param window_width The image width.
					 * @param window_height The image height.
					 */
					virtual void bmp(std::string file, std::shared_ptr<mae::fl::laban::laban_sequence> sequence, int width = 1920, int height = 1080);

				private:
					std::shared_ptr<res::directions_handler> directions_handler_;
					SDL_PixelFormat* format_;

					bool free_format_;

					/**
					 * Draws the staff on the graphics.
					 *
					 * @param graphics The graphics component.
					 * @param sequence The sequence.
					 * @param window_width The window width.
					 * @param window_height The window height.
					 * @param max_column_index The maximum column index.
					 */
					virtual void paint_staff(SDL_Surface* graphics, std::shared_ptr<mae::fl::laban::laban_sequence> sequence, int window_width, int window_height, int max_column_index);

					/**
					 * Draws the line on the graphics.
					 *
					 * @param graphics The graphics component.
					 * @param from_x x1.
					 * @param from_y y1.
					 * @param to_x x2.
					 * @param to_y y2.
					 */
					virtual void draw_line(SDL_Surface* graphics, int from_x, int from_y, int to_x, int to_y);
			};

		} // namespace fl
	} // namespace demo
} // namespace mae

#endif // LABAN_VISUALIZER_HPP_
