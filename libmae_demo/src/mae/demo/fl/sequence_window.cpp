/*
 * sequence_window.cpp
 *
 *  Created on: 19.09.2014
 *      Author: keks
 */

#include "sequence_window.hpp"

namespace mae
{
	namespace demo
	{
		namespace fl
		{

			sequence_window::sequence_window(std::string title, std::string resources_dir, int width, int height,
					int x_pos, int y_pos, Uint32 flags)
					: sdl_window(title, width, height, x_pos, y_pos, flags)
			{
				if (resources_dir.at(resources_dir.size() - 1) != mae::mos::path_separator())
				{
					resources_dir.insert(resources_dir.end(), mae::mos::path_separator());
				}

				resources_dir_ = resources_dir;
				background_ = nullptr;

				initialize();
			}

			sequence_window::~sequence_window()
			{
			}

			void sequence_window::initialize()
			{
				std::stringstream bg_sstr;
				bg_sstr << resources_dir_;
				bg_sstr << "background0.png";

				//load background png image
				SDL_Surface* loaded_surface = IMG_Load(bg_sstr.str().c_str());

				if (loaded_surface != nullptr)
				{
					background_ = SDL_ConvertSurface(loaded_surface, get_surface()->format, 0);

					//Get rid of old loaded surface
					SDL_FreeSurface(loaded_surface);
					loaded_surface = nullptr;

					if (background_ == nullptr)
					{
						std::stringstream e_sstr;
						e_sstr << "Unable to optimize image " << bg_sstr.str() << "! SDL Error: " << SDL_GetError()
								<< std::endl;
						throw std::runtime_error(e_sstr.str());
					}
				}
				else
				{
					std::stringstream e_sstr;
					e_sstr << "Unable to load image " << bg_sstr.str() << "! SDL Error: " << SDL_GetError()
							<< std::endl;
					throw std::runtime_error(e_sstr.str());
				}

				//Loading success flag
				bool success = true;

				//load all other directions (33 images)
				std::vector<mae::fl::e_fl_direction> fl_dirs = mae::fl::e_fl_direction_c::vec();
				for (unsigned int i = 0; i < fl_dirs.size(); i++)
				{
					if (fl_dirs.at(i) == mae::fl::e_fl_direction::INVALID)
					{
						continue;
					}

					//load direction png image
					std::stringstream d_sstr;
					d_sstr << resources_dir_;
					d_sstr << "laban_direction" << mae::fl::e_fl_direction_c::to_int(fl_dirs.at(i)) << ".png";

					SDL_Surface* png_sur = IMG_Load(d_sstr.str().c_str());

					if (png_sur == nullptr)
					{
						//failed to load, therefore break, do cleanup and throw exception
						success = false;
						break;
					}
					else
					{
						SDL_Surface* sur = SDL_ConvertSurface(png_sur, get_surface()->format, 0);

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

				repaint();
			}

			void sequence_window::cleanup()
			{
				if (background_ != nullptr)
				{
					SDL_FreeSurface(background_);
					background_ = nullptr;
				}

				for (unsigned int i = 0; i < directions_.size(); i++)
				{
					if (directions_.at(i) != nullptr)
					{
						SDL_FreeSurface(directions_.at(i));
						background_ = nullptr;
					}
				}
			}

			void sequence_window::paint(SDL_Surface* graphics)
			{
				//Apply the background image to the graphics
				SDL_Rect bg_os;
				bg_os.x = 0;
				bg_os.y = 0;
				bg_os.w = (int) (background_->w * (double) get_width() / 1920.0);
				bg_os.h = (int) (background_->h * (double) get_height() / 1080.0);

				if (background_ != nullptr)
				{
					SDL_BlitScaled(background_, NULL, graphics, &bg_os);
				}

				if (current_sequence_ != nullptr)
				{
					std::vector<int> columns = current_sequence_->get_columns();

					int max_index = std::abs(columns.at(0));
					if (std::abs(columns.back()) > max_index)
					{
						max_index = columns.back();
					}

					for (unsigned int i = 0; i < columns.size(); i++)
					{
						//draw by column
						int column = columns.at(i);
						int draw_x_pos = (int)(get_width()*((double)(column)/(max_index*2)));

						std::vector<std::shared_ptr<mae::fl::laban::i_movement> > movements =
								current_sequence_->get_column_movements(column);

						for (unsigned int j = 0; j < movements.size(); j++)
						{
							if (std::shared_ptr<mae::fl::laban::movement> mov = std::dynamic_pointer_cast<
									mae::fl::laban::movement>(movements.at(j)))
							{
								if (std::shared_ptr<mae::fl::laban::mv::direction_symbol> symb =
										std::dynamic_pointer_cast<mae::fl::laban::mv::direction_symbol>(
												mov->get_symbol()))
								{
									int draw_y_pos = (int)((get_height() - 50)*(1 - ((mov->get_measure()*current_sequence_->get_beats()+mov->get_beat()+mov->get_duration())/(current_sequence_->get_measures()*current_sequence_->get_beats())))); //TODO calculate to y pos and the height that is to be applied
									int draw_h = (int)((get_height() - 50)*(mov->get_duration()/(current_sequence_->get_measures()*current_sequence_->get_beats())));

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

										offset_scale.w = (int) (direction_surface->w * (double) get_width() / 1920.0);
										offset_scale.h = draw_h;

										//Blit the surface
										SDL_BlitScaled(direction_surface, NULL, graphics, &offset_scale);

									}
								}
							}
						}
					}
				}
			}

			void sequence_window::handle_event(SDL_Event& e)
			{
				//TODO handle event

			}

			void sequence_window::on_sequence(long timestamp, std::shared_ptr<mae::fl::laban::laban_sequence> sequence)
			{
				current_sequence_ = sequence;
				repaint();
			}

		} // namespace fl
	} // namespace demo
} // namespace mae
