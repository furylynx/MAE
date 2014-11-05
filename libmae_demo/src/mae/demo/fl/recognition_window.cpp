/*
 * recognition_window.cpp
 *
 *  Created on: 20.09.2014
 *      Author: keks
 */

#include "recognition_window.hpp"

namespace mae
{
	namespace demo
	{
		namespace fl
		{

			recognition_window::recognition_window(std::string title, bool backgroundimage, int width, int height,
					int x_pos, int y_pos, Uint32 flags)
					: sdl_window(title, width, height, x_pos, y_pos, flags)
			{
				background_ = nullptr;
				backgroundimage_ = backgroundimage;

				visualizer_ = std::shared_ptr<laban_visualizer>(new laban_visualizer(get_surface()->format));

				current_sequence_ = nullptr;
				current_sequence_title_ = "";

				initialize();
			}

			recognition_window::~recognition_window()
			{
				cleanup();
			}

			void recognition_window::initialize()
			{

//				//load background png image
//				std::stringstream bg_sstr;
//				bg_sstr << resources_dir_;
//				bg_sstr << "background0.png";
//				SDL_Surface* loaded_surface = IMG_Load(bg_sstr.str().c_str());

				SDL_Surface* loaded_surface = IMG_LoadTyped_RW(
						SDL_RWFromConstMem(res::background0.data, res::background0.size), 0, "PNG");

				if (loaded_surface != nullptr)
				{
					background_ = SDL_ConvertSurface(loaded_surface, get_surface()->format, 0);

					//Get rid of old loaded surface
					SDL_FreeSurface(loaded_surface);
					loaded_surface = nullptr;

					if (background_ == nullptr)
					{
						std::stringstream e_sstr;
						e_sstr << "Unable to optimize image " << "! SDL Error: " << SDL_GetError() << std::endl;
						throw std::runtime_error(e_sstr.str());
					}
				}
				else
				{
					std::stringstream e_sstr;
					e_sstr << "Unable to load image " << "! SDL Error: " << SDL_GetError() << std::endl;
					throw std::runtime_error(e_sstr.str());
				}

				repaint();
			}

			void recognition_window::cleanup()
			{
				if (background_ != nullptr)
				{
					SDL_FreeSurface(background_);
					background_ = nullptr;
				}
			}

			void recognition_window::paint(SDL_Surface* graphics)
			{
				//Apply the background image to the graphics
				SDL_Rect bg_os;
				bg_os.x = 0;
				bg_os.y = 0;
				bg_os.w = get_width();
				bg_os.h = get_height();

				if (background_ != nullptr && backgroundimage_)
				{
					SDL_BlitScaled(background_, NULL, graphics, &bg_os);
				}
				else
				{
					SDL_FillRect(graphics, &bg_os, 0xFFFFFFFF);
				}

				if (current_sequence_ != nullptr)
				{
					visualizer_->paint_sequence(graphics, current_sequence_, get_width(), get_height());
				}
				else
				{
					if (current_sequence_title_.length() > 0)
					{
						//print title to window -> use sdl_ttf
						TTF_Font* font = TTF_OpenFontRW(
								SDL_RWFromConstMem(res::droidsans_ttf.data, res::droidsans_ttf.size), 1, 45);

						if (font != nullptr)
						{
							SDL_Surface* tmp_surface = TTF_RenderText_Solid(font, current_sequence_title_.c_str(),
									TEXTCOLOR);

							if (tmp_surface != nullptr)
							{
								SDL_Surface* txt_surface = SDL_ConvertSurface(tmp_surface, get_surface()->format, 0);

								if (txt_surface != nullptr)
								{
									SDL_Rect offset_scale;
									offset_scale.w = get_width() / 3;
									offset_scale.h = (int) (txt_surface->h * ((get_width() / 3.0) / txt_surface->w));

									offset_scale.x = get_width() / 2 - offset_scale.w / 2;
									offset_scale.y = get_height() / 2 - offset_scale.h / 2;

									SDL_BlitScaled(txt_surface, NULL, graphics, &offset_scale);
								}

								//free text surface
								SDL_FreeSurface(txt_surface);
								txt_surface = nullptr;
							}

							//Get rid of old loaded surface
							SDL_FreeSurface(tmp_surface);
							tmp_surface = nullptr;

						}

						TTF_CloseFont(font);
						font = nullptr;
					}
				}
			}

			void recognition_window::handle_event(SDL_Event& e)
			{
				//TODO handle event

			}

			void recognition_window::on_recognition(long timestamp,
					std::vector<std::shared_ptr<mae::fl::laban::laban_sequence> > sequences)
			{
				if (sequences.size() > 0)
				{
					current_sequence_ = sequences.front();

					repaint();
				}
			}

			void recognition_window::on_recognition(long timestamp, std::vector<std::string> titles)
			{
				if (titles.size() > 0)
				{
					current_sequence_title_ = titles.front();

					repaint();
				}
			}

		} // namespace fl
	} // namespace demo
} // namespace mae
