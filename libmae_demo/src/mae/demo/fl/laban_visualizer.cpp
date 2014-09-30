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

			laban_visualizer::laban_visualizer(std::string resources_dir, SDL_PixelFormat* format)
			{
				resources_dir_ = resources_dir;
				format_ = format;

				initialize();
			}

			laban_visualizer::~laban_visualizer()
			{
				cleanup();
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
												- ((mov->get_measure() * sequence->get_beats()
														+ mov->get_beat() + mov->get_duration())
														/ (sequence->get_measures()
																* sequence->get_beats()))));
								int draw_h = (int) ((window_height - 50)
										* (mov->get_duration()
												/ (sequence->get_measures() * sequence->get_beats())));

								unsigned int direction = mae::fl::e_fl_direction_c::to_int(
										mae::fl::e_fl_direction_c::dir(symb->get_horizontal(), symb->get_vertical(),
												(column < 0)));

								if (direction <= directions_.size() && direction > 0)
								{
									SDL_Surface* direction_surface = directions_.at(direction - 1);

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

			void laban_visualizer::initialize()
			{
				//Loading success flag
				bool success = true;

				//load all other directions (33 images)
				std::vector<mae::fl::e_fl_direction> fl_dirs = mae::fl::e_fl_direction_c::vec();
				for (unsigned int i = 0; i < fl_dirs.size(); i++)
				{
					std::cout << i << std::endl;

					if (fl_dirs.at(i) == mae::fl::e_fl_direction::INVALID)
					{
						continue;
					}

					//load direction png image
//					std::stringstream d_sstr;
//					d_sstr << resources_dir_;
//					d_sstr << "laban_direction" << mae::fl::e_fl_direction_c::to_int(fl_dirs.at(i)) << ".png";

//					SDL_Surface* png_sur = IMG_Load(d_sstr.str().c_str());

					mae_res res = res::laban_res.at(i-1);
					SDL_Surface* png_sur = IMG_LoadTyped_RW(SDL_RWFromConstMem(res.data, res.size), 1, "PNG");

					if (png_sur == nullptr)
					{
						//failed to load, therefore break, do cleanup and throw exception
						success = false;
						break;
					}
					else
					{
						SDL_Surface* sur = SDL_ConvertSurface(png_sur, format_, 0);

						//Get rid of old loaded surface
						SDL_FreeSurface(png_sur);
						png_sur = nullptr;

						if (sur == nullptr)
						{
							//failed to load, therefore break, do cleanup and throw exception
							success = false;
							break;
						}
						else
						{
							//add surface to list
							directions_.push_back(sur);
						}
					}
				}

				if (!success)
				{
					cleanup();
					std::stringstream e_sstr;
					e_sstr << "Could not load the resources from " << resources_dir_ << std::endl;

					throw std::runtime_error(e_sstr.str());
				}
			}

			void laban_visualizer::cleanup()
			{
				for (unsigned int i = 0; i < directions_.size(); i++)
				{
					if (directions_.at(i) != nullptr)
					{
						SDL_FreeSurface(directions_.at(i));
					}
				}

				directions_.clear();
			}


		} // namespace fl
	} // namespace demo
} // namespace mae
