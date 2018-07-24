/*
 * laban_visualizer.cpp
 *
 *  Created on: 20.09.2014
 *      Author: furylynx
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
				free_format_ = false;
				format_ = format;

				directions_handler_ = std::shared_ptr<res::directions_handler>(new res::directions_handler(format_));
			}

			laban_visualizer::laban_visualizer()
			{
				free_format_ = true;

				format_ = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

				try
				{
					directions_handler_ = std::shared_ptr<res::directions_handler>(new res::directions_handler(format_));
				}
				catch(std::exception& e)
				{
					//free allocated format
					SDL_FreeFormat(format_);

					throw e;
				}
				catch (...)
				{
					//free allocated format
					SDL_FreeFormat(format_);

					throw std::runtime_error("Could not initialize the directions handler.");
				}

			}

			laban_visualizer::~laban_visualizer()
			{
				if (free_format_)
				{
					SDL_FreeFormat(format_);
				}
			}


            void laban_visualizer::paint_sequence(SDL_Surface* graphics,
                                                      std::shared_ptr<mae::fl::laban::laban_sequence> sequence, int window_width, int window_height) const
            {

                std::string svgstring = sequence->svg(window_width, window_height);
                SDL_RWops *rw = SDL_RWFromConstMem(svgstring.c_str(), svgstring.length());

                SDL_Surface* tmp = IMG_LoadSVG_RW(rw);

                SDL_BlitSurface(tmp, NULL, graphics, NULL);

                //free the surface
                SDL_FreeSurface(tmp);
                tmp = nullptr;
            }


			void laban_visualizer::paint_sequence_raw(SDL_Surface* graphics,
					std::shared_ptr<mae::fl::laban::laban_sequence> sequence, int window_width, int window_height) const
			{
				std::vector<int> columns = sequence->get_columns();

				int max_index = std::abs(columns.at(0));
				if (std::abs(columns.back()) > max_index)
				{
					max_index = columns.back();
				}

				//paint the Labanotation staff
				paint_staff(graphics, sequence, window_width, window_height, max_index);

				int total_beats = (sequence->get_measures()+1) * sequence->get_beats();
				double beat_height = (window_height - 105) / total_beats;
				double column_width = (window_width - 100.0)/(max_index * 2.0);

				for (unsigned int i = 0; i < columns.size(); i++)
				{
					//draw by column
					int column = columns.at(i);
					int draw_x_pos = (int)((window_width / 2.0) + ((column - (mae::math::math::sign(column)*0.5))*column_width)) - 30;
					//(int) ((window_width - 100) * (0.5 + (double) (column) / (max_index * 2)) + 20);

					//TODO print pre-sign


					//print direction symbols
					std::vector<std::shared_ptr<mae::fl::laban::i_movement> > movements =
							sequence->get_column_movements(column);

					for (unsigned int j = 0; j < movements.size(); j++)
					{
						if (std::shared_ptr<mae::fl::laban::movement> mov = std::dynamic_pointer_cast<mae::fl::laban::movement>(movements.at(j)))
						{
							if (std::shared_ptr<mae::fl::laban::mv::direction_symbol> symb = std::dynamic_pointer_cast<
									mae::fl::laban::mv::direction_symbol>(mov->get_symbol()))
							{
								int draw_y_pos = 0;
								int draw_h = 0;

								if (mov->get_measure() != 0)
								{
									draw_y_pos = (int) (window_height - 50 - (mov->get_measure() * sequence->get_beats() + mov->get_beat()
																			+ mov->get_duration()) * beat_height) - 5;
									draw_h = (int) (beat_height * mov->get_duration());
								}
								else
								{
									draw_y_pos = (int) (window_height - 50 - (mov->get_measure() * sequence->get_beats() + mov->get_beat()
										+ sequence->get_beats()) * beat_height);
									draw_h = (int) (beat_height * sequence->get_beats());
								}


								unsigned int direction = mae::fl::e_fl_direction_c::to_int(
										mae::fl::e_fl_direction_c::dir(symb->get_horizontal(), symb->get_vertical(),
												(column < 0)));

								if (direction < directions_handler_->size() && direction > 0)
								{
									SDL_Surface* direction_surface = directions_handler_->get_direction_image(
											direction);

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

			void laban_visualizer::bmp(std::string file, std::shared_ptr<mae::fl::laban::laban_sequence> sequence, int width, int height) const
			{
				//generate surface
				SDL_Surface* surface = prepare_surface(sequence, width, height);

				//store surface as a file
				SDL_SaveBMP(surface, file.c_str());

				//free the surface
				SDL_FreeSurface(surface);
				surface = nullptr;
			}

			void laban_visualizer::png(std::string file, std::shared_ptr<mae::fl::laban::laban_sequence> sequence, int width, int height) const
			{
				//generate surface
				SDL_Surface* surface = prepare_surface(sequence, width, height);

				//store surface as a file
				IMG_SavePNG(surface, file.c_str());

				//free the surface
				SDL_FreeSurface(surface);
				surface = nullptr;
			}


			void laban_visualizer::jpeg(std::string file, std::shared_ptr<mae::fl::laban::laban_sequence> sequence, int width, int height) const
			{
				//generate surface
				SDL_Surface* surface = prepare_surface(sequence, width, height);

				//store surface as a file
				IMG_SaveJPG(surface, file.c_str(), 95);

				//free the surface
				SDL_FreeSurface(surface);
				surface = nullptr;
			}

			SDL_Surface* laban_visualizer::prepare_surface(std::shared_ptr<mae::fl::laban::laban_sequence> sequence, int width, int height) const
			{
				//generate surface
				SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, (int)format_->BitsPerPixel, format_->Rmask, format_->Gmask, format_->Bmask, format_->Amask);

				//white background
				SDL_Rect rect;
				rect.x = 0;
				rect.y = 0;
				rect.w = surface->w;
				rect.h = surface->h;
				SDL_FillRect(surface, &rect, 0xFFFFFFFF);

				//print sequence to the surface
				paint_sequence(surface, sequence, width, height);

				return surface;
			}

			void laban_visualizer::paint_staff(SDL_Surface* graphics,
					std::shared_ptr<mae::fl::laban::laban_sequence> sequence, int window_width, int window_height,
					int max_column_index) const
			{
				int total_beats = (sequence->get_measures()+1) * sequence->get_beats();
				double beat_height = (window_height - 105) / total_beats;
				double column_width = (window_width - 100)/(max_column_index * 2.0);

				//draw staff
				int left_bound = (int)((window_width / 2.0) - (2.0*column_width));
				int right_bound = (int)((window_width / 2.0) + (2.0*column_width));
				int bottom_bound = (window_height - 50);
				int top_bound = 50;
				int center = (int)(window_width / 2.0);

				//bottom line
				draw_line(graphics, left_bound, bottom_bound, right_bound, bottom_bound);

				//top line
				draw_line(graphics,  left_bound, 50,  window_width / 2 + 2*column_width, 50);

				//draw movement start lines
				int start_line_y = (int)(window_height - 50 - (beat_height*sequence->get_beats()));
				draw_line(graphics, left_bound, start_line_y,  right_bound, start_line_y);
				draw_line(graphics, left_bound, start_line_y-5,  right_bound, start_line_y - 5);

				//draw center line
				draw_line(graphics, center, top_bound, center, bottom_bound);

				//draw right and left line
				draw_line(graphics, left_bound, top_bound, left_bound, bottom_bound);
				draw_line(graphics, right_bound, top_bound, right_bound, bottom_bound);

				//draw beat and measure marks
				for (unsigned int i = sequence->get_beats() + 1 ; i < (sequence->get_measures()+1) * sequence->get_beats(); i++)
				{
					int mark_pos_y = (int) (window_height - 55 - (i * beat_height));
					if ((i % sequence->get_beats()) == 0)
					{
						//is a measure -> more width
						draw_line(graphics, left_bound, mark_pos_y,  right_bound, mark_pos_y);
					}
					else
					{
						//is a beat -> less width
						draw_line(graphics, center-15, mark_pos_y,  center+15, mark_pos_y);
					}
				}
			}

			void laban_visualizer::draw_line(SDL_Surface* graphics, int from_x, int from_y, int to_x, int to_y) const
			{
				SDL_Rect tmp_rect;
				tmp_rect.x = from_x;
				tmp_rect.y = from_y;

				tmp_rect.h = to_y - from_y;
				if (tmp_rect.h == 0)
				{
					tmp_rect.h = 2;
				}

				tmp_rect.w = to_x - from_x;
				if (tmp_rect.w == 0)
				{
					tmp_rect.w = 2;
				}

				SDL_FillRect(graphics, &tmp_rect, 0);
			}

		} // namespace fl
	} // namespace demo
} // namespace mae
