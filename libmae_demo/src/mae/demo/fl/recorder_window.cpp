/*
 * recorder_window.cpp
 *
 *  Created on: 28.09.2014
 *      Author: keks
 */

#include "recorder_window.hpp"

namespace mae
{
	namespace demo
	{
		namespace fl
		{

			recorder_window::recorder_window(std::string title, bool backgroundimage,
					int width, int height, int x_pos, int y_pos, Uint32 flags) : sdl_window(title, width, height, x_pos, y_pos, flags)
			{

				backgroundimage_ = backgroundimage;
				background_ = nullptr;
				current_sequence_ = nullptr;
				countdown_ = -1;

				visualizer_ = std::shared_ptr<laban_visualizer>(
						new laban_visualizer(get_surface()->format));

				initialize();
			}

			recorder_window::~recorder_window()
			{
				cleanup();
			}

			void recorder_window::initialize()
			{
				//load background png image
				SDL_Surface* loaded_surface = IMG_LoadTyped_RW(SDL_RWFromConstMem(res::background0.data, res::background0.size), 1, "PNG");

				if (loaded_surface != nullptr)
				{
					background_ = SDL_ConvertSurface(loaded_surface, get_surface()->format, 0);

					//Get rid of old loaded surface
					SDL_FreeSurface(loaded_surface);
					loaded_surface = nullptr;

					if (background_ == nullptr)
					{
						std::stringstream e_sstr;
						e_sstr << "Unable to optimize image " << "! SDL Error: " << SDL_GetError()
								<< std::endl;
						throw std::runtime_error(e_sstr.str());
					}
				}
				else
				{
					std::stringstream e_sstr;
					e_sstr << "Unable to load image " << "! SDL Error: " << SDL_GetError()
							<< std::endl;
					throw std::runtime_error(e_sstr.str());
				}

				font_ = TTF_OpenFontRW(SDL_RWFromConstMem(res::droidsans_ttf.data, res::droidsans_ttf.size), 1, 45);

				if (font_ == nullptr)
				{
					cleanup();

					std::stringstream e_sstr;
					e_sstr << "Unable to load font! TTF Error: " << TTF_GetError() << std::endl;
					throw std::runtime_error(e_sstr.str());
				}

				repaint();
			}

			void recorder_window::cleanup()
			{
				if (background_ != nullptr)
				{
					SDL_FreeSurface(background_);
					background_ = nullptr;
				}

				if (font_ != nullptr)
				{
					TTF_CloseFont(font_);
					font_ = nullptr;
				}
			}

			void recorder_window::clear_paint()
			{
				current_sequence_ = nullptr;
				repaint();
			}

			void recorder_window::update_countdown(int time_left)
			{
				if (time_left < 0)
				{
					countdown_ = 0;
					clear_paint();
				}
				else
				{
					countdown_ = time_left;
					repaint();
				}

			}

			void recorder_window::paint(SDL_Surface* graphics)
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

					//print the number in the mid
					std::stringstream sstr;
					sstr << countdown_ << " s";

					TTF_Font* font = TTF_OpenFontRW(SDL_RWFromConstMem(res::droidsans_ttf.data, res::droidsans_ttf.size), 1, get_height()/10);

					SDL_Surface* text = TTF_RenderText_Solid(font, sstr.str().c_str(), TEXTCOLOR_ORANGE);
					SDL_Surface* text_sur = SDL_ConvertSurface(text, get_surface()->format, 0);

					//Get rid of old loaded surface
					SDL_FreeSurface(text);
					text = nullptr;

					SDL_Rect offset_scale = text_sur->clip_rect;
					offset_scale.x = 10;
					offset_scale.y = 10;

					SDL_BlitScaled(text_sur, NULL, graphics, &offset_scale);

					//free text surface
					SDL_FreeSurface(text_sur);
					text_sur = nullptr;
				}
				else
				{
					if (countdown_ >= 0)
					{
						//print the number in the mid
						std::stringstream sstr;
						sstr << countdown_ << " s";

						TTF_Font* font = TTF_OpenFontRW(SDL_RWFromConstMem(res::droidsans_ttf.data, res::droidsans_ttf.size), 1, get_height()/3);

						SDL_Surface* text = TTF_RenderText_Solid(font, sstr.str().c_str(), TEXTCOLOR_ORANGE);
						SDL_Surface* text_sur = SDL_ConvertSurface(text, get_surface()->format, 0);

						//Get rid of old loaded surface
						SDL_FreeSurface(text);
						text = nullptr;

						SDL_Rect offset_scale = text_sur->clip_rect;
						offset_scale.x = get_width()/2 - offset_scale.w/2;
						offset_scale.y = get_height()/2 - offset_scale.h/2;

						SDL_BlitScaled(text_sur, NULL, graphics, &offset_scale);

						//free text surface
						SDL_FreeSurface(text_sur);
						text_sur = nullptr;
					}
					else
					{
						//print waiting for calibration or something
						TTF_Font* font = TTF_OpenFontRW(SDL_RWFromConstMem(res::droidsans_ttf.data, res::droidsans_ttf.size), 1, get_height()/5);

						SDL_Surface* text = TTF_RenderText_Solid(font, wait_str, TEXTCOLOR_ORANGE);
						SDL_Surface* text_sur = SDL_ConvertSurface(text, get_surface()->format, 0);

						//Get rid of old loaded surface
						SDL_FreeSurface(text);
						text = nullptr;

						SDL_Rect offset_scale = text_sur->clip_rect;
						offset_scale.x = get_width()/2 - offset_scale.w/2;
						offset_scale.y = get_height()/2 - offset_scale.h/2;


						SDL_BlitScaled(text_sur, NULL, graphics, &offset_scale);

						//free text surface
						SDL_FreeSurface(text_sur);
						text_sur = nullptr;
					}
				}
			}

			void recorder_window::handle_event(SDL_Event& e)
			{
				//TODO handle event

			}

			void recorder_window::on_sequence(uint64_t timestamp, std::shared_ptr<mae::fl::laban::laban_sequence> sequence)
			{
				current_sequence_ = sequence;
				repaint();
			}

		} // namespace fl
	} // namespace demo
} // namespace mae
