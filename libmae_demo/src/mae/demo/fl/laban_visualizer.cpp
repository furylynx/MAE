/*
 * laban_visualizer.cpp
 *
 *  Created on: 20.09.2014
 *      Author: keks
 */

#include "laban_visualizer.hpp"

namespace mae
{
	namespace demo
	{
		namespace fl
		{

			laban_visualizer::laban_visualizer(SDL_PixelFormat* format)
			{
				format_ = format;

				directions_handler_ = std::shared_ptr<res::directions_handler>(new res::directions_handler(format));
			}

			laban_visualizer::~laban_visualizer()
			{
			}

			void laban_visualizer::paint_sequence(SDL_Surface* graphics,
					std::shared_ptr<mae::fl::laban::laban_sequence> sequence, int window_width, int window_height)
			{
				std::vector<int> columns = sequence->get_columns();

				int max_index = std::abs(columns.at(0));
				if (std::abs(columns.back()) > max_index)
				{
					max_index = columns.back();
				}

				for (unsigned int i = 0; i < columns.size(); i++)
				{
					//draw by column
					int column = columns.at(i);
					int draw_x_pos = (int) ((window_width - 100) * (0.5 + (double) (column) / (max_index * 2)) + 20);

					std::vector<std::shared_ptr<mae::fl::laban::i_movement> > movements =
							sequence->get_column_movements(column);

					for (unsigned int j = 0; j < movements.size(); j++)
					{
						if (std::shared_ptr<mae::fl::laban::movement> mov = std::dynamic_pointer_cast<
								mae::fl::laban::movement>(movements.at(j)))
						{
							if (std::shared_ptr<mae::fl::laban::mv::direction_symbol> symb = std::dynamic_pointer_cast<
									mae::fl::laban::mv::direction_symbol>(mov->get_symbol()))
							{
								int draw_y_pos = (int) ((window_height - 50)
										* (1
												- ((mov->get_measure() * sequence->get_beats() + mov->get_beat()
														+ mov->get_duration())
														/ (sequence->get_measures() * sequence->get_beats()))));
								int draw_h = (int) ((window_height - 50)
										* (mov->get_duration() / (sequence->get_measures() * sequence->get_beats())));

								unsigned int direction = mae::fl::e_fl_direction_c::to_int(
										mae::fl::e_fl_direction_c::dir(symb->get_horizontal(), symb->get_vertical(),
												(column < 0)));

								if (direction < directions_handler_->size() && direction > 0)
								{
									SDL_Surface* direction_surface = directions_handler_->get_direction_image(direction);

									//apply direction for all body parts
									SDL_Rect offset_scale;
									offset_scale.x = draw_x_pos;
									offset_scale.y = draw_y_pos;

									offset_scale.w = (int) (direction_surface->w * (double) window_width / 1920.0);
									offset_scale.h = draw_h;

									//Blit the surface
									SDL_BlitScaled(direction_surface, NULL, graphics, &offset_scale);

								}
							}
						}
					}
				}
			}

		} // namespace fl
	} // namespace demo
} // namespace mae
